#include "gestionrelation.h"

GestionRelation::GestionRelation(QWidget *parent) : QDialog(parent)
{
    layoutPrincipal = new QVBoxLayout();
    layoutRelations = new QHBoxLayout();
    layoutCouples = new QHBoxLayout();
    layoutModifTitre = new QHBoxLayout();
    layoutModifDescription = new QHBoxLayout();
    layoutModifCouples = new QHBoxLayout();


    listeRelations = new QComboBox(this);
    connect(listeRelations, SIGNAL(currentIndexChanged(QString)), this, SLOT(chargerChangementRelation(QString)));
    modifTitre = new QLineEdit(this);
    modifDescription= new QTextEdit(this);
    listeCouples = new QComboBox(this);
    connect(listeCouples, SIGNAL(currentIndexChanged(QString)), this, SLOT(chargerCouple(QString)));
    modifCouple = new QLineEdit(this);


    labelRelations = new QLabel("Liste des Relation : ", this);
    labelModifTitre = new QLabel("Titre : ", this);
    labelModifDescription = new QLabel("Description : ", this);
    labelCouples = new QLabel("Liste des Couples de la Relation : ",this);
    labelModifCouples = new QLabel("Titre : ",this);

    supprimer = new QPushButton("Supprimer", this);
    sauvegarder = new QPushButton("Sauvergarder",this);
    connect(supprimer, SIGNAL(clicked(bool)), this, SLOT(sauvegarderModif()));
    connect(supprimer, SIGNAL(clicked(bool)), this, SLOT(supprimerCouple()));

    layoutRelations->addWidget(labelRelations);
    layoutRelations->addWidget(listeRelations);

    layoutModifTitre->addWidget(labelModifTitre);
    layoutModifTitre->addWidget(modifTitre);

    layoutModifDescription->addWidget(labelModifDescription);
    layoutModifDescription->addWidget(modifDescription);

    layoutCouples->addWidget(labelCouples);
    layoutCouples->addWidget(listeCouples);

    layoutModifCouples->addWidget(labelModifCouples);
    layoutModifCouples->addWidget(modifCouple);

    layoutPrincipal->addLayout(layoutRelations);
    layoutPrincipal->addLayout(layoutModifTitre);
    layoutPrincipal->addLayout(layoutModifDescription);
    layoutPrincipal->addLayout(layoutCouples);
    layoutPrincipal->addLayout(layoutModifCouples);

    layoutPrincipal->addWidget(sauvegarder);
    layoutPrincipal->addWidget(supprimer);


    this->setLayout(layoutPrincipal);
}



void GestionRelation::chargerListeRelations()
{
    RelationManager& relations = RelationManager::getInstance();

    listeRelations->clear();

    for(RelationManager::iterator it = relations.begin(); it != relations.end(); ++it)
    {
        listeRelations->insertItem(0, (*it).getTitre());
    }

    listeRelations->setCurrentIndex(0);
}

void GestionRelation::chargerListeCouples(QString titre)
{
    RelationManager& instance = RelationManager::getInstance();

    listeCouples->clear();
    
    Relation* relation = instance.find(titre);

    for(Relation::iterator it = relation->begin(); it != relation->end(); ++it)
    {
        listeCouples->insertItem(0, (*it).getLabel() + '-' + (*it).getPere()->getId() + '-' + (*it).getFils()->getId());
    }

    listeCouples->setCurrentIndex(0);
}

void GestionRelation::sauvegarderModif()
{
    Relation* relation = selectionnerRelation();
    relation->setTitre(modifTitre->text());
    relation->setDescription(modifDescription->toPlainText());
    Couple* couple = selectionnerCouple();
    couple->setLabel(modifCouple->text());

}

void GestionRelation::supprimerCouple()
{

}

Couple* GestionRelation::selectionnerCouple()
{
    Relation* relation = selectionnerRelation();

    NoteManager& instance = NoteManager::getInstance();

    QString titrecouple=listeCouples->currentText().section('-', 0,0);
    QString titrenote1=listeCouples->currentText().section('-', 1,1);
    QString titrenote2=listeCouples->currentText().section('-', 2,2);

    Note* note1 = instance.find(titrenote1);
    Note* note2 = instance.find(titrenote2);

    Couple* couple = relation->findCouple(titrecouple,note1,note2);

    return couple;
}

Relation* GestionRelation::selectionnerRelation()
{
    RelationManager& instance = RelationManager::getInstance();
    QString titrerelation=listeRelations->currentText();
    Relation* relation = instance.find(titrerelation);
    return relation;
}

void GestionRelation::chargerRelation()
{
    Relation* relation = selectionnerRelation();
    modifTitre->setText(relation->getTitre());
    modifDescription->setText(relation->getDescription());
}

void GestionRelation::chargerCouple(QString titre)
{
    QString titrecouple = titre.section(' ', 0,0);
    modifCouple->setText(titrecouple);
}

void GestionRelation::chargerChangementRelation(QString titre)
{
    chargerListeCouples(titre);
    chargerRelation();
}
