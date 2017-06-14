#ifndef RELATIONMANAGER_H
#define RELATIONMANAGER_H

#include <QObject>
#include <QVector>

#include "relation.h"
#include "reference.h"

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

    Relation* find(const QString& titre); /*!< \brief Renvoie un pointeur sur la relation correspondant au titre, ou nullptr si elle n'existe pas */

    Relation* back() const {return relations.back();} /*!< \brief Renvoie la dernière Relation créé, utilisé dans la fonction load() */

    void ajouterReference(); /*!< \brief Permet d'ajouter une référence sans aucun couple */

    bool isReferenced(Note *n); /*!< \brief Indique si la relation est référencée par la relation Référence */

    /*! \class iterator
     *  \brief Iterateur pour parcourir toutes les relations, sauf la relation référence qui n'est pas prise en compte
     * */
    class iterator
    {
    private:
        friend class RelationManager;
        QVector<Relation*>::iterator it;
        int restant;

    public:
        iterator(QVector<Relation*>::iterator i, int r) : it(i), restant(r) {
            if(restant > 0 && (*it)->isReference()) {
                restant--;
                it++;
            }
        }

        bool operator !=(const iterator& i) const {return it != i.it;}
        iterator& operator++() {
            it++; restant--;
            if(restant > 0 && (*it)->isReference()) {
                restant--;
                it++;
            }
            return *this;
        }
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
        iteratorPredSucc(QVector<Relation*>::iterator i, Note* n,bool succ, int r) : it(i), note(n), successeur(succ), restant(r)
        {
            if(restant > 0)
                itR = (*it)->begin(n, succ);

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

        Relation* getRelation() const {return *it;}
    };

    iterator begin() {return iterator(relations.begin(), relations.size());}
    iterator end() {return iterator(relations.end(), 0);}

    iteratorPredSucc begin(Note* n, bool successeur) {return iteratorPredSucc(relations.begin(), n, successeur, relations.size());}
    iteratorPredSucc endSuccPred() {return iteratorPredSucc();}
    public slots:
        void ajouterRelation(const QString& titre, const QString& descrition); /*!< \brief Permet d'ajouter une relation sans aucun Couple */
        void ajouterCouple (const QString& titre,const QString& id, Note* note1,Note* note2); /*!< \brief Permet d'ajouter un couple à une relation */

        void ajouterCoupleReference(Note* pere, Note* fils);

    signals:
        void creationRelation();
        void erreur(QString);

};

#endif // RELATIONMANAGER_H
