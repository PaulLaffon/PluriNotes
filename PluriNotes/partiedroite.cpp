#include "partiedroite.h"

PartieDroite::PartieDroite(QWidget *parent) : QDockWidget(parent)
{
    window = new QWidget(this);

    layout = new QVBoxLayout(window);

    gestionRelation = new QPushButton("Detail Relation", window);

    arbre = new QTreeWidget(window);

    layout->addWidget(arbre);
    layout->addWidget(gestionRelation);

    this->setWidget(window);
}

PartieDroite::~PartieDroite()
{

}


void PartieDroite::chargerArbre(Note *n)
{
    arbre->clear();

    QTreeWidgetItem* racine = new QTreeWidgetItem(arbre, QTreeWidgetItem::Type);

    racine->setText(0, n->getId());

    QSet<Note*> noteDejaAjoutes;
    chargerArbreRecursif(racine, n, noteDejaAjoutes);
}

void PartieDroite::chargerArbreRecursif(QTreeWidgetItem *pere, Note *noteActu, QSet<Note *> &noteDejaAjoutes)
{
    RelationManager& relations = RelationManager::getInstance();

    if(noteDejaAjoutes.contains(noteActu))
        return;

    noteDejaAjoutes.insert(noteActu);

    for(RelationManager::iteratorPredSucc it = relations.begin(noteActu, true); it != relations.endSuccPred(); ++it)
    {
        QTreeWidgetItem *fils = new QTreeWidgetItem(pere, QTreeWidgetItem::Type);
        fils->setText(0, (*it)->getId());

        chargerArbreRecursif(fils, *it, noteDejaAjoutes);
    }
    arbre->expandItem(pere);
}

QPushButton* PartieDroite::getButton()
{
 return gestionRelation;
}
