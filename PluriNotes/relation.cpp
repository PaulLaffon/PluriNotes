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


void Relation::retireAllCouple()
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        delete *it;
    }
    couples.clear();
}

