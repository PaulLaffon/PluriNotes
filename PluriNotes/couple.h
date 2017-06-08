#ifndef COUPLE_H
#define COUPLE_H

#include <QObject>
#include <QString>

#include "note.h"

class Couple : public QObject
{
    Q_OBJECT
private:
    QString label;

    Note* pere;
    Note* fils;

public:
    Couple(const QString& _label, Note* _pere, Note* _fils);

    const QString& getLabel() const {return label;}

    Note* getPere() const {return pere;}
    Note* getFils() const {return fils;}

   void writeInFile(QXmlStreamWriter& stream) const;
};

#endif // COUPLE_H
