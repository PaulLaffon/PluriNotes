#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    NoteManager& instance = NoteManager::getInstance();

    centre = new PartieCentrale(this);
    setCentralWidget(centre);

    gauche = new PartieGauche(this);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, gauche);

    menu = new QMenuBar(this);
    setMenuBar(menu);

    fichier = new QMenu("Fichier", this);
    fichier->addAction("Nouvel Article");
    fichier->addAction("Nouvelle Tache");

    menu->addMenu(fichier);

    // Lorsqu'on double clic sur une note dans la partie gauche ==> Affiche la note dans la partie centrale
    connect(gauche->getNoteActive(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), centre, SLOT(ouvrirNote(QListWidgetItem*)));

    // Lorsqu'on clic dans le menu fichier
    connect(fichier, SIGNAL(triggered(QAction*)), this, SLOT(clicFichier(QAction*)));

    // Lorsqu'une note est créé, on actualise la partie gauche
    connect(&instance, SIGNAL(creationNote()), gauche, SLOT(chargerListeNote()));


    connect(&instance, SIGNAL(noteDejaExistante(QString)), this, SLOT(erreur(QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::clicFichier(QAction *a)
{
    QInputDialog *d = new QInputDialog(this);
    d->setInputMode(QInputDialog::TextInput);

    NoteManager& instance = NoteManager::getInstance();

    if(a->text() == QString("Nouvel Article"))
    {
        d->setLabelText(QString("Id du nouvel article"));
        connect(d, SIGNAL(textValueSelected(QString)), &instance, SLOT(nouvelleArticle(QString)));
    }
    else if(a->text() == QString("Nouvelle Tache"))
    {
        d->setLabelText(QString("Id de la nouvelle tache"));
    }
    else
        throw NoteException("Type à créer non reconnu, slot clicFichier");



    d->exec();
}


void MainWindow::erreur(QString s)
{
    QMessageBox message;
    message.critical(this, "Erreur", s);
}
