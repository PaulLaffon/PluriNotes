#ifndef RELATION_H
#define RELATION_H

#include <QObject>
#include <QString>
#include <QVector>

#include "couple.h"

class Relation : public QObject
{
    Q_OBJECT
private:
    QString titre;
    QString description;

    QVector<Couple*> couples; // Tous les couples de la relation


public:
    Relation(const QString& _titre, const QString& _description);

    void ajouterCouple(const QString& label, Note* pere, Note* fils);


    const QString& getTitre() const {return titre;}
    const QString& getDescription() const {return description;}


    virtual bool isReference() const {return false;}

    // Iterateur pour parcourir tous les couples d'une relation
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

    iterator begin() {return iterator(couples.begin());}
    iterator end() {return iterator(couples.end());}

};

#endif // RELATION_H
