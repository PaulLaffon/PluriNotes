#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    NoteManager& instance = NoteManager::getInstance();
    RelationManager& relations = RelationManager::getInstance();


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
    fichier->addAction("Nouvelle Image");
    fichier->addAction("Nouveau Type de Relation");
    fichier->addAction("Ajouter un couple");

    menu->addMenu(fichier);

    // Lorsqu'on double clic sur une note dans la partie gauche ==> Affiche la note dans la partie centrale
    connect(gauche->getNoteActive(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), centre, SLOT(ouvrirNote(QListWidgetItem*)));
    connect(gauche->getTache(),SIGNAL(itemDoubleClicked(QListWidgetItem*)),centre,SLOT(ouvrirNote(QListWidgetItem*)));
    connect(gauche->getArchive(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), centre, SLOT(ouvrirNote(QListWidgetItem*)));
    connect(gauche->getCorbeille(),SIGNAL(itemDoubleClicked(QListWidgetItem*)),centre,SLOT(ouvrirNote(QListWidgetItem*)));


    // Lorsqu'on double clic sur une note dans l'arborescense, ça affiche la note dans la partie centrale
    connect(droite->getArbreFils(), SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), centre, SLOT(ouvrirNote(QTreeWidgetItem*,int)));
    connect(droite->getArbrePere(), SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), centre, SLOT(ouvrirNote(QTreeWidgetItem*,int)));


    // Lorsqu'on clic dans le menu fichier
    connect(fichier, SIGNAL(triggered(QAction*)), this, SLOT(clicFichier(QAction*)));

    // Lorsqu'une note est créé, on actualise la partie gauche
    connect(&instance, SIGNAL(creationNote()), gauche, SLOT(chargerAll()));

    // Lorsqu'on change la note au premier plan, on change l'arborescense correspondante
    connect(centre, SIGNAL(rechargerArbre(Note*)), droite, SLOT(chargerArbre(Note*)));

    connect(&instance, SIGNAL(erreur(QString)), this, SLOT(erreur(QString)));
    connect(&relations, SIGNAL(erreur(QString)), this, SLOT(erreur(QString)));

    connect(droite->getButton(), SIGNAL(clicked(bool)), this, SLOT(ouvertureGestionRelation()));

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
    else if(a->text() == QString("Nouvelle Image"))
    {
        d->setLabelText(QString("Id de la nouvelle note image"));
        connect(d,SIGNAL(textValueSelected(QString)),&instance,SLOT(nouvelleImage(QString)));
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

void MainWindow::ouvertureGestionRelation()
{
    GestionRelation* gest = new GestionRelation(this);
    gest->chargerListeRelations();
    gest->exec();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    NoteManager& instance = NoteManager::getInstance();

    if(instance.corbeilleVide())
    {
        event->accept();
        return;
    }

    QMessageBox::StandardButton viderCorbeille;
    viderCorbeille = QMessageBox::question( this, "PluriNotes", "Voulez-vous supprimer la corbeille ?",
                           QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes, QMessageBox::Yes);

    if(viderCorbeille == QMessageBox::Yes)
        instance.supprimerCorbeille();
    if(viderCorbeille == QMessageBox::Cancel)
        event->ignore();
    else
        event->accept();
}
