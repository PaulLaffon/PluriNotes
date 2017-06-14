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
        new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(ARTICLE) + QString(")"), noteActive);
    }

    for(NoteManager::TypeIterator it = instance.begin(MEDIA_IMG); it != instance.end(); ++it)
        new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(MEDIA_IMG) + QString(")"), noteActive);

    for(NoteManager::TypeIterator it = instance.begin(MEDIA_VID); it != instance.end(); ++it)
        new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(MEDIA_VID) + QString(")"), noteActive);

    for(NoteManager::TypeIterator it = instance.begin(MEDIA_AUDIO); it != instance.end(); ++it)
        new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(MEDIA_AUDIO) + QString(")"), noteActive);
}

void PartieGauche::chargerListeTaches()
{
    NoteManager& instance = NoteManager::getInstance();

    tache->clear();

    for(NoteManager::TypeIterator it = instance.begin(TACHE); it != instance.end();++it)
    {
        new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(TACHE) + QString(")"), tache);
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
            new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(type) + QString(")"), archive);
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
            new QListWidgetItem((*it)->getId() + QString(" (") + VersionNote::textFromType(type) + QString(")"), corbeille);
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
