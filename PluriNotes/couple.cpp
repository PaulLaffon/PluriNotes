#include "couple.h"

Couple::Couple(const QString &_label, Note *_pere, Note *_fils)
    : QObject(), label(_label), pere(_pere), fils(_fils)
{

}

void Couple::writeInFile(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("Couple");

    stream.writeTextElement("Label", label);
    stream.writeTextElement("IdPere", pere->getId());
    stream.writeTextElement("IdFils", fils->getId());

    stream.writeEndElement();
}
