#ifndef AFFICHAGEMULTIMEDIA_H
#define AFFICHAGEMULTIMEDIA_H

#include <QFileDialog>
#include <QImage>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QSpacerItem>

#include "affichagenote.h"

/*! \class AffichageMultimedia
 *  \brief Classe abstraite, généralisation des affichages pour les notes avec fichiers multimédia (image, vidéo, audio)
 *
 *   Hérite de AffichageArticle
 * */
class AffichageMultimedia : public AffichageArticle
{
    Q_OBJECT
protected:
    QHBoxLayout *layoutPath;

    QLineEdit* path;
    QPushButton* buttonPath; /*!< \brief Bouton pour choisir le fichier multimédia */

public:
    AffichageMultimedia(Note* n, QWidget *parent = 0);
    ~AffichageMultimedia();

    void chargerVersion(unsigned int i); /*!< \brief Redéfinition de la fonction pour charger une version */

    virtual void chargerMultimedia() = 0; /*!< \brief Fonction virtuelle pure, sera redéfini pour charger les différents types de médias pris en charge */

public slots:
    void nouvelleVersion(); /*!< \brief Slot appelé quand on appuie sur le bouton save */

private slots:
    virtual void changerPath() = 0; /*!< \brief Ouvre l'outil de selection des fichier, n'affiche que les types souhaités */
};

class AffichageImage : public AffichageMultimedia
{
    Q_OBJECT
private:
    QLabel *image;

public:
    AffichageImage(Note* n, QWidget *parent = 0);

    void chargerMultimedia();

private slots:
    void changerPath();
};

class AffichageVideo : public AffichageMultimedia
{
    Q_OBJECT
private:
    QVideoWidget *video;
    QMediaPlayer *player;

    QPushButton *pause;

    QSpacerItem *space; /*!< \brief Espace allant acceuillir la vidéo */

public:
    AffichageVideo(Note* n, QWidget *parent = 0);
    ~AffichageVideo();

    void nouvelleVersion();
    void chargerMultimedia();

    void resizeEvent(QResizeEvent* event); /*!<  \brief Redimentionner la vidéo quand la fenetre change de taille */

    void closeEvent(QCloseEvent* event); /*!< \brief Arreter la vidéo quand la fenetre est fermée */

private slots:
    void playPause(); /*!< \brief Gestion de l'appuie sur le bouton Play/pause */
    void changerPath();
};

class AffichageAudio : public AffichageMultimedia
{
    Q_OBJECT
private:
    QMediaPlayer *player;
    QPushButton *pause;

public:
    AffichageAudio(Note* n, QWidget *parent = 0);

    void nouvelleVersion();
    void chargerMultimedia(); /*!< \brief Arreter la vidéo quand la fenetre est fermée */

    void closeEvent(QCloseEvent* event);

private slots:
    void playPause(); /*!< \brief Gestion de l'appuie sur le bouton Play/pause */
    void changerPath();

};


#endif // AFFICHAGEMULTIMEDIA_H
