#ifndef CREATIONCOUPLE_H
#define CREATIONCOUPLE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QDialog>
#include <QString>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QInputDialog>

#include "notemanager.h"
#include "relationmanager.h"
#include "versionnote.h"

/*! \class CreationCouple
 *  \brief Classe abstraite pour l'affichage de la création d'un couple
 *  Hérite de QDialog, affiche la liste des relation et des notes pour pouvoir créer un couple
 * */

class CreationCouple : public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *layout;

    QLabel *labelRelation;
    QLabel *labelNote1;
    QLabel *labelNote2;
    QLabel *labelTitre;

    QLineEdit *titre;
    QComboBox *listeRelation;
    QComboBox *listeNote1;
    QComboBox *listeNote2;

    QDialogButtonBox *buttonbox;


public:
    CreationCouple(QWidget *parent = 0);
    void chargerListeRelation(); /*!< \brief charge la liste des relation à partir de d'une instance de relationmanager */
    void chargerListeNote1(); /*!< \brief charge la liste des note dans la premiere combobox à partir d'une instance de notemanager */
    void chargerListeNote2(); /*!< \brief charge la liste des note dans la deuxième combobox à partir d'une instance de notemanager */

signals:
    void CoupleAccepter(QString titre,QString id, Note* note1,Note* note2); /*!< \brief emet un signal qui permet la creation d'un couple */
public slots:
    void valider();
};


#endif // CREATIONCOUPLE_H
