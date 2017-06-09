#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <QObject>
#include <QVector>

#include "relation.h"

/*! \class RelationManager
 *  \brief Singleton factory pour les Relation
 * */

class RelationManager : public QObject
{
    Q_OBJECT
private:
    QVector<Relation*> relations; /*!< Tableau contenant toutes les Relation */

    RelationManager(); /*!< \brief Singleton, on ne peut ni créer ni détruire un objet de cette classe */
    ~RelationManager();
    RelationManager(const RelationManager& m);
    RelationManager& operator=(const RelationManager& m);

    static RelationManager* instance;


public:
    static RelationManager& getInstance(); /*!< Récupère l'instance de RelationManager */
    static void deleteInstance(); /*!< Supprime l'instance de la classe */

    void saveAll(QXmlStreamWriter& stream); /*!< \brief Sauvegarde toutes les relations dans un fichier XML, est appelé par saveAll() de NoteManager */
    void load(QXmlStreamReader& stream); /*!< \brief Charge les relations à partir d'une fichier XML, est appelé par load() de NoteManager */

    void ajouterRelation(const QString& titre, const QString& descrition); /*!< \brief Permet d'ajouter une relation sans aucun Couple */

    Relation* find(const QString& titre); /*!< \brief Renvoie un pointeur sur la relation correspondant au titre, ou nullptr si elle n'existe pas */

    Relation* back() const {return relations.back();} /*!< \brief Renvoie la dernière Relation créé, utilisé dans la fonction load() */
};

#endif // RELATIONMANAGER_H
