#include "note.h"

Note::Note(const QString& i, QDateTime creation, QDateTime modif, bool _archive, bool _corbeille)
    : QObject(), id(i), dateCreation(creation), dateModif(modif), archive(_archive), corbeille(_corbeille)
{

}

void Note::ajouterVersion(TypeNote type, QXmlStreamReader& stream)
{
    VersionNote* nouveau;

    // Ici on gère le type de la version qu'on veut ajotuer
    if(type == ARTICLE)
        nouveau = new Article(stream);
    else
        throw NoteException(QString("Type de version non reconnu"));

    // On ajoute la nouvelle version à la fin du tableau de version
    versions.push_back(nouveau);
}

// Ajoute un une versionNote de type article
void Note::ajouterVersion(const QString &titre, const QString &texte)
{
    Article* nouveau = new Article(titre, texte);
    versions.push_back(nouveau);
}
