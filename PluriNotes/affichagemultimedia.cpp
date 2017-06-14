#include "affichagemultimedia.h"

AffichageMultimedia::AffichageMultimedia(Note *n, QWidget *parent) : AffichageArticle(n, parent)
{
    layoutPath = new QHBoxLayout();
    path = new QLineEdit(this);
    buttonPath = new QPushButton("Choisir fichier");

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

    connect(path, SIGNAL(textChanged(QString)), this, SLOT(sauvegardePossible()));
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
    path->setText(filename);
    chargerMultimedia();
}


AffichageVideo::AffichageVideo(Note *n, QWidget *parent) :AffichageMultimedia(n, parent)
{
    this->resize(300, 400);

    space = new QSpacerItem(100, 100, QSizePolicy::Expanding, QSizePolicy::Expanding);
    video = new QVideoWidget(this);

    chargerMultimedia();


    layoutPrincipal->insertSpacerItem(4, space);

    QRect r = space->geometry();
    r.setLeft(r.left() + 15);
    r.setTop(r.top() + 40);
    r.setHeight(r.height() + 20);
    video->setGeometry(r);
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

AffichageVideo::~AffichageVideo()
{
    player->stop();
}

void AffichageVideo::chargerMultimedia()
{
    player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile(path->text()));
    player->setVolume(10);
    player->play();

    player->setVideoOutput(video);
}


void AffichageVideo::changerPath()
{
    QString filename = QFileDialog::getOpenFileName(this, QString("Ouvrir fichier"), QDir::currentPath(), QString("Videos (*.wmv)"));
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
