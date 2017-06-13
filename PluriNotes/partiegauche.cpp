#include "partiegauche.h"

PartieGauche::PartieGauche(QWidget *parent) : QDockWidget(parent)
{
    // On met un widget qui prend toute le surface, car un QDockWidget ne peut pas contenir de layout
    widgetTotal = new QWidget;

    layout = new QVBoxLayout(widgetTotal);

    noteActive = new QListWidget(widgetTotal);
    tache = new QListWidget(widgetTotal);
    archive = new QListWidget(widgetTotal);
    //corbeille = new QListWidget(widgetTotal);

    layout->addWidget(noteActive);
    layout->addWidget(tache);
    layout->addWidget(archive);

    chargerListeNote();
    chargerListeTaches();
    chargerListeArchive();

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

void PartieGauche::chargerListeTaches()
{
    NoteManager& instance = NoteManager::getInstance();

    for(NoteManager::TypeIterator it = instance.begin(TACHE); it != instance.end();++it)
    {
        new QListWidgetItem((*it)->getId(),tache);
    }
}

void PartieGauche::chargerListeArchive()
{
    NoteManager& instance = NoteManager::getInstance();

    for(int typeInt = ARTICLE; typeInt != FIN; typeInt++)
    {
        TypeNote type = static_cast<TypeNote>(typeInt);

        for(NoteManager::TypeIterator it = instance.begin(type, true); it != instance.end(); ++it)
        {
            new QListWidgetItem((*it)->getId(), archive);
        }
    }
}
