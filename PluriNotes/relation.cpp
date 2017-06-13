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

Couple* Relation:: findCouple(const QString& label, Note* pere, Note* fils)
{
    for(QVector<Couple*>::iterator it = couples.begin(); it != couples.end(); it++)
    {
        const Couple& coupleActu = **it;

        if(coupleActu.getLabel()== label && coupleActu.getPere() == pere && coupleActu.getFils() == fils)
            return *it;
        else throw NoteException("Couple non existant !");

    }
}

