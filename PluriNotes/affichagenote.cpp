#include "affichagenote.h"

AffichageNote::AffichageNote(QWidget *parent) : QWidget(parent), note(nullptr)
{
    layoutPrincipal = new QVBoxLayout(this);
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
}

AffichageArticle::AffichageArticle(const QString& _id, unsigned int version, QWidget *parent) :AffichageNote(parent)
{
    layoutTexte = new QHBoxLayout();
    labelTexte= new QLabel("Texte : ", this);
    texte = new QTextEdit(this);

    layoutTexte->addWidget(labelTexte);
    layoutTexte->addWidget(texte);

    layoutPrincipal->insertLayout(2, layoutTexte);

    NoteManager& instance = NoteManager::getInstance();

    note = instance.find(_id);
    Article* a = dynamic_cast<Article*>(note->getVersion(version));

    if(a == nullptr) throw NoteException("La note passé ne correspond pas à un article, erreur de dynamique cast");

    texte->setText(a->getTexte());
    titre->setText(a->getTitre());
    id->setText(note->getId());
}
