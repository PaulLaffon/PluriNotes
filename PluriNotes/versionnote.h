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

enum Status {enAttente, enCours, terminee};

class Tache : public VersionNote
{
    Q_OBJECT
private :
    QString action;
    int priorite;
    Status status;
    QDateTime echeance;

    
public :
    Tache(QXmlStreamReader &stream);
    Tache(const QString& _titre,const QString& _action,const int _priorite,const QDateTime _echeance,Status _status = enAttente, QDateTime modif = QDateTime::currentDateTime());
    ~Tache();
    QString type() const {return QString("Tache"); }
    
    void writeInFile(QXmlStreamWriter& stream) const;
    void readFromFile(QXmlStreamReader& stream);

    static const QString  StatusQString[];
    static const QString getTextStatus(int status) {return StatusQString[status];}
    static Status getStatusFromText(const QString& s);
    
    const QString& getAction() {return action; }
    int getPriorite() {return priorite; }
    const QDateTime& getEcheance() {return echeance; }
    Status getStatus() {return status; }
};

#endif // VERSIONNOTE_H
