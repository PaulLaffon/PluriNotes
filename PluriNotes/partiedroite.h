#ifndef PARTIEDROITE_H
#define PARTIEDROITE_H

#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QLabel>

#include "notemanager.h"

/*! \class PartieDroite
 *
 *  \brief Affichage de la partie droite de l'application (arbre des dépendances)
 * */


class PartieDroite : public QDockWidget
{
    Q_OBJECT
private:
    QWidget *window; /*!< \brief Widget qui prends toute la surface afin de pouvoir contenir un layout */

    QVBoxLayout *layout;

    QPushButton *gestionRelation;

    QTreeWidget *arbreFils; /*!< \brief Arborescence des notes filles par rapport aux relation */
    QTreeWidget *arbrePere; /*!< \brief Arborescence des notes mères par rapport aux relation */


    void chargerArbreRecursif(QTreeWidgetItem *pere, Note *noteActu, QSet<Note*> &noteDejaAjoutes, bool successeur);
    /*!< \brief Charge un arbre des successeur/predecesseur récursivement */

    PartieDroite();  /*!< \brief Singleton, on ne peut ni créer ni détruire un objet de cette classe */
    ~PartieDroite();
    PartieDroite(const PartieDroite& p);
    PartieDroite& operator=(const PartieDroite& p);

    static PartieDroite* instance;


public:
    static PartieDroite *getInstance(); /*!< Récupère l'instance de PartieDroite */
    static void deleteInstance(); /*!< Supprime l'instance de la classe */

    QPushButton* getButton();

    QTreeWidget* getArbreFils() const {return arbreFils;}
    QTreeWidget* getArbrePere() const {return arbrePere;}

public slots:
    void chargerArbre(Note *n); /*!< \brief Charge les arbres des successeurs et prédécesseurs de la note */

};

#endif // PARTIEDROITE_H
