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
#include "preferences.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    PartieCentrale *centre;
    PartieGauche *gauche;
    PartieDroite *droite;
    QMenuBar *menu;
    QMenu *fichier;
    QMenu *vue;
    QMenu *option;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);

public slots:
    void clicFichier(QAction* a);
    void clicVue(QAction *a);
    void erreur(QString s);
    void ouvertureGestionRelation(); /*!< \brief Recoit un signal provenant du bouton GestionRelation et permet d'ouvrir une fenetre QDialog */

private slots:
    void clicOption();
};

#endif // MAINWINDOW_H
