#ifndef VERSIONNOTE_H
#define VERSIONNOTE_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QString>
#include <QDateTime>

enum Status {enAttente, enCours, terminee};
enum TypeNote {ARTICLE, TACHE};

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
    virtual TypeNote type() const = 0;   // Renvoie le type de la version
    virtual void writeInFile(QXmlStreamWriter& stream) const = 0; // Ecrit le contenu dans le stream
    virtual void readFromFile(QXmlStreamReader& stream) = 0; // Se charge depuis le stream

    static QString textNextBaliseXml(QXmlStreamReader& stream); // Récupère le texte de la balise XML suivante

    static const QString typeQString[];
    static const QString& textFromType(TypeNote type) {return typeQString[type];}
    static TypeNote getTypeFromText(const QString& s); // Obtenir le type en QString

    const QString& getTitre() const {return titre;}
    const QDateTime& getModif() const {return dateModif;}
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
    TypeNote type() const {return ARTICLE;}

    void writeInFile(QXmlStreamWriter& stream) const;
    void readFromFile(QXmlStreamReader& stream);


    const QString& getTexte() const {return texte;}
};



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
    TypeNote type() const {return TACHE;}
    
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
