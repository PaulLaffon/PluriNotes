#ifndef REFERENCE_H
#define REFERENCE_H

#include "relation.h"

/*! \class Reference
 *  \brief C'est une relation particulière, elle hérite de Relation
 * */
class Reference : public Relation
{
    Q_OBJECT
public:
    Reference(const QString& _titre, const QString& _description);

    bool isReference() {return true;} /*!< \brief Indique si la relation est une Reference */

signals:

public slots:
};

#endif // REFERENCE_H
