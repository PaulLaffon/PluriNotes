#ifndef CREATIONRELATION_H
#define CREATIONRELATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QDialog>
#include <QString>
#include <QDialogButtonBox>
#include <QFormLayout>

#include "relationmanager.h"

class CreationRelation : public QDialog
{
    Q_OBJECT
protected:
    QHBoxLayout *layoutId;
    QHBoxLayout *layoutDescription;

    QLabel *labelId;
    QLabel *labelDescription;

    QLineEdit *id;
    QTextEdit *description;

    QDialogButtonBox buttonbox;
public:
    CreationRelation(QWidget *parent);

signals:
    void RelationAccepter(QString id, QString Description);
public slots:
    void valider();
};



#endif // CREATIONRELATION_H
