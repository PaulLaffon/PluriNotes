#include "versionnote.h"

VersionNote::VersionNote(const QString& _titre, QDateTime modif)
    : QObject(), titre(_titre), dateModif(modif)
{

}
VersionNote::VersionNote() : QObject()
{

}

QString VersionNote::textNextBaliseXml(QXmlStreamReader &stream)
{
    // On lit les valeur jusqu'a arrivé au début de la prochaine balise
    while(stream.readNext() != QXmlStreamReader::StartElement);
    stream.readNext(); // On lit le texte de la balise XML
    return stream.text().toString(); // On retourne le texte
}

Article::Article(const QString &_titre, const QString &_texte, QDateTime modif)
    :VersionNote(_titre, modif), texte(_texte)
{

}

Article::Article(QXmlStreamReader &stream) : VersionNote()
{
    readFromFile(stream);
}

VersionNote::~VersionNote()
{

}

Article::~Article()
{

}

void Article::writeInFile(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("Version");

    stream.writeTextElement("Type", textFromType(type()));
    stream.writeTextElement("Date", dateModif.toString());
    stream.writeTextElement("Titre", titre);
    stream.writeTextElement("Texte", texte);

    stream.writeEndElement();
}

void Article::readFromFile(QXmlStreamReader &stream)
{
    dateModif = QDateTime::fromString(VersionNote::textNextBaliseXml(stream));
    titre = VersionNote::textNextBaliseXml(stream);
    texte = VersionNote::textNextBaliseXml(stream);
}

const QString VersionNote::typeQString[] = {QString("Article"), QString("Tache")};

const QString Tache::StatusQString[] = {QString("En attente"), QString("En cours"), QString("Terminee")};

const QString Multimedia::TypeMultimediaQString[] = {QString("image"), QString("audio"), QString("video")};

TypeNote VersionNote::getTypeFromText(const QString &s)
{
    if(s == QString("Article"))
        return ARTICLE;

    return TACHE;
}

Status Tache::getStatusFromText(const QString& s)
{
    if(s == QString("En attente"))
        return enAttente;
    else if(s == QString("En cours"))
        return enCours;

    return terminee;
}

TypeMultimedia Multimedia::getTypeMultimediaFromText(const QString& t)
{
    if(t == QString("image"))
        return image;
    else if(t == QString("audio"))
        return audio;

    return video;
}

Tache::Tache(QXmlStreamReader& stream) : VersionNote()
{
    readFromFile(stream);
}

Tache::Tache(const QString& _titre, const QString& _action, int _priorite, QDateTime _echeance,Status _status, QDateTime modif) :
    VersionNote(_titre,modif),action(_action),priorite(_priorite),status(_status), echeance(_echeance)
{
        
}

Tache::~Tache()
{
    
}

void Tache::writeInFile(QXmlStreamWriter& stream) const
{
    stream.writeStartElement("Version");

    stream.writeTextElement("Type", textFromType(type()));
    stream.writeTextElement("Date", dateModif.toString());
    stream.writeTextElement("Titre", titre);
    stream.writeTextElement("Action", action);
    stream.writeTextElement("Priorite", QString::number(priorite));
    stream.writeTextElement("Echeance", echeance.toString());
    stream.writeTextElement("Statut", getTextStatus(status));

    stream.writeEndElement();
}

void Tache::readFromFile(QXmlStreamReader& stream)
{
    dateModif = QDateTime::fromString(VersionNote::textNextBaliseXml(stream));
    titre = VersionNote::textNextBaliseXml(stream);
    action = VersionNote::textNextBaliseXml(stream);
    priorite = VersionNote::textNextBaliseXml(stream).toInt();
    echeance = QDateTime::fromString(VersionNote::textNextBaliseXml(stream));
    status = getStatusFromText(VersionNote::textNextBaliseXml(stream));
}

void Tache::setStatusEnAttente(bool checked)
{
    if (checked)
        status=enAttente;
}

void Tache::setStatusEnCours(bool checked)
{
    if (checked)
        status=enCours;
}

void Tache::setStatusTerminee(bool checked)
{
    if (checked)
        status=terminee;
}

Multimedia::Multimedia(const QString &_titre, const QString &_descr, const QString _file, QDateTime modif) :
    VersionNote(_titre,modif),description(_descr),file(_file)
{

}

Multimedia::Multimedia(QXmlStreamReader &stream) : VersionNote()
{
    readFromFile(stream);
}

Multimedia::~Multimedia()
{

}

void Multimedia::writeInFile(QXmlStreamWriter& stream) const
{
    stream.writeStartElement("Version");

    stream.writeTextElement("Type", textFromType(type()));
    stream.writeTextElement("Date", dateModif.toString());
    stream.writeTextElement("Titre", titre);
    stream.writeTextElement("Description", description);
    stream.writeTextElement("Fichier", file);
    stream.writeTextElement("TypeMedia",getTextTypeMultimedia(typeMedia));


    stream.writeEndElement();
}

void Multimedia::readFromFile(QXmlStreamReader& stream)
{
    dateModif = QDateTime::fromString(VersionNote::textNextBaliseXml(stream));
    titre = VersionNote::textNextBaliseXml(stream);
    description = VersionNote::textNextBaliseXml(stream);
    file = VersionNote::textNextBaliseXml(stream);
    typeMedia = getTypeMultimediaFromText(VersionNote::textNextBaliseXml(stream));
}

