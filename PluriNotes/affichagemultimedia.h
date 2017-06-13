#ifndef AFFICHAGEMULTIMEDIA_H
#define AFFICHAGEMULTIMEDIA_H

#include <QFileDialog>
#include <QImage>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSpacerItem>

#include "affichagenote.h"

class AffichageMultimedia : public AffichageArticle
{
    Q_OBJECT
protected:
    QHBoxLayout *layoutPath;

    QLineEdit* path;
    QPushButton* buttonPath;

public:
    AffichageMultimedia(Note* n, QWidget *parent = 0);

    void chargerVersion(unsigned int i);

    virtual void chargerMultimedia() = 0;

public slots:
    void nouvelleVersion();

    virtual void changerPath() = 0;
};

class AffichageImage : public AffichageMultimedia
{
    Q_OBJECT
private:
    QLabel *image;

public:
    AffichageImage(Note* n, QWidget *parent = 0);

    void chargerMultimedia();

public slots:
    void changerPath();
};

class AffichageVideo : public AffichageMultimedia
{
    Q_OBJECT
private:
    QVideoWidget *video;
    QMediaPlayer *player;

    QSpacerItem *space;

public:
    AffichageVideo(Note* n, QWidget *parent = 0);
    ~AffichageVideo();

    void nouvelleVersion();
    void chargerMultimedia();

    void resizeEvent(QResizeEvent* event);

public slots:
    void changerPath();
};


#endif // AFFICHAGEMULTIMEDIA_H
