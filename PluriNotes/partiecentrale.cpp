#include "partiecentrale.h"

PartieCentrale::PartieCentrale(QWidget *parent) : QMdiArea(parent)
{

}

// SLOT
void PartieCentrale::ouvrirNote(QListWidgetItem *item)
{
    // Si la note est déjà affiché, on la mets au premier plan et on arrete la fonction
    if(dejaOuvert(item->text()))
    {
        dejaOuvert(item->text())->setFocus();
        return;
    }

    // on récupère la note correspondant à l'id
    NoteManager& instance = NoteManager::getInstance();
    Note* n = instance.find(item->text());

    AffichageNote *affichage = nullptr;
    // Ici on gère les différents type de note à ouvrir
    if(n->type() == ARTICLE)
        affichage = new AffichageArticle(n, this);
    else
        throw NoteException("Type de note non pris en charge lors de l'ouverture de l'affichage de la note");

    affichage->show();
    notes.push_back(affichage);

    // Lors de la fermeture de cette note, on veut l'enlever du tableau
    connect(notes.back(), SIGNAL(fermetureNote(const QString&)), this, SLOT(fermerNote(const QString&)));
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
