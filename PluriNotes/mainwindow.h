#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QInputDialog>
#include <QMessageBox>

#include "partiecentrale.h"
#include "partiegauche.h"
#include "partiedroite.h"

#include "relationmanager.h"
#include "creationrelation.h"
#include "creationcouple.h"
#include "gestionrelation.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    PartieCentrale *centre;
    PartieGauche *gauche;
    PartieDroite *droite;
    QMenuBar *menu;
    QMenu *fichier;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

public slots:
    void clicFichier(QAction* a);
    void erreur(QString s);
    void ouvertureGestionRelation();
};

#endif // MAINWINDOW_H
