#include "affichagemultimedia.h"

AffichageMultimedia::AffichageMultimedia(Note *n, QWidget *parent) : AffichageArticle(n, parent)
{
    layoutPath = new QHBoxLayout();
    path = new QLineEdit(this);
    buttonPath = new QPushButton("Choisir fichier", this);

    layoutPath->addWidget(path);
    layoutPath->addWidget(buttonPath);

    layoutPrincipal->insertLayout(3, layoutPath);

    chargerVersion(note->getNumberVersion() - 1);

    if(note->isArchive() || note->isInCorbeille()) // Si la note est à la corbeille ou archivée
    {
        path->setReadOnly(true);
    }
    else
        connect(buttonPath, SIGNAL(clicked(bool)), this, SLOT(changerPath()));

    // Rends la sauvegarde possible quand on changé le chemin du fichier
    connect(path, SIGNAL(textChanged(QString)), this, SLOT(sauvegardePossible()));
}

AffichageMultimedia::~AffichageMultimedia()
{

}

void AffichageMultimedia::chargerVersion(unsigned int i)
{
    // A ce moment là, la note est obligatoirement un MultiMedia
    MultiMedia *m = dynamic_cast<MultiMedia*>(note->getVersion(i));

    if(m == nullptr) throw NoteException("La note passé ne correspond pas à un multimedia, erreur de dynamique cast");

    path->setText(m->getFilePath());
    texte->setText(m->getDescription());
    titre->setText(m->getTitre());
    id->setText(note->getId());

    save->setDisabled(true);
}

void AffichageMultimedia::nouvelleVersion()
{
    note->supprimerVersionVide();
    note->ajouterVersion(titre->text(), texte->toPlainText(), path->text());
    chargerListeVersion();

    save->setDisabled(true);

    emit actualisation(note);
}


AffichageImage::AffichageImage(Note *n, QWidget *parent) : AffichageMultimedia(n, parent)
{
    image = new QLabel(this);

    chargerMultimedia();

    layoutPrincipal->insertWidget(4, image);
}

void AffichageImage::chargerMultimedia()
{
    QImage *img = new QImage;
    img->load(path->text());

    image->setPixmap(QPixmap::fromImage(*img));
}

void AffichageImage::changerPath()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Ouvrir fichier"), QDir::currentPath(), QString("Images (*.png *.jpg)"));

    if(filename != QString(""))
        path->setText(filename);
    chargerMultimedia();
}


AffichageVideo::AffichageVideo(Note *n, QWidget *parent) :AffichageMultimedia(n, parent)
{
    pause = new QPushButton("Play", this);

    space = new QSpacerItem(100, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
    video = new QVideoWidget(this);

    chargerMultimedia();

    layoutPrincipal->insertSpacerItem(4, space);
    layoutPrincipal->insertWidget(5, pause);

    QRect r = space->geometry();
    r.setLeft(r.left() + 15);
    r.setTop(r.top() + 40);
    r.setHeight(r.height() + 20);
    video->setGeometry(r);

    connect(pause, SIGNAL(clicked(bool)), this, SLOT(playPause()));
}

AffichageVideo::~AffichageVideo()
{

}

void AffichageVideo::playPause()
{
    if(player->state() == QMediaPlayer::PausedState)
    {
        player->play();
        pause->setText("Pause");
    }
    else
    {
        player->pause();
        pause->setText("Play");
    }
}

void AffichageVideo::resizeEvent(QResizeEvent *event)
{
    QMdiSubWindow::resizeEvent(event);
    QRect r = space->geometry();
    r.setLeft(r.left() + 10);
    r.setTop(r.top() + 40);
    r.setHeight(r.height() + 20);
    video->setGeometry(r);
}

void AffichageVideo::chargerMultimedia()
{
    player = new QMediaPlayer(this);
    player->setMedia(QUrl::fromLocalFile(path->text()));
    player->pause();
    pause->setText("Play");

    player->setVideoOutput(video);
}


void AffichageVideo::changerPath()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Ouvrir fichier"), QDir::currentPath(), QString("Videos (*.wmv)"));

    if(filename != QString(""))
        path->setText(filename);
    chargerMultimedia();
}

void AffichageVideo::nouvelleVersion()
{
    note->supprimerVersionVide();
    note->ajouterVersionVideo(titre->text(), texte->toPlainText(), path->text());
    chargerListeVersion();

    save->setDisabled(true);

    emit actualisation(note);
}

void AffichageVideo::closeEvent(QCloseEvent *event)
{
    AffichageNote::closeEvent(event);
    player->stop();
    delete player;
}

AffichageAudio::AffichageAudio(Note *n, QWidget *parent) : AffichageMultimedia(n, parent)
{
    pause = new QPushButton("Play", this);

    layoutPrincipal->insertWidget(4, pause);

    chargerMultimedia();

    connect(pause, SIGNAL(clicked(bool)), this, SLOT(playPause()));
}

void AffichageAudio::playPause()
{
    if(player->state() == QMediaPlayer::PausedState)
    {
        player->play();
        pause->setText("Pause");
    }
    else
    {
        player->pause();
        pause->setText("Play");
    }
}

void AffichageAudio::changerPath()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Ouvrir fichier"), QDir::currentPath(), QString("Audio (*.mp3)"));

    if(filename != QString(""))
        path->setText(filename);
    chargerMultimedia();
}

void AffichageAudio::chargerMultimedia()
{
    player = new QMediaPlayer(this);

    player->setMedia(QUrl::fromLocalFile(path->text()));
    player->pause();
    pause->setText("Play");
}

void AffichageAudio::nouvelleVersion()
{
    note->supprimerVersionVide();
    note->ajouterVersionAudio(titre->text(), texte->toPlainText(), path->text());
    chargerListeVersion();

    save->setDisabled(true);

    emit actualisation(note);
}

void AffichageAudio::closeEvent(QCloseEvent *event)
{
    AffichageNote::closeEvent(event);
    player->stop();
    delete player;
}
