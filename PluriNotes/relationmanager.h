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

    /*! \class iterator
     *  \brief Iterateur pour parcourir toutes les relations
     * */
    class iterator
    {
    private:
        friend class RelationManager;
        QVector<Relation*>::iterator it;

    public:
        iterator(QVector<Relation*>::iterator i) : it(i) {}

        bool operator !=(const iterator& i) const {return it != i.it;}
        iterator& operator++() {it++; return *this;}
        Relation& operator*() {return **it;}
    };

    /*! \class iteratorSuccPred
     *  \brief Iterateur pour parcourir tous les successeurs ou predecesseurs d'une note
     * */
    class iteratorPredSucc
    {
    private:
        friend class RelationManager;
        QVector<Relation*>::iterator it;
        Relation::iteratorSuccPred itR;
        Note *note;
        bool successeur; /*!< \brief Si il est vrai, on parcourt les successeur, sinon les prédécesseur */
        int restant;

    public:
        iteratorPredSucc() : note(nullptr), restant(0) {}
        iteratorPredSucc(QVector<Relation*>::iterator i, Note* n,bool succ, int r) : it(i), itR((*it)->begin(n, succ)), note(n), successeur(succ), restant(r)
        {
            while(restant > 0 && !(itR != (*it)->endSuccPred())) {
                ++it;
                restant--;

                if(restant > 0)
                    itR = (*it)->begin(note, successeur);
            }
        }

        bool operator !=(const iteratorPredSucc& i) {return restant != i.restant;}

        iteratorPredSucc& operator++() {
            ++itR;
            while(restant > 0 && !(itR != (*it)->endSuccPred())) {
                ++it;
                restant--;

                if(restant > 0)
                    itR = (*it)->begin(note, successeur);
            }
            return *this;
        }

        Note* operator*() {
            return *itR;
        }
    };

    iterator begin() {return iterator(relations.begin());}
    iterator end() {return iterator(relations.end());}

    iteratorPredSucc begin(Note* n, bool successeur) {return iteratorPredSucc(relations.begin(), n, successeur, relations.size());}
    iteratorPredSucc endSuccPred() {return iteratorPredSucc();}
};

#endif // RELATIONMANAGER_H
