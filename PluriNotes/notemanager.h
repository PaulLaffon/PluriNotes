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


    void nouvelleNote(const QString& id, const QDateTime& crea, const QDateTime& modif, bool archive, bool corbeille);

    Note* find(const QString& id) const;
};

#endif // NOTEMANAGER_H
