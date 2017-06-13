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

    void writeInFile(QXmlStreamWriter& stream) const;

    TypeNote type() const {return MEDIA_IMG;}
};


#endif // VERSIONMULTIMEDIA_H
