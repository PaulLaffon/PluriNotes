#ifndef RELATION_H
#define RELATION_H

#include <QObject>
#include <QString>
#include <QVector>

#include "couple.h"

/*! \class Relation
 *  \brief Contient toutes les informations d'une relation, est composé de Couple
 * */

class Relation : public QObject
{
    Q_OBJECT
private:
    QString titre;
    QString description;

    QVector<Couple*> couples; /*!< Contient tous les couples de la Relation */


public:
    Relation(const QString& _titre, const QString& _description);

    void ajoutCouple(const QString& label, Note* pere, Note* fils); /*!< \brief Ajoute un couple à la Relation */


    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}

    Couple* find(Note* pere, Note* fils); /*!< \brief Recherche ce couple dans la liste des couples, renvoie le couple ou nullptr si il n'existe pas */

    void retireAllCouple(); /*!< \brief Retire tous les couples de la relation */

    virtual bool isReference() const {return false;} /*!< \brief Indique si la relation est une Reference */

    /*! \class iterator
     *  \brief Iterateur pour parcourir tous les couples d'une relation
     * */
    class iterator
    {
    private:
        friend class Relation;
        QVector<Couple*>::iterator it;

    public:
        iterator(QVector<Couple*>::iterator i) : it(i) {}

        bool operator !=(const iterator& i) const {return it != i.it;}
        iterator& operator++() {it++; return *this;}
        Couple& operator*() {return **it;}
    };

    /*! \class iteratorSuccPred
     *  \brief Iterateur pour parcourir tous les successeurs ou predecesseurs d'une note dans une relation
     * */
    class iteratorSuccPred
    {
    private:
        friend class Relation;
        QVector<Couple*>::iterator it;
        Note *note;
        bool successeur; /*!< \brief Si il est vrai, on parcourt les successeur, sinon les prédécesseur */
        int restant;

    public:
        iteratorSuccPred() : note(nullptr), restant(0) {}
        iteratorSuccPred(QVector<Couple*>::iterator i, Note *n, bool succ, int r) :it(i), note(n), successeur(succ), restant(r)
        {
            if(successeur) {
                while (restant > 0 && (*it)->getPere() != note) {
                    it++;
                    restant--;
                }
            }
            else {
                while (restant > 0 && (*it)->getFils() != note) {
                    it++;
                    restant--;
                }
            }
        }

        bool operator !=(const iteratorSuccPred& i) const {return it != i.it;}

        iteratorSuccPred& operator++() {
            ++it; restant--;
            if(successeur) {
                while (restant > 0 && (*it)->getPere() != note) {
                    it++;
                    restant--;
                }
            }
            else {
                while (restant > 0 && (*it)->getFils() != note) {
                    it++;
                    restant--;
                }
            }
            return *this;
        }

        Note* operator*() {
            if(successeur)
                return (*it)->getFils();

            return (*it)->getPere();
        }
    };

    iterator begin() {return iterator(couples.begin());}
    iterator end() {return iterator(couples.end());}

    iteratorSuccPred begin(Note* n, bool successeur) {return iteratorSuccPred(couples.begin(), n, successeur, couples.size());}
    iteratorSuccPred endSuccPred() {return iteratorSuccPred(couples.end(), nullptr, true, 0);}
};

#endif // RELATION_H
