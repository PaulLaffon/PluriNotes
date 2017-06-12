#include "relationmanager.h"

RelationManager* RelationManager::instance = nullptr;

RelationManager::RelationManager() : QObject()
{

}

RelationManager::~RelationManager()
{

}

RelationManager& RelationManager::getInstance()
{
    if(RelationManager::instance == nullptr)
        RelationManager::instance = new RelationManager();

    return *RelationManager::instance;
}

void RelationManager::deleteInstance()
{
    if(RelationManager::instance != nullptr)
        delete RelationManager::instance;

    RelationManager::instance = nullptr;
}

Relation* RelationManager::find(const QString &titre)
{
    for(QVector<Relation*>::iterator it = relations.begin(); it != relations.end(); ++it)
    {
        const Relation& relationActu = **it;

        if(relationActu.getTitre() == titre)
            return *it;
    }

    return nullptr;
}

void RelationManager::ajouterRelation(const QString &titre, const QString &descrition)
{
    if(find(titre))
        throw NoteException("Une relation avec le même titre existe déjà");

    relations.push_back(new Relation(titre, descrition));
}

void RelationManager::ajouterCouple (const QString& titre,const QString& id, Note* note1,Note* note2)
{
    Relation* relation = find(id);
    relation->ajoutCouple(titre,note1,note2);
}

// Sauvegarde les relations en utilisant le QXmlStreamWriter de NoteManager
// Les relations sont sauvegardés à la fin du fichier XML
void RelationManager::saveAll(QXmlStreamWriter &stream)
{
    for(auto it = relations.begin(); it != relations.end(); ++it)
    {
        Relation& actu = **it;

        if(actu.isReference())
            stream.writeStartElement("Reference");
        else
            stream.writeStartElement("Relation");

        stream.writeTextElement("Titre", actu.getTitre());
        stream.writeTextElement("Description", actu.getDescription());

        for(Relation::iterator itCouple = actu.begin(); itCouple != actu.end(); ++itCouple)
        {
            (*itCouple).writeInFile(stream);
        }
        stream.writeEndElement();
    }
}









