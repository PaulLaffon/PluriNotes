#ifndef VERSIONNOTE_H
#define VERSIONNOTE_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

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

    static QString textNextBaliseXml(QXmlStreamReader& stream);

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

typedef enum {QString("En attente"), QString("En cours"), QString("Terminee")} Status;

class Tache : public VersionNote
{
    Q_OBJECT
private :
    QString action;
    int priorite;
    QDateTime echeance;
    Status status;
    
public :
    Tache(QXmlStreamReader &stream);
    Tache(const QString& _titre,const Qstring& _action,const int _priorite,const QDateTime _echeance,Status _status = QString("En attente"), QDateTime modif = QDateTime::currentDateTime());
    ~Tache();
    QString type() const {return QString("Tache"); }
    
    void writeInFile(QXmlStreamWriter& stream) const;
    void readFromFile(QXmlStreamReader& stream);
    
    const QString& getAction() {return action; }
    const int getPriorite() {return priorite; }
    const QDateTime& getEcheance {return echeance; }
    const Status& getStatus {return status; }
};

#endif // VERSIONNOTE_H
