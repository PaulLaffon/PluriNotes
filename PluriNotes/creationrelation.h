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
#include <QInputDialog>


class CreationRelation : public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *layout;

    QLabel *labelId;
    QLabel *labelDescription;

    QLineEdit *id;
    QTextEdit *description;

    QDialogButtonBox *buttonbox;
public:
    CreationRelation(QWidget *parent = 0);

signals:
    void RelationAccepter(QString id, QString Description);
public slots:
    void valider();
};



#endif // CREATIONRELATION_H
