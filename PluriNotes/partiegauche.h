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

    PartieGauche();  /*!< \brief Singleton, on ne peut ni créer ni détruire un objet de cette classe */
    ~PartieGauche();
    PartieGauche(const PartieGauche& p);
    PartieGauche& operator=(const PartieGauche& p);

    static PartieGauche* instance;

public:
    static PartieGauche *getInstance(); /*!< Récupère l'instance de PartieGauche */
    static void deleteInstance(); /*!< Supprime l'instance de la classe */

    QListWidget* getNoteActive() const {return noteActive;} // Pour connect avec partieCentrale dans mainWindow
    QListWidget* getTache() const {return tache;}
    QListWidget* getArchive() const {return archive;}
    QListWidget* getCorbeille() const {return corbeille;}

    void chargerListeNote(); /*!< \brief Charge toutes les notes actives dans la liste */
    void chargerListeTaches(); /*!< \brief Charge toutes les taches */

    void chargerListeArchive(); /*!< \brief Charge toutes les notes archives */
    void chargerListeCorbeille(); /*!< \brief Charge toutes les notes de la corbeille */

public slots:
    void chargerAll(); /*!< \brief Charge les 4 liste de notes */
};

#endif // PARTIEGAUCHE_H
