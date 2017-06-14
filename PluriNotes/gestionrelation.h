#ifndef GESTIONRELATION_H
#define GESTIONRELATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QDialog>
#include <QString>
#include <QPushButton>
#include <QFormLayout>
#include <QInputDialog>

#include "relationmanager.h"
#include "notemanager.h"

/*! \class CreationCouple
 *  \brief Classe abstraite pour le parcours et la modification des relations ainsi que des
 *  couples qui lui sont associés
 *  Hérite de QDialog, affiche la liste des relations, le titre de la description de la
 *  relation sélectionée ainsi que la liste des couples associés à cetet relation avec le titre
 *  du couples selectionné
 * */

class GestionRelation : public QDialog
{
    Q_OBJECT
protected:
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutCouples;
    QHBoxLayout *layoutRelations;
    QHBoxLayout *layoutModifTitre;
    QHBoxLayout *layoutModifDescription;
    QHBoxLayout *layoutModifCouples;

    QLabel *labelRelations;
    QLabel *labelModifTitre;
    QLabel *labelModifDescription;
    QLabel *labelCouples;
    QLabel *labelModifCouples;

    QComboBox *listeRelations;
    QLineEdit *modifTitre;
    QTextEdit *modifDescription;
    QComboBox *listeCouples;
    QLineEdit *modifCouple;


    QPushButton *supprimer;
    QPushButton *sauvegarder;

public:
    GestionRelation(QWidget *parent = 0);
    void chargerListeRelations(); /*!< \brief charge la liste des relations à partir d'une instance de RelationManager */
    void chargerRelation();   /*!< \brief charge le titre et la description d'une relation dans les QLineEdit et QTextEdit */
    Couple* selectionnerCouple(); /*!< \brief Renvoie un pointeur sur le couple qui est actuellement decrit dans la ComboBox listeCouples*/
    Relation* selectionnerRelation(); /*!< \brief Renvoi un pointeur sur la relation qui est actuellement decrite dans la ComboBox listeRelations*/
    void chargerListeCouples(QString); /*!< \brief charge la liste des couples correspondants a la relation decrite par la chaîne de caractères */


public slots:
    void sauvegarderModif();
    void supprimerCouple();
    void chargerChangementRelation(int i); /*!< \brief Reçoit un signal lorsque l 'index de la Combobox des relations change et permet de charger les nouveaux titres et description ainsi que la liste des couples en consequence*/
    void chargerCouple(QString); /*!< \brief Charge le titre du couple selectioné par la ComboBox dans le QLineEdit*/
};
#endif // GESTIONRELATION_H
