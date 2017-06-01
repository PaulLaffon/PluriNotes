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

    texte->setText(a->getTexte());
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
    note->ajouterVersion(titre->text(), texte->toPlainText());
    chargerListeVersion();
}
