#ifndef VERSIONMULTIMEDIA_H
#define VERSIONMULTIMEDIA_H

#include <QObject>

#include "versionnote.h"

/*! \class MultiMedia
 *  \brief Classe abstraite qui généralise les informations des différentes versions multimédia  (video, audio, image)
 * */
class MultiMedia : public Article
{
    Q_OBJECT
protected:
    QString filepath; /*!< \brief Chemin vers le fichier multimedia (video, audio, image) */

public:
    MultiMedia(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime()); /*!< \brief Crée une version multimedia a partir de toutes les informations */
    MultiMedia(QXmlStreamReader &stream); /*!< \brief Charge une version multimedia a partir d'un fichier XML */
    ~MultiMedia();

    const QString& getFilePath() const {return filepath;}
};

/*! \class Image
 *  \brief Version gérant les fichiers sous forme d'image
 * */
class Image : public MultiMedia
{
    Q_OBJECT
private:


public:
    Image(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime());
    Image(QXmlStreamReader &stream); /*!< \brief Charge une version multimedia a partir d'un fichier XML */
    ~Image();

    virtual void writeInFile(QXmlStreamWriter& stream) const; /*!< \brief Rédéfintion de la fonction pour sauvegarder la version */

    TypeNote type() const {return MEDIA_IMG;}
};

/*! \class Video
 *  \brief Version gérant les fichiers sous forme de vidéo (peu de format pris en compte, préféré les .wmv)
 * */
class Video : public MultiMedia
{
    Q_OBJECT
private:


public:
    Video(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime());
    Video(QXmlStreamReader &stream);
    ~Video();

    virtual void writeInFile(QXmlStreamWriter& stream) const; /*!< \brief Rédéfintion de la fonction pour sauvegarder la version */

    TypeNote type() const {return MEDIA_VID;}
};

/*! \class Audio
 *  \brief Version gérant les fichiers sous forme audio (préféré les .mp3)
 * */
class Audio : public MultiMedia
{
    Q_OBJECT

public:
    Audio(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime());
    Audio(QXmlStreamReader &stream);
    ~Audio();

    virtual void writeInFile(QXmlStreamWriter& stream) const; /*!< \brief Rédéfintion de la fonction pour sauvegarder la version */

    TypeNote type() const {return MEDIA_AUDIO;}
};

#endif // VERSIONMULTIMEDIA_H
