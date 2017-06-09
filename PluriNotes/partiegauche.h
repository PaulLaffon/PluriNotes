#ifndef PARTIEGAUCHE_H
#define PARTIEGAUCHE_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>

#include "notemanager.h"

/*! \class PartieGauche
 *  \brief Affichage du menu à gauche l'application, hérite de QDockWidget
 *
 *  Gère les listes de Notes, de Taches, les notes Archivés ...
 */

class PartieGauche : public QDockWidget
{
private:
    QWidget *widgetTotal; /*!< \brief Widget qui prends toute la surface afin de pouvoir contenir un layout */

    QVBoxLayout *layout;

    QListWidget *noteActive; /*!< \brief Liste des notes actives */
    QListWidget *tache;  /*!< \brief Liste des taches */

public:
    PartieGauche(QWidget *parent = 0);
    ~PartieGauche();

    QListWidget* getNoteActive() const {return noteActive;} // Pour connect avec partieCentrale dans mainWindow

    void chargerListeNote(); /*!< \brief Charge toutes les notes actives dans la liste */
};

#endif // PARTIEGAUCHE_H
