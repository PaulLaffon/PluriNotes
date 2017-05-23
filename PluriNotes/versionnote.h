#ifndef VERSIONNOTE_H
#define VERSIONNOTE_H

#include <QObject>
#include <QXmlStreamWriter>

#include <QString>
#include <QDateTime>

class VersionNote : public QObject
{
    Q_OBJECT
protected:
    QString titre;
    QDateTime dateModif;

public:
    VersionNote();
    VersionNote(const QString& _titre, QDateTime modif = QDateTime::currentDateTime());

    virtual ~VersionNote();
    virtual QString type() const = 0;
    virtual void writeInFile(QXmlStreamWriter& stream) const = 0;
    virtual void readFromFile(QXmlStreamReader& stream) = 0;


    const QString& getTitre() const {return titre;}
};


class Article : public VersionNote
{
    Q_OBJECT
private:
    QString texte;

public:
    Article(QXmlStreamReader& stream);
    Article(const QString& _titre, const QString& _texte, QDateTime modif = QDateTime::currentDateTime());
    ~Article();
    QString type() const {return QString("Article");}

    void writeInFile(QXmlStreamWriter& stream) const;
    void readFromFile(QXmlStreamReader& stream);


    const QString& getTexte() const {return texte;}
};

#endif // VERSIONNOTE_H
