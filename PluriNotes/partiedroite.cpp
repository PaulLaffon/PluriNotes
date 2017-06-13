#include "partiedroite.h"

PartieDroite* PartieDroite::instance = nullptr;

PartieDroite::PartieDroite() : QDockWidget()
{
    window = new QWidget(this);

    layout = new QVBoxLayout(window);

    gestionRelation = new QPushButton("Detail Relation", window);

    arbreFils = new QTreeWidget(window);
    arbrePere = new QTreeWidget(window);

    if(arbreFils->headerItem())
    {
         arbreFils->headerItem()->setText(0, "Arbre des fils");
    }
    if(arbrePere->headerItem())
    {
         arbrePere->headerItem()->setText(0, "Arbre des pères");
    }

    layout->addWidget(arbreFils);
    layout->addWidget(arbrePere);
    layout->addWidget(gestionRelation);

    this->setWidget(window);
}

PartieDroite::~PartieDroite()
{

}

PartieDroite* PartieDroite::getInstance()
{
    if(PartieDroite::instance == nullptr)
        PartieDroite::instance = new PartieDroite();

    return PartieDroite::instance;
}

void PartieDroite::deleteInstance()
{
    if(PartieDroite::instance != nullptr)
        delete PartieDroite::instance;

    PartieDroite::instance = nullptr;
}

void PartieDroite::chargerArbre(Note *n)
{
    arbreFils->clear();
    arbrePere->clear();

    QTreeWidgetItem* racineFils = new QTreeWidgetItem(arbreFils, QTreeWidgetItem::Type);
    QTreeWidgetItem* racinePere = new QTreeWidgetItem(arbrePere, QTreeWidgetItem::Type);

    racineFils->setText(0, n->getId());
    racinePere->setText(0, n->getId());

    QSet<Note*> noteDejaAjoutes;
    chargerArbreRecursif(racineFils, n, noteDejaAjoutes, true);
    noteDejaAjoutes.clear();
    chargerArbreRecursif(racinePere, n, noteDejaAjoutes, false);

    arbreFils->expandAll();
    arbrePere->expandAll();
}

void PartieDroite::chargerArbreRecursif(QTreeWidgetItem *pere, Note *noteActu, QSet<Note *> &noteDejaAjoutes, bool successeur)
{
    RelationManager& relations = RelationManager::getInstance();

    if(noteDejaAjoutes.contains(noteActu))
        return;

    noteDejaAjoutes.insert(noteActu);

    for(RelationManager::iteratorPredSucc it = relations.begin(noteActu, successeur); it != relations.endSuccPred(); ++it)
    {
        QTreeWidgetItem *fils = new QTreeWidgetItem(pere, QTreeWidgetItem::Type);
        fils->setText(0, (*it)->getId());

        if(it.getRelation()->getTitre() == QString("Référence"))
            fils->setForeground(0, QBrush(Qt::red));

        chargerArbreRecursif(fils, *it, noteDejaAjoutes, successeur);
    }
}

QPushButton* PartieDroite::getButton()
{
 return gestionRelation;
}
