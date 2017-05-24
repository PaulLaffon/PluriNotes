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

    stream.writeTextElement("Type", type());
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
