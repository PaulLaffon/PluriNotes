#include "versionmultimedia.h"

MultiMedia::MultiMedia(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif)
    : Article(_titre, _descr, modif), filepath(_file)
{

}

MultiMedia::MultiMedia(QXmlStreamReader &stream) :Article(stream)
{
    filepath = VersionNote::textNextBaliseXml(stream);
}

MultiMedia::~MultiMedia()
{

}

Image::Image(const QString &_titre, const QString &_descr, const QString _file, QDateTime modif)
    :MultiMedia(_titre, _descr, _file, modif)
{

}

Image::Image(QXmlStreamReader &stream) :MultiMedia(stream)
{

}

Image::~Image()
{

}

void Image::writeInFile(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("Version");

    stream.writeTextElement("Type", textFromType(type()));
    stream.writeTextElement("Date", dateModif.toString());
    stream.writeTextElement("Titre", titre);
    stream.writeTextElement("Description", texte);
    stream.writeTextElement("Fichier", filepath);

    stream.writeEndElement();
}

Video::Video(const QString &_titre, const QString &_descr, const QString _file, QDateTime modif)
    :MultiMedia(_titre, _descr, _file, modif)
{

}

Video::Video(QXmlStreamReader &stream) :MultiMedia(stream)
{

}

Video::~Video()
{

}

void Video::writeInFile(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("Version");

    stream.writeTextElement("Type", textFromType(type()));
    stream.writeTextElement("Date", dateModif.toString());
    stream.writeTextElement("Titre", titre);
    stream.writeTextElement("Description", texte);
    stream.writeTextElement("Fichier", filepath);

    stream.writeEndElement();
}

Audio::Audio(const QString &_titre, const QString &_descr, const QString _file, QDateTime modif)
    :MultiMedia(_titre, _descr, _file, modif)
{

}

Audio::Audio(QXmlStreamReader &stream) :MultiMedia(stream)
{

}

Audio::~Audio()
{

}

void Audio::writeInFile(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("Version");

    stream.writeTextElement("Type", textFromType(type()));
    stream.writeTextElement("Date", dateModif.toString());
    stream.writeTextElement("Titre", titre);
    stream.writeTextElement("Description", texte);
    stream.writeTextElement("Fichier", filepath);

    stream.writeEndElement();
}


