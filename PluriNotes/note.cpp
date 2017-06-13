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
    else if (type == TACHE)
        nouveau = new Tache(stream);
    else if(type == MEDIA_IMG)
        nouveau = new Image(stream);
    else if(type == MEDIA_VID)
        nouveau = new Video(stream);
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

void Note::ajouterVersion(const QString& titre,const QString& action,const int priorite,const QDateTime echeance,Status status)
{
    Tache* nouveau = new Tache(titre,action,priorite,echeance,status);
    versions.push_back(nouveau);
}

void Note::ajouterVersion(const QString &titre, const QString &descr, const QString& path)
{
    Image* nouveau = new Image(titre, descr, path);
    versions.push_back(nouveau);
}

void Note::ajouterVersionVideo(const QString &titre, const QString &descr, const QString &path)
{
    Video* nouveau = new Video(titre, descr, path);
    versions.push_back(nouveau);
}

// Supprime la dernière version, est utilisé pour supprimer les versions vide qui sont créer à la création de la note
void Note::supprimerVersionVide()
{
    if(!versions.empty() && versions.back()->getTitre() == QString(""))
    {
        delete versions.back();
        versions.pop_back();
    }
}
