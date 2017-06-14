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

void NoteManager::nouvelleTache(const QString& id)
{
    if(find(id))
        emit erreur(QString("Une note avec cet id existe déjà"));
    else
    {
        Note* nouvelle = new Note(id);
        nouvelle->ajouterVersion(QString(""),QString(""),0,QDateTime::currentDateTime(),enAttente);
        notes.push_back(nouvelle);

        emit creationNote();
    }
}

void NoteManager::nouvelleImage(const QString& id)
{
    if(find(id))
        emit erreur(QString("Une note avec cet id existe déjà"));
    else
    {
        Note* nouvelle = new Note(id);
        nouvelle->ajouterVersion(QString(""),QString(""),QString(""));
        notes.push_back(nouvelle);

        emit creationNote();
    }
}

void NoteManager::nouvelleVideo(const QString &id)
{
    if(find(id))
        emit erreur(QString("Une note avec cet id existe déjà"));
    else
    {
        Note* nouvelle = new Note(id);
        nouvelle->ajouterVersionVideo(QString(""),QString(""),QString(""));
        notes.push_back(nouvelle);

        emit creationNote();
    }
}

void NoteManager::nouvelleAudio(const QString &id)
{
    if(find(id))
        emit erreur(QString("Une note avec cet id existe déjà"));
    else
    {
        Note* nouvelle = new Note(id);
        nouvelle->ajouterVersionAudio(QString(""),QString(""),QString(""));
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

    RelationManager& relations = RelationManager::getInstance();

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        emit erreur(QString("Fichier de sauvegarde non trouvé, création d'un fichier de sauvegarde"));
        relations.ajouterReference();
        return;
    }

    QXmlStreamReader stream(&file);

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
            else if(stream.name() == "Reference")
            {
                VersionNote::textNextBaliseXml(stream); // On lit le titre mais on ne s'en sert pas
                VersionNote::textNextBaliseXml(stream); // On lit la description mais on ne s'en sert pas

                relations.ajouterReference();
            }

            else if(stream.name() == "Couple")
            {
                QString label = VersionNote::textNextBaliseXml(stream);
                QString pere = VersionNote::textNextBaliseXml(stream);
                QString fils = VersionNote::textNextBaliseXml(stream);

                relations.back()->ajoutCouple(label, find(pere), find(fils));
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

void NoteManager::actualiserReference()
{
    RelationManager& relations = RelationManager::getInstance();

    Relation *reference = relations.find("Référence");
    reference->retireAllCouple();

    // On parcourt chacune des notes
    for(QVector<Note*>::iterator it = notes.begin(); it != notes.end(); ++it)
    {
        QString text = (*it)->getLastVersion()->getDescription(); // On récupère le texte où les références peuvent apparaitre

        QStringList listes = text.split("\\ref{"); // On sépare chaque élément du texte

        QStringList::iterator itString = listes.begin();
        itString++; // On ne s'intéresse pas au premier, car il ne contient pas de références

        for(; itString != listes.end(); itString++) // Pour chaque séparation du texte
        {
            QString s = *itString;

            int indice = 0;
            while(indice < s.size() && s[indice] != '}') indice++; // On prends l'indice de la fin de l'id

            QString id = s.left(indice); // On extrait l'id

            Note* pere = *it;
            Note* fils = find(id);

            if(fils)
                relations.ajouterCoupleReference(pere, fils);
        }
    }
}


void NoteManager::clicSupprimerNote(Note *n)
{
    RelationManager& relations = RelationManager::getInstance();

    if(relations.isReferenced(n))
        n->putInArchive();
    else
        n->putInCorbeille();

    emit creationNote();
}


void NoteManager::restaurerNote(Note *n)
{
    n->restore();

    emit creationNote();
}

void NoteManager::supprimerNote(const QString &id)
{
    // On considère que la note n'est pas référencée par une Référence
    RelationManager& relations = RelationManager::getInstance();
    Note* n = find(id);

    for(RelationManager::iterator it = relations.begin(); it != relations.end(); ++it)
    {
        (*it).retireCouple(n);
    }

    for(QVector<Note*>::iterator it = notes.begin(); it != notes.end(); it++)
    {
        if(*it == n)
        {
            delete n;
            notes.erase(it);
            it--;
        }
    }
}

void NoteManager::supprimerCorbeille()
{
    for(QVector<Note*>::iterator it = notes.begin(); it != notes.end(); it++)
    {
        if((*it)->isInCorbeille())
        {
            supprimerNote((*it)->getId());
            it--;
        }
    }
}

bool NoteManager::corbeilleVide()
{
    for(QVector<Note*>::iterator it = notes.begin(); it != notes.end(); it++)
    {
        if((*it)->isInCorbeille())
            return false;
    }

    return true;
}
