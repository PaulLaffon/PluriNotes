#ifndef NOTE_H
#define NOTE_H

#include <QObject>

#include <QDateTime>
#include <QVector>
#include <QException>

#include "versionnote.h"

class Note : public QObject
{
    Q_OBJECT
private:
    QString id;
    QDateTime dateCreation;
    QDateTime dateModif;


    bool archive;
    bool corbeille;

    QVector<VersionNote*> versions;

public:
    Note(const QString& i, QDateTime creation = QDateTime::currentDateTime(), QDateTime modif = QDateTime::currentDateTime(), bool _archive = false, bool _corbeille = false);

    const QString& getId() const {return id;}
    const QDateTime& getCreation() const {return dateCreation;}
    const QDateTime& getModif() const {return dateModif;}

    bool isArchive() const {return archive;}
    bool isInCorbeille() const {return corbeille;}

    VersionNote& getLastVersion() const {return *versions.back();}

    void ajouterVersion(const QString& type, QXmlStreamReader &stream); // Ajoute une version a partir d'un fichier XML
    void ajouterVersion(const QString& titre, const QString& texte); // Ajoute un article

    // Iterateur pour parcourir toutes les versions d'une note
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

    iterator begin() {return iterator(versions.begin());}
    iterator end() {return iterator(versions.end());}
};


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
