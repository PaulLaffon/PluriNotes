#include "partiegauche.h"

PartieGauche::PartieGauche(QWidget *parent) : QDockWidget(parent)
{
    // On met un widget qui prend toute le surface, car un QDockWidget ne peut pas contenir de layout
    widgetTotal = new QWidget;

    layout = new QVBoxLayout(widgetTotal);

    noteActive = new QListWidget(widgetTotal);
    tache = new QListWidget(widgetTotal);

    layout->addWidget(noteActive);
    layout->addWidget(tache);

    chargerListeNote();
    new QListWidgetItem(tr("Ici seront les tache"), tache);

    this->setWidget(widgetTotal);
}

PartieGauche::~PartieGauche()
{

}

void PartieGauche::chargerListeNote()
{
    NoteManager& instance = NoteManager::getInstance();

    noteActive->clear(); // On s'assure que la liste est vide

    // Iterateur sur tout les articles
    for(NoteManager::TypeIterator it = instance.begin(ARTICLE); it != instance.end(); ++it)
    {
        // Ajoute chaque article à la liste
        new QListWidgetItem((*it)->getId(), noteActive);
    }
}
