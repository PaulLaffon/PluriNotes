#ifndef PARTIEGAUCHE_H
#define PARTIEGAUCHE_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>

#include "notemanager.h"

/*! \class PartieGauche
 *  \brief Affichage du menu à gauche l'application, hérite de QDockWidget
 *
 *  Gère les listes de Notes, de Taches, les notes Archivés ...
 */

class PartieGauche : public QDockWidget
{
    Q_OBJECT

private:
    QWidget *widgetTotal; /*!< \brief Widget qui prends toute la surface afin de pouvoir contenir un layout */

    QVBoxLayout *layout;

    QListWidget *noteActive; /*!< \brief Liste des notes actives */
    QListWidget *tache;  /*!< \brief Liste des taches */
    QListWidget *archive;
    QListWidget *corbeille;

public:
    PartieGauche(QWidget *parent = 0);
    ~PartieGauche();

    QListWidget* getNoteActive() const {return noteActive;} // Pour connect avec partieCentrale dans mainWindow
    QListWidget* getTache() const {return tache;}
    QListWidget* getArchive() const {return archive;}
    QListWidget* getCorbeille() const {return corbeille;}

    void chargerListeNote(); /*!< \brief Charge toutes les notes actives dans la liste */
    void chargerListeTaches(); /*!< \brief Charge toutes les taches */

    void chargerListeArchive();
    void chargerListeCorbeille();

public slots:
    void chargerAll();
};

#endif // PARTIEGAUCHE_H
