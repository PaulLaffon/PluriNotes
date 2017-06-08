#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <QObject>
#include <QVector>

#include "relation.h"

class RelationManager : public QObject
{
    Q_OBJECT
private:
    QVector<Relation*> relations;

    // Singleton, on ne peut ni créer ni détruire un objet de cette classe

    RelationManager();
    ~RelationManager();
    RelationManager(const RelationManager& m);
    RelationManager& operator=(const RelationManager& m);

    static RelationManager* instance;


public:
    static RelationManager& getInstance();
    static void deleteInstance();

    void saveAll(QXmlStreamWriter& stream);
    void load(QXmlStreamReader& stream);

    void ajouterRelation(const QString& titre, const QString& descrition);

    Relation* find(const QString& titre); // Trouve une relation par rapport au titre

    Relation* back() const {return relations.back();}
};

#endif // RELATIONMANAGER_H
