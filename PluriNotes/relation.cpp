#include "relation.h"

Relation::Relation(const QString& _titre, const QString& _description)
    : QObject(), titre(_titre), description(_description)
{

}

void Relation::ajoutCouple(const QString& label, Note* pere, Note* fils)
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        const Couple& coupleActu = **it;

        if(coupleActu.getPere() == pere && coupleActu.getFils() == fils)
            throw NoteException("Couple dejà présent dans la relation !");
    }

    couples.push_back(new Couple(label, pere, fils));
}

Couple* Relation::find(Note *pere, Note *fils)
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        Couple* coupleActu = *it;
        if(coupleActu->getPere() == pere && coupleActu->getFils() == fils)
            return coupleActu;
    }

    return nullptr;
}

void Relation::retireCouple(Note *n)
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        if((*it)->getPere() == n || (*it)->getFils() == n)
        {
            delete *it;
            couples.erase(it);
            it--;
        }
    }
}

void Relation::retireAllCouple()
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        delete *it;
    }
    couples.clear();
}


bool Relation::isReferenced(Note *n) const
{
    for(QVector<Couple*>::const_iterator it = couples.begin(); it != couples.end(); it++)
    {
        if((*it)->getFils() == n)
            return true;
    }
    return false;
}

Couple* Relation:: findCouple(const QString& label, Note* pere, Note* fils)
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        const Couple& coupleActu = **it;

        if(coupleActu.getLabel()== label && coupleActu.getPere() == pere && coupleActu.getFils() == fils)
            return *it;
        else throw NoteException("Couple non existant !");

    }
    return nullptr;
}
