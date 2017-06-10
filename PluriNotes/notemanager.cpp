#include "notemanager.h"

// De base, il n'y a pas d'instance de NoteManager
NoteManager* NoteManager::instance = nullptr;

NoteManager::NoteManager() : QObject()
{
    filename = "save.xml";
}

NoteManager::~NoteManager()
{

}

NoteManager& NoteManager::getInstance()
{
    if(NoteManager::instance == nullptr)
        NoteManager::instance = new NoteManager();

    return *NoteManager::instance;
}

void NoteManager::deleteInstance()
{
    if(NoteManager::instance != nullptr)
        delete NoteManager::instance;

    NoteManager::instance = nullptr;
}


void NoteManager::nouvelleNote(const QString& id, const QDateTime& crea, const QDateTime& modif, bool archive, bool corbeille)
{
    Note* nouvelle = new Note(id, crea, modif, archive, corbeille);
    notes.push_back(nouvelle);
}

void NoteManager::nouvelleArticle(const QString &id)
{
    if(find(id))
        emit erreur(QString("Une note avec cet id existe déjà"));
    else
    {
        Note* nouvelle = new Note(id);
        nouvelle->ajouterVersion(QString(""), QString(""));
        notes.push_back(nouvelle);

        emit creationNote();
    }
}

void NoteManager::saveAll()
{
    QFile file(filename);

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        emit erreur(QString("Fichier de sauvegarde non trouvé, impossible de sauvegarder"));
        return;
    }

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("Sauvegarde");

    for(auto it = notes.begin(); it != notes.end(); it++)
    {
        Note& actu = **it;

        stream.writeStartElement("Note");
        stream.writeTextElement("id", actu.getId());
        stream.writeTextElement("Creation", actu.getCreation().toString());
        stream.writeTextElement("Modification", actu.getModif().toString());

        stream.writeTextElement("Archive", QString::number(actu.isArchive()));
        stream.writeTextElement("Corbeille", QString::number(actu.isInCorbeille()));

        for(Note::iterator itVersion = actu.begin(); itVersion != actu.end(); ++itVersion)
        {
            (*itVersion).writeInFile(stream);
        }
        stream.writeEndElement();
    }

    // On sauvegarde toutes les relations à la fin du fichier
    RelationManager& instance = RelationManager::getInstance();
    instance.saveAll(stream);

    stream.writeEndElement();
    stream.writeEndDocument();
    file.close();
}

void NoteManager::load()
{
    QFile file(filename);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit erreur(QString("Fichier de sauvegarde non trouvé, création d'un fichier de sauvegarde"));
        return;
    }

    QXmlStreamReader stream(&file);

    RelationManager& relations = RelationManager::getInstance();

    while(!stream.atEnd() && !stream.hasError())
    {
        QXmlStreamReader::TokenType token = stream.readNext();

        if(token == QXmlStreamReader::StartDocument) continue; // Si c'est la balise de début de document

        if(token == QXmlStreamReader::StartElement) // Si c'est une balise de début d'élément
        {
            if(stream.name() == "Sauvegarde") continue; // Si c'est la balise qui englobe tout

            if(stream.name() == "Note") // Si c'est le début d'une note
            {

                // On récupère toutes les infos de la note

                QString id = VersionNote::textNextBaliseXml(stream);

                QDateTime creation = QDateTime::fromString(VersionNote::textNextBaliseXml(stream));

                QDateTime modif = QDateTime::fromString(VersionNote::textNextBaliseXml(stream));

                bool archive = VersionNote::textNextBaliseXml(stream).toInt();

                bool corbeille = VersionNote::textNextBaliseXml(stream).toInt();
                nouvelleNote(id, creation, modif, archive, corbeille);
            }

            else if(stream.name() == "Version")
            {
                // On recupère le type de la version
                TypeNote type = VersionNote::getTypeFromText(VersionNote::textNextBaliseXml(stream));

                // Cette version appartient a la dernière note ajoutée
                // On laisse la note s'occuper d'ajouter la version
                notes.back()->ajouterVersion(type, stream);
            }

            else if(stream.name() == "Relation")
            {
                QString titre = VersionNote::textNextBaliseXml(stream);
                QString description = VersionNote::textNextBaliseXml(stream);

                relations.ajouterRelation(titre, description);
            }

            else if(stream.name() == "Couple")
            {
                QString label = VersionNote::textNextBaliseXml(stream);
                QString pere = VersionNote::textNextBaliseXml(stream);
                QString fils = VersionNote::textNextBaliseXml(stream);

                relations.back()->ajouterCouple(label, find(pere), find(fils));
            }
        }
    }
}


Note *NoteManager::find(const QString &id) const
{
    for(QVector<Note*>::const_iterator it = notes.begin(); it != notes.end(); it++)
    {
        if((*it)->getId() == id)
            return *it;
    }

    return nullptr; // ici on a pas trouvé la note correspondant
}








