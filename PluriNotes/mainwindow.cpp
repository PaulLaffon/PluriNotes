#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    PartieCentrale *centre = new PartieCentrale(this);
    setCentralWidget(centre);

    PartieGauche *gauche = new PartieGauche(this);
    addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea, gauche);

    // Lorsqu'on double clic sur une note dans la partie gauche ==> Affiche la note dans la partie centrale
    connect(gauche->getNoteActive(), SIGNAL(itemDoubleClicked(QListWidgetItem*)), centre, SLOT(ouvrirNote(QListWidgetItem*)));
}

MainWindow::~MainWindow()
{

}
