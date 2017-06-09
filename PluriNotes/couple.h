#ifndef COUPLE_H
#define COUPLE_H

#include <QObject>
#include <QString>

#include "note.h"

/*! \class Couple
 *  \brief Couple utilisé dans les relations
 * */

class Couple : public QObject
{
    Q_OBJECT
private:
    QString label;

    Note* pere;
    Note* fils;

public:
    /*! \brief Constructeur
     *  Construit un couple avec un label, une note père et une note fils
     * */
    Couple(const QString& _label, Note* _pere, Note* _fils);

    const QString& getLabel() const {return label;}

    Note* getPere() const {return pere;}
    Note* getFils() const {return fils;}

   /*! \brief Sauvegarde le couple dans un fichier XML
    *  Sauvegarde toutes les données du couple dans un fichier XML, appelé dans la fonction saveAll() de RelationManager
    * */
   void writeInFile(QXmlStreamWriter& stream) const;
};

#endif // COUPLE_H
