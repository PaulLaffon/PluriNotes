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

    if(note->isArchive() || note->isInCorbeille()) // Si la note est à la corbeille ou archivée
    {
        titre->setReadOnly(true);
        save->setDisabled(true);
        supprimer->setText(QString("Restaurer la note"));
        connect(supprimer, SIGNAL(clicked(bool)),this, SLOT(restaurerNote()));
    }
    else
        connect(supprimer, SIGNAL(clicked(bool)), this, SLOT(supprimerNote()));

    connect(titre, SIGNAL(textChanged(QString)), this, SLOT(sauvegardePossible()));
    setWidget(window); // On affiche le widget dans le QMdiSubWindow
}

AffichageNote::~AffichageNote()
{

}

void AffichageNote::sauvegardePossible()
{
    save->setEnabled(true);
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

void AffichageNote::supprimerNote()
{
    NoteManager& instance = NoteManager::getInstance();

    instance.clicSupprimerNote(note);
    close();
}

void AffichageNote::restaurerNote()
{
    NoteManager& instance = NoteManager::getInstance();

    instance.restaurerNote(note);
    close();
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

    if(note->isArchive() || note->isInCorbeille()) // Si la note est à la corbeille ou archivée
    {
        texte->setReadOnly(true);
    }
    else
        connect(save, SIGNAL(clicked(bool)), this, SLOT(nouvelleVersion()));

    connect(texte, SIGNAL(textChanged()), this, SLOT(sauvegardePossible()));
}

AffichageArticle::~AffichageArticle()
{

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

    save->setDisabled(true);
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

    save->setDisabled(true);

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
    echeance = new QDateTimeEdit(this);
    statusEnAttente = new QRadioButton("En attente", this);
    statusEnCours = new QRadioButton("En cours", this);
    statusTerminee = new QRadioButton("Terminee", this);
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

    if(note->isArchive() || note->isInCorbeille()) // Si la note est à la corbeille ou archivée
    {
        action->setReadOnly(true);
        echeance->setReadOnly(true);
        groupStatus->setDisabled(true);
        priorite->setDisabled(true);
    }
    else
        connect(save, SIGNAL(clicked(bool)), this, SLOT(nouvelleVersion()));

    connect(action, SIGNAL(textChanged()), this, SLOT(sauvegardePossible()));
    connect(echeance, SIGNAL(dateTimeChanged(QDateTime)), this, SLOT(sauvegardePossible()));
    connect(priorite, SIGNAL(textChanged(QString)), this, SLOT(sauvegardePossible()));
}

AffichageTache::~AffichageTache()
{
    delete layoutAction;
    delete layoutPriorite;
    delete layoutEcheance;
    delete layoutStatus;
    delete layoutButtons;
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
    echeance->setDateTime(t->getEcheance());
    priorite->setText(QString::number(t->getPriorite()));
    statusAffichage = t->getStatus();

    if(statusAffichage == enAttente)
        statusEnAttente->setChecked(true);
    else if(statusAffichage == enCours)
        statusEnCours->setChecked(true);
    else
        statusTerminee->setChecked(true);

    save->setDisabled(true);

}

void AffichageTache::nouvelleVersion()
{
    note->supprimerVersionVide();

    if(statusEnAttente->isChecked())
        statusAffichage = enAttente;
    else if(statusEnCours->isChecked())
        statusAffichage = enCours;
    else
        statusAffichage = terminee;

    note->ajouterVersion(titre->text(), action->toPlainText(),priorite->text().toInt(),QDateTime::fromString(echeance->text()),statusAffichage);
    chargerListeVersion();

    save->setDisabled(true);

    emit actualisation(note);
}

