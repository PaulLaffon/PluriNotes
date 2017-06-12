#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    NoteManager& instance = NoteManager::getInstance();


    centre = new PartieCentrale(this);
    setCentralWidget(centre);

    gauche = new PartieGauche(this);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, gauche);

    droite = new PartieDroite(this);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, droite);

    menu = new QMenuBar(this);
    setMenuBar(menu);

    fichier = new QMenu("Fichier", this);
    fichier->addAction("Nouvel Article");
    fichier->addAction("Nouvelle Tache");
    fichier->addAction("Nouveau Type de Relation");
    fichier->addAction("Ajouter un couple");

    menu->addMenu(fichier);

    // Lorsqu'on double clic sur une note dans la partie gauche ==> Affiche la note dans la partie centrale
    connect(gauche->getNoteActive(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), centre, SLOT(ouvrirNote(QListWidgetItem*)));
    connect(gauche->getTache(),SIGNAL(itemDoubleClicked(QListWidgetItem*)),centre,SLOT(ouvrirNote(QListWidgetItem*)));

    // Lorsqu'on clic dans le menu fichier
    connect(fichier, SIGNAL(triggered(QAction*)), this, SLOT(clicFichier(QAction*)));

    // Lorsqu'une note est créé, on actualise la partie gauche
    connect(&instance, SIGNAL(creationNote()), gauche, SLOT(chargerListeNote()));
    connect(&instance,SIGNAL(creationTache()),gauche,SLOT(chargerListeTaches()));


    connect(&instance, SIGNAL(erreur(QString)), this, SLOT(erreur(QString)));

    connect(centre, SIGNAL(rechargerArbre(Note*)), droite, SLOT(chargerArbre(Note*)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::clicFichier(QAction *a)
{
    QInputDialog *d = new QInputDialog(this);
    d->setInputMode(QInputDialog::TextInput);
    CreationRelation *rel = new CreationRelation(this);
    CreationCouple *cou = new CreationCouple(this);

    NoteManager& instance = NoteManager::getInstance();
    RelationManager& relations = RelationManager::getInstance();

    if(a->text() == QString("Nouvel Article"))
    {
        d->setLabelText(QString("Id du nouvel article"));
        connect(d, SIGNAL(textValueSelected(QString)), &instance, SLOT(nouvelleArticle(QString)));
        d->exec();
    }
    else if(a->text() == QString("Nouvelle Tache"))
    {
        d->setLabelText(QString("Id de la nouvelle tache"));
        connect(d,SIGNAL(textValueSelected(QString)),&instance,SLOT(nouvelleTache(QString)));
        d->exec();
    }
    else if(a->text() == QString("Nouveau Type de Relation"))
    {
        connect(rel,SIGNAL(RelationAccepter(QString,QString)),&relations,SLOT(ajouterRelation(QString,QString)));
        rel->exec();
    }
    else if(a->text() == QString("Ajouter un couple"))
    {
        cou->chargerListeRelation();
        cou->chargerListeNote1();
        cou->chargerListeNote2();
        connect(cou,SIGNAL(CoupleAccepter(QString,QString,Note*,Note*)),&relations,SLOT(ajouterCouple(QString,QString,Note*,Note*)));
        cou->exec();
    }

    else
        throw NoteException("Type à créer non reconnu, slot clicFichier");



}


void MainWindow::erreur(QString s)
{
    QMessageBox message;
    message.critical(this, "Erreur", s);
}
