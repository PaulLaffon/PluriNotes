#include "affichagenote.h"

AffichageNote::AffichageNote(Note* n, QWidget *parent) : QMdiSubWindow(parent), note(n)
{
    window = new QWidget(this); // Widget qui prends la zone, il sert à mettre un layout
    layoutPrincipal = new QVBoxLayout(window);
    layoutId = new QHBoxLayout();
    layoutTitre = new QHBoxLayout();

    labelId = new QLabel("Id : ", this);
    labelTitre = new QLabel("Titre : ", this);

    id = new QLineEdit(this);
    id->setReadOnly(true);
    titre = new QLineEdit(this);

    save = new QPushButton("Sauvegarder", this);

    supprimer = new QPushButton("Supprimer la note", this);

    listeVersion = new QComboBox(this);

    chargerListeVersion();

    // Récupérer lorsque l'on change de version dans la liste déroulante
    connect(listeVersion, SIGNAL(currentIndexChanged(int)), this, SLOT(selectionVersion(int)));


    layoutId->addWidget(labelId);
    layoutId->addWidget(id);

    layoutTitre->addWidget(labelTitre);
    layoutTitre->addWidget(titre);

    layoutPrincipal->addLayout(layoutId);
    layoutPrincipal->addWidget(listeVersion);
    layoutPrincipal->addLayout(layoutTitre);
    layoutPrincipal->addWidget(save);
    layoutPrincipal->addWidget(supprimer);

    setWidget(window); // On affiche le widget dans le QMdiSubWindow
}

void AffichageNote::chargerListeVersion()
{
    listeVersion->clear();

    for(Note::iterator it = note->begin(); it != note->end(); ++it)
    {
        listeVersion->insertItem(0, (*it).getModif().toString());
    }

    listeVersion->setCurrentIndex(0);
}

// Redéfinition de la fonction quand la sous fenetre est fermée
void AffichageNote::closeEvent(QCloseEvent *event)
{
    emit fermetureNote(id->text());
    event->accept();
}

// Redéfinition de la fonction quand la sous fenetre passe au premier plan
void AffichageNote::focusInEvent(QFocusEvent *event)
{
    emit passagePremierPlan(note);
    event->accept();
}

AffichageArticle::AffichageArticle(Note *n, QWidget *parent) :AffichageNote(n, parent)
{
    layoutTexte = new QHBoxLayout();
    labelTexte= new QLabel("Texte : ", this);
    texte = new QTextEdit(this);

    layoutTexte->addWidget(labelTexte);
    layoutTexte->addWidget(texte);

    layoutPrincipal->insertLayout(3, layoutTexte);

    // On charge la dernière version
    chargerVersion(note->getNumberVersion() - 1);

    connect(save, SIGNAL(clicked(bool)), this, SLOT(nouvelleVersion()));
}

// Charge la i-ème version de l'article
void AffichageArticle::chargerVersion(unsigned int i)
{
    // A ce moment là, la note est obligatoirement un Article
    Article *a = dynamic_cast<Article*>(note->getVersion(i));

    // Test au cas où le dynamique cast échoue
    if(a == nullptr) throw NoteException("La note passé ne correspond pas à un article, erreur de dynamique cast");

    texte->setText(a->getDescription());
    titre->setText(a->getTitre());
    id->setText(note->getId());
}

// SLOT change la version quand on choisi dans la liste déroulante
void AffichageNote::selectionVersion(int i)
{
    if(listeVersion->currentIndex() < 0)
        return;
    // On charge le bonne version, ls indices sont inversé dans QComboBox et Note
    chargerVersion(note->getNumberVersion() - i - 1);
}

void AffichageArticle::nouvelleVersion()
{
    note->supprimerVersionVide();
    note->ajouterVersion(titre->text(), texte->toPlainText());
    chargerListeVersion();

    emit actualisation(note);
}

AffichageTache::AffichageTache(Note *n,QWidget *parent) : AffichageNote(n,parent)
{
    layoutAction = new QHBoxLayout();
    layoutPriorite = new QHBoxLayout();
    layoutEcheance = new QHBoxLayout();
    layoutStatus = new QHBoxLayout();
    layoutButtons = new QVBoxLayout();

    labelAction = new QLabel("Action : ",this);
    labelPriorite = new QLabel("Priorite : ",this);
    labelEcheance = new QLabel("Echeance : ",this);
    groupStatus = new QGroupBox("Status",this);

    action = new QTextEdit(this);
    priorite = new QLineEdit(this);
    echeance = new QLineEdit(this);
    statusEnAttente = new QRadioButton("En attente");
    statusEnCours = new QRadioButton("En cours");
    statusTerminee = new QRadioButton("Terminee");
    //statusEnAttente->setChecked(true);
    statusAffichage = enAttente;

    layoutButtons->addWidget(statusEnAttente);
    layoutButtons->addWidget(statusEnCours);
    layoutButtons->addWidget(statusTerminee);

    layoutAction->addWidget(labelAction);
    layoutAction->addWidget(action);

    layoutPriorite->addWidget(labelPriorite);
    layoutPriorite->addWidget(priorite);

    layoutEcheance->addWidget(labelEcheance);
    layoutEcheance->addWidget(echeance);

    groupStatus->setLayout(layoutButtons);
    layoutStatus->addWidget(groupStatus);

    layoutPrincipal->insertLayout(3,layoutEcheance);
    layoutPrincipal->insertLayout(4,layoutPriorite);
    layoutPrincipal->insertLayout(5,layoutStatus);
    layoutPrincipal->insertLayout(6,layoutAction);

    chargerVersion(note->getNumberVersion() - 1);

    connect(save, SIGNAL(clicked(bool)), this, SLOT(nouvelleVersion()));


}

void AffichageTache::setStatus()
{
    if (statusAffichage==enCours)
    {
        statusEnCours->setChecked(true);
        statusEnAttente->setChecked(false);
    }
    else if (statusAffichage==terminee)
    {
        statusTerminee->setChecked(true);
        statusEnAttente->setChecked(false);
    }
    else if (statusAffichage==enAttente)
    {
        statusEnAttente->setChecked(true);
    }
}



void AffichageTache::chargerVersion(unsigned int i)
{
    // A ce moment là, la note est obligatoirement une Tache
    Tache *t = dynamic_cast<Tache*>(note->getVersion(i));

    // Test au cas où le dynamique cast échoue
    if(t == nullptr) throw NoteException("La note passé ne correspond pas à une tache, erreur de dynamique cast");

    action->setText(t->getAction());
    titre->setText(t->getTitre());
    id->setText(note->getId());
    echeance->setText(t->getEcheance().toString());
    priorite->setText(QString::number(t->getPriorite()));
    statusAffichage = t->getStatus();
    setStatus();

    modifStatus(t);

}

void AffichageTache::nouvelleVersion()
{
    note->ajouterVersion(titre->text(), action->toPlainText(),priorite->text().toInt(),QDateTime::fromString(echeance->text()),statusAffichage);
    chargerListeVersion();

    emit actualisation(note);
}

void AffichageTache::modifStatus(Tache *t)
{
    connect(statusEnAttente,SIGNAL(toggled(bool)),t,SLOT(setStatusEnAttente(bool)));
    connect(statusEnCours,SIGNAL(toggled(bool)),t,SLOT(setStatusEnCours(bool)));
    connect(statusTerminee,SIGNAL(toggled(bool)),t,SLOT(setStatusTerminee(bool)));
    statusAffichage = t->getStatus();
}


