#include "creationcouple.h"

CreationCouple::CreationCouple(QWidget *parent): QDialog(parent)
{
    layout = new QVBoxLayout();

    labelTitre = new QLabel("Titre de la relation : ", this);
    labelRelation = new QLabel("Type de Relation: ", this);
    labelNote1 = new QLabel("Note mère : ", this);
    labelNote2 = new QLabel("Note fille : ", this);

    titre = new QLineEdit(this);
    listeRelation = new QComboBox(this);
    listeNote1 = new QComboBox(this);
    listeNote2 = new QComboBox(this);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(valider()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    layout->addWidget(labelTitre);
    layout->addWidget(titre);

    layout->addWidget(labelRelation);
    layout->addWidget(listeRelation);

    layout->addWidget(labelNote1);
    layout->addWidget(listeNote1);

    layout->addWidget(labelNote2);
    layout->addWidget(listeNote2);

    layout->addWidget(buttonbox);

    this->setLayout(layout);
}

void CreationCouple::valider()
{   QString idnote1 = listeNote1->currentText();
    QString idnote2 = listeNote2->currentText();
    QString idrelation = listeRelation->currentText();
    NoteManager& instance = NoteManager::getInstance();
    Note* notemere = instance.find(idnote1);
    Note* notefille = instance.find(idnote2);

    emit CoupleAccepter(titre->text(),idrelation,notemere,notefille);
    accept();
}

void CreationCouple::chargerListeRelation()
{
    RelationManager& relations = RelationManager::getInstance();

    listeRelation->clear();

    for(RelationManager::iterator it = relations.begin(); it != relations.end(); ++it)
    {
        listeRelation->insertItem(0, (*it).getTitre());
    }

    listeRelation->setCurrentIndex(0);
}

void CreationCouple::chargerListeNote1()
{
    listeNote1->clear();

    NoteManager& instance = NoteManager::getInstance();

    for ( int typeInt = ARTICLE; typeInt != FIN; typeInt++ )
    {
       TypeNote type = static_cast<TypeNote>(typeInt);

    for(NoteManager::TypeIterator it = instance.begin(type); it != instance.end(); ++it)
    {
        listeNote1->insertItem(0, (*it)->getId());
    }
    }

    listeNote2->setCurrentIndex(0);
}

void CreationCouple::chargerListeNote2()
{
    listeNote2->clear();

    NoteManager& instance = NoteManager::getInstance();

    for ( int typeInt = ARTICLE; typeInt != FIN; typeInt++ )
    {
       TypeNote type = static_cast<TypeNote>(typeInt);

    for(NoteManager::TypeIterator it = instance.begin(type); it != instance.end(); ++it)
    {
        listeNote2->insertItem(0, (*it)->getId());
    }
    }

    listeNote2->setCurrentIndex(0);
}
