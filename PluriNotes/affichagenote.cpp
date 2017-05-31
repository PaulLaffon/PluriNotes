#include "affichagenote.h"

AffichageNote::AffichageNote(QWidget *parent) : QMdiSubWindow(parent), note(nullptr)
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


    layoutId->addWidget(labelId);
    layoutId->addWidget(id);

    layoutTitre->addWidget(labelTitre);
    layoutTitre->addWidget(titre);

    layoutPrincipal->addLayout(layoutId);
    layoutPrincipal->addLayout(layoutTitre);
    layoutPrincipal->addWidget(save);

    setWidget(window); // On affiche le widget dans le QMdiSubWindow
}

// Redéfinition de la fonction quand la sous fenetre est fermée
void AffichageNote::closeEvent(QCloseEvent *event)
{
    emit fermetureNote(id->text());
    event->accept();
}

AffichageArticle::AffichageArticle(Note *n, QWidget *parent) :AffichageNote(parent)
{
    layoutTexte = new QHBoxLayout();
    labelTexte= new QLabel("Texte : ", this);
    texte = new QTextEdit(this);

    layoutTexte->addWidget(labelTexte);
    layoutTexte->addWidget(texte);

    layoutPrincipal->insertLayout(2, layoutTexte);

    note = n;
    // A ce moment là, la note est obligatoirement un Article
    Article* a = dynamic_cast<Article*>(note->getLastVersion());

    // Test au cas où le dynamique cast échoue
    if(a == nullptr) throw NoteException("La note passé ne correspond pas à un article, erreur de dynamique cast");

    texte->setText(a->getTexte());
    titre->setText(a->getTitre());
    id->setText(note->getId());
}
