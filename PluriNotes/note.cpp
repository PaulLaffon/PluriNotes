#include "note.h"

Note::Note(const QString& i, QDateTime creation, QDateTime modif, bool _archive, bool _corbeille)
    : QObject(), id(i), dateCreation(creation), dateModif(modif), archive(_archive), corbeille(_corbeille)
{

}

void Note::ajouterVersion(const QString &type, QXmlStreamReader& stream)
{
    VersionNote* nouveau;

    if(type == "Article")
        nouveau = new Article(stream);
    else
        throw NoteException(QString("Type de version non reconnu"));

    versions.push_back(nouveau);
}
