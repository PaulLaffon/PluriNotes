#ifndef NOTE_H
#define NOTE_H


#include <QObject>

#include <QDateTime>
#include <QVector>
#include <QException>

#include "versionnote.h"
#include "versionmultimedia.h"

/*! \class Note
 *  \brief Classe gérant une note, composée de toutes ses versions
 *
 *  La classe gère toutes les informations relatives a une notes
 *
 * */

class Note : public QObject
{
    Q_OBJECT
private:
    QString id;
    QDateTime dateCreation;
    QDateTime dateModif;


    bool archive;
    bool corbeille;

    QVector<VersionNote*> versions; /*!< Tableau dynamique des version, classé par ordre croissant des dates, la plus récente est à la fin */

public:
    Note(const QString& i, QDateTime creation = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime(), bool _archive = false, bool _corbeille = false);

    const QString& getId() const {return id;}
    const QDateTime& getCreation() const {return dateCreation;}
    const QDateTime& getModif() const {return dateModif;}
    unsigned int getNumberVersion() {return versions.size();} /*!< \brief Retourne le nombre total de version */

    bool isArchive() const {return archive;}
    bool isInCorbeille() const {return corbeille;}

    void putInCorbeille() {corbeille = true;}
    void putInArchive() {archive = true;}

    void restore() {corbeille = false; archive = false;}

    VersionNote* getVersion(unsigned int i) const {return versions[i];} /*!< \brief Retourne la i-ème version de la note */
    VersionNote* getLastVersion() const {return versions.back();} /*!< \brief Retourne la version la plus récente de la note */

    void ajouterVersion(TypeNote type, QXmlStreamReader &stream); /*!< \brief Ajoute une version à partir d'un fichier XML */
    void ajouterVersion(const QString& titre, const QString& texte); /*!< \brief Ajoute une version de type Article */
    void ajouterVersion(const QString& titre,const QString& action,const int priorite,const QDateTime echeance,Status status);
    void ajouterVersion(const QString& titre,const QString& descr,const QString& path);

    TypeNote type() const {return versions.back()->type();} /*!< \brief Retourne le type de la dernière version de la note */

    void supprimerVersionVide(); /*!< \brief Supprime la dernière version de la note, dans le cas d'une version vide */

    /*! \class iterator
     *  \brief Permet d'itérer sur toutes les versions d'une note
     *
     *  Parcourt de façon standardisé de l'ensemeble des versions d'une note
     * */
    class iterator
    {
    private:
        friend class Note;
        QVector<VersionNote*>::iterator it;

    public:
        iterator(QVector<VersionNote*>::iterator i) :it(i) {}
        bool operator !=(const iterator& i) const {return it != i.it;}
        iterator& operator++() {it++; return *this;}
        VersionNote& operator*() {return **it;}
    };

    iterator begin() {return iterator(versions.begin());} /*!< \brief Retourne un iterateur sur le premier élément */
    iterator end() {return iterator(versions.end());} /*!< \brief Retourne un iterateur après le dernier élément */
};


/*!
 * \class NoteException
 * \brief Permet de lever une exception, hérite de QException
 */
class NoteException : public QException
{
private:
    QString info;

public:
    NoteException(const QString& message) : info(message) {}
    const char* what() const noexcept {return info.toStdString().c_str();}

    void raise() const {throw *this;}
    NoteException* clone() const {return new NoteException(*this);}


};

#endif // NOTE_H
