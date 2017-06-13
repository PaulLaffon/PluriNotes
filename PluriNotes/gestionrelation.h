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
    void chargerListeRelations();
    void chargerRelation();
    void chargerCouple(QString);
    Couple* selectionnerCouple();
    Relation* selectionnerRelation();
    void chargerListeCouples(QString);


public slots:
    void sauvegarderModif();
    void supprimerCouple();
    void chargerChangementRelation(QString);
};
#endif // GESTIONRELATION_H
