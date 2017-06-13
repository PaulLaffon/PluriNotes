#ifndef VERSIONNOTE_H
#define VERSIONNOTE_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QString>
#include <QDateTime>

/*! \enum Status
 *  \brief Enumération des différents status d'une Tache
 */
enum Status {enAttente, enCours, terminee};

/*! \enum TypeNote
 *  \brief Enumération des différents type de Note
 */
enum TypeNote {ARTICLE,MULTIMEDIA,TACHE,FIN};

/*! \enum TypeMultimedia
 *  \brief Enumération des différents types de multimédia
 */
enum TypeMultimedia {image, audio, video};

/*! \class VersionNote
 *  \brief Classe abstraite qui regroupe les partie communes d'une version d'une Note
*/
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
    virtual TypeNote type() const = 0;   /*!< \brief Renvoie le type de la version */
    virtual void writeInFile(QXmlStreamWriter& stream) const = 0; /*!< \brief Ecrit le contenu de la version dans un fichier XML */
    virtual void readFromFile(QXmlStreamReader& stream) = 0; /*!< \brief Se charge depuis une fichier XML */

    static QString textNextBaliseXml(QXmlStreamReader& stream); /*!< \brief Récupère le texte de la balise XML suivante */

    static const QString typeQString[];
    static const QString& textFromType(TypeNote type) {return typeQString[type];} /*!< \brief Retourne le type de la note en QString */
    static TypeNote getTypeFromText(const QString& s); /*!< \brief Obtenir le type de la note à partir d'un QString */

    const QString& getTitre() const {return titre;}
    const QDateTime& getModif() const {return dateModif;}

    virtual const QString& getDescription() const = 0;
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
    TypeNote type() const {return ARTICLE;}  /*!< \brief Renvoie le type de la version */

    void writeInFile(QXmlStreamWriter& stream) const; /*!< \brief Redéfinition, ecrit le contenu de la version dans un fichier XML */
    void readFromFile(QXmlStreamReader& stream);  /*!< \brief Redéfinition, se charge depuis une fichier XML */

    const QString& getDescription() const {return texte;}
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
    
    void writeInFile(QXmlStreamWriter& stream) const; /*!< \brief Redéfinition, ecrit le contenu de la version dans un fichier XML */
    void readFromFile(QXmlStreamReader& stream);  /*!< \brief Rédéfinition, se charge depuis une fichier XML */

    static const QString  StatusQString[];
    static const QString getTextStatus(Status status) {return StatusQString[status];} /*!< \brief Renvoie le Status en QString */
    static Status getStatusFromText(const QString& s); /*!< \brief Renvoie le Status à partir d'un QString */
    

    const QString& getAction() {return action; }
    int getPriorite() {return priorite; }
    const QDateTime& getEcheance() {return echeance; }
    Status getStatus() {return status; }
    void setStatus(const Status s) {status = s;}

    const QString& getDescription() const {return action;}

public slots :

    void setStatusEnAttente(bool checked);
    void setStatusEnCours(bool checked);
    void setStatusTerminee(bool checked);
};

class Multimedia : public VersionNote
{
    Q_OBJECT
private:
    QString description;
    QString file;
    TypeMultimedia typeMedia;

public :
    Multimedia(const QString& _titre,const QString& _descr,const QString _file,QDateTime modif = QDateTime::currentDateTime());
    Multimedia(QXmlStreamReader &stream);
    ~Multimedia();
    TypeNote type() const {return MULTIMEDIA;}

    static const QString  TypeMultimediaQString[];
    static const QString getTextTypeMultimedia(TypeMultimedia type) {return TypeMultimediaQString[type];} /*!< \brief Renvoie le TypeMultimedia en QString */
    static TypeMultimedia getTypeMultimediaFromText(const QString& t); /*!< \brief Renvoie le TypeMultimedia à partir d'un QString */

    void writeInFile(QXmlStreamWriter &stream) const;
    void readFromFile(QXmlStreamReader &stream);

    const QString& getDescription() {return description;}
    const QString& getFile() {return file;}
    TypeMultimedia getTypeMedia() {return typeMedia;}



};


#endif // VERSIONNOTE_H
