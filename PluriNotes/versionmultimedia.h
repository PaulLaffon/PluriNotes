#ifndef VERSIONMULTIMEDIA_H
#define VERSIONMULTIMEDIA_H

#include <QObject>

#include "versionnote.h"

class MultiMedia : public Article
{
    Q_OBJECT
protected:
    QString filepath;

public:
    MultiMedia(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime());
    MultiMedia(QXmlStreamReader &stream);
    ~MultiMedia();

    const QString& getFilePath() const {return filepath;}
};


class Image : public MultiMedia
{
    Q_OBJECT
private:


public:
    Image(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime());
    Image(QXmlStreamReader &stream);
    ~Image();

    virtual void writeInFile(QXmlStreamWriter& stream) const;

    TypeNote type() const {return MEDIA_IMG;}
};

class Video : public MultiMedia
{
    Q_OBJECT
private:


public:
    Video(const QString& _titre,const QString& _descr,const QString _file, QDateTime modif = QDateTime::currentDateTime());
    Video(QXmlStreamReader &stream);
    ~Video();

    virtual void writeInFile(QXmlStreamWriter& stream) const;

    TypeNote type() const {return MEDIA_VID;}
};

#endif // VERSIONMULTIMEDIA_H
