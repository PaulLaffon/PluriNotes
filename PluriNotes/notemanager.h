#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QVector>
#include <QString>
#include <QDebug>

#include "note.h"

class NoteManager : public QObject
{
    Q_OBJECT
private:
    QVector<Note*> notes;

    QString filename;

    // Singleton, on ne peut pas créer ni détruire un objet de cette classe
    NoteManager();
    ~NoteManager();
    NoteManager(const NoteManager& m);
    NoteManager& operator=(const NoteManager& m);

    static NoteManager* instance;

public:
    static NoteManager& getInstance();
    static void deleteInstance();

    void load();
    void saveAll() const;

    // Cree une nouvelle note sans version, elle n'as pas de type
    // Idéalement, il faudrait crée une note avec un type et une version de base
    void nouvelleNote(const QString& id, const QDateTime& crea, const QDateTime& modif, bool archive, bool corbeille);

    // Renvoie la note correspondant à l'id
    Note* find(const QString& id) const;


    // Itérateur sur le type d'une note, ex begin(ARTICLE) ==> Iterateur sur tous les articles
    class TypeIterator
    {
    private:
        friend class NoteManager;
        QVector<Note*>::iterator it;
        TypeNote type;
        int restant;

    public:
        TypeIterator(QVector<Note*>::iterator i, TypeNote t, int r) :it(i), type(t), restant(r)
        {
            while(restant > 0 && (*it)->type() != type) {
                it++;
                restant--;
            }
        }

        bool operator !=(const TypeIterator& i) const {return it != i.it;}
        TypeIterator& operator++()
        {
            it++; restant--;
            while(restant > 0 && (*it)->type() != type) {
                it++;
                restant--;
            }
            return *this;
        }

        Note* operator*() {return *it;}

    };


    TypeIterator begin(TypeNote type) {return TypeIterator(notes.begin(), type, notes.size());}
    // Ici le type d'itérateur n'as pas d'importance
    TypeIterator end() {return TypeIterator(notes.end(), ARTICLE, 0);}
};

#endif // NOTEMANAGER_H
