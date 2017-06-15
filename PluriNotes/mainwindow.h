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

/*! \class MainWindow
 *  \brief Fenetre principale de l'application
 * */

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

    void closeEvent(QCloseEvent *event); /*!< \brief Redéfinition de la fonction quand la fenetre est fermée, demande à l'utilisateur de vider la corbeille */

public slots:
    void clicFichier(QAction* a); /*!< \brief Slot appelé quand on clique sur un élément du menu Fichier */
    void clicVue(QAction *a); /*!< \brief Slot appelé quand on clique sur un élément du menu Vue */
    void erreur(QString s); /*!< \brief Ouvre un QMessageBox pour indiquer l'erreur */
    void ouvertureGestionRelation(); /*!< \brief Recoit un signal provenant du bouton GestionRelation et permet d'ouvrir une fenetre QDialog */

private slots:
    void clicOption(); /*!< \brief Slot appelé quand on clique sur un élément du menu Option */
};

#endif // MAINWINDOW_H
