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
    void chargerListeRelation();
    void chargerListeNote1();
    void chargerListeNote2();

signals:
    void CoupleAccepter(QString titre,QString id, Note* note1,Note* note2);
public slots:
    void valider();
};


#endif // CREATIONCOUPLE_H
