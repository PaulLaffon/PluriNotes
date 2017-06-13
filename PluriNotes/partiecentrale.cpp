#include "partiecentrale.h"

PartieCentrale::PartieCentrale(QWidget *parent) : QMdiArea(parent)
{

}

// SLOT, appelé lorsque qu'on double clic sur une note dans le menu à gauche
void PartieCentrale::ouvrirNote(QListWidgetItem *item)
{
    ouvrirNote(item->text());
}

// SLOT, appelé lorsque qu'on double clic sur une note dans le menu à droite (arborescense)
void PartieCentrale::ouvrirNote(QTreeWidgetItem *item, int column)
{
    ouvrirNote(item->text(column));
}

// Fonction appelée par les slots du même nom pour ouvrir une note
void PartieCentrale::ouvrirNote(const QString &id)
{
    // Si la note est déjà affiché, on la mets au premier plan et on arrete la fonction
    if(dejaOuvert(id))
    {
        dejaOuvert(id)->setFocus();
        return;
    }

    // on récupère la note correspondant à l'id
    NoteManager& instance = NoteManager::getInstance();
    Note* n = instance.find(id);

    AffichageNote *affichage = nullptr;
    // Ici on gère les différents type de note à ouvrir
    if(n->type() == ARTICLE)
        affichage = new AffichageArticle(n, this);
    else if (n->type() == TACHE)
        affichage = new AffichageTache(n,this);
    else
        throw NoteException("Type de note non pris en charge lors de l'ouverture de l'affichage de la note");

    affichage->show();
    notes.push_back(affichage);

    // Lors de la fermeture de cette note, on veut l'enlever du tableau
    connect(notes.back(), SIGNAL(fermetureNote(const QString&)), this, SLOT(fermerNote(const QString&)));
    connect(notes.back(), SIGNAL(passagePremierPlan(Note*)), this, SLOT(emitRechargerArbre(Note*)));
    connect(notes.back(), SIGNAL(actualisation(Note*)), &instance, SLOT(actualiserReference()));
    connect(notes.back(), SIGNAL(actualisation(Note*)), this, SLOT(emitRechargerArbre(Note*)));

    emit rechargerArbre(n);
}

// SLOT, on enlève la note du tableau
void PartieCentrale::fermerNote(const QString &id)
{
    for(int i = 0; i < notes.size(); i++)
    {
        if(notes[i]->getId() == id)
        {
            notes.erase(notes.begin() + i);
            return;
        }
    }
}

AffichageNote* PartieCentrale::dejaOuvert(const QString& id) const
{
    for(int i = 0; i < notes.size(); i++)
    {
        if(notes[i]->getId() == id)
            return notes[i];
    }

    return nullptr;
}

void PartieCentrale::emitRechargerArbre(Note *n)
{
    emit rechargerArbre(n);
}

