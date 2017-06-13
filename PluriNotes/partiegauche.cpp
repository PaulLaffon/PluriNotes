#include "partiegauche.h"

PartieGauche* PartieGauche::instance = nullptr;

PartieGauche::PartieGauche() : QDockWidget()
{
    // On met un widget qui prend toute le surface, car un QDockWidget ne peut pas contenir de layout
    widgetTotal = new QWidget;

    layout = new QVBoxLayout(widgetTotal);

    QLabel *labelActives = new QLabel(QString("Notes Actives :"));
    QLabel *labelTache = new QLabel(QString("Taches :"));
    QLabel *labelArchive = new QLabel(QString("Notes archivées :"));
    QLabel *labelCorbeille = new QLabel(QString("Corbeille :"));


    noteActive = new QListWidget(widgetTotal);
    tache = new QListWidget(widgetTotal);
    archive = new QListWidget(widgetTotal);
    corbeille = new QListWidget(widgetTotal);

    layout->addWidget(labelActives);
    layout->addWidget(noteActive);
    layout->addWidget(labelTache);
    layout->addWidget(tache);
    layout->addWidget(labelArchive);
    layout->addWidget(archive);
    layout->addWidget(labelCorbeille);
    layout->addWidget(corbeille);

    chargerAll();

    this->setWidget(widgetTotal);
}

PartieGauche::~PartieGauche()
{

}

PartieGauche* PartieGauche::getInstance()
{
    if(PartieGauche::instance == nullptr)
        PartieGauche::instance = new PartieGauche();

    return PartieGauche::instance;
}

void PartieGauche::deleteInstance()
{
    if(PartieGauche::instance != nullptr)
        delete PartieGauche::instance;

    PartieGauche::instance = nullptr;
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
    for(NoteManager::TypeIterator it2 = instance.begin(MEDIA_IMG); it2 != instance.end(); ++it2)
    {
        // Ajoute chaque article à la liste
        new QListWidgetItem((*it2)->getId(), noteActive);
    }
}

void PartieGauche::chargerListeTaches()
{
    NoteManager& instance = NoteManager::getInstance();

    tache->clear();

    for(NoteManager::TypeIterator it = instance.begin(TACHE); it != instance.end();++it)
    {
        new QListWidgetItem((*it)->getId(),tache);
    }
}

void PartieGauche::chargerListeArchive()
{
    NoteManager& instance = NoteManager::getInstance();

    archive->clear();

    for(int typeInt = ARTICLE; typeInt != FIN; typeInt++)
    {
        TypeNote type = static_cast<TypeNote>(typeInt);

        for(NoteManager::TypeIterator it = instance.begin(type, true); it != instance.end(); ++it)
        {
            new QListWidgetItem((*it)->getId(), archive);
        }
    }
}

void PartieGauche::chargerListeCorbeille()
{
    NoteManager& instance = NoteManager::getInstance();

    corbeille->clear();

    for(int typeInt = ARTICLE; typeInt != FIN; typeInt++)
    {
        TypeNote type = static_cast<TypeNote>(typeInt);

        for(NoteManager::TypeIterator it = instance.begin(type, false, true); it != instance.end(); ++it)
        {
            new QListWidgetItem((*it)->getId(), corbeille);
        }
    }
}

void PartieGauche::chargerAll()
{
    chargerListeArchive();
    chargerListeNote();
    chargerListeTaches();
    chargerListeCorbeille();
}
