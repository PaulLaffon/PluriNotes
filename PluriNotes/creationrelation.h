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

/*! \class CreationRelation
 *  \brief Classe qui gère l'affichage de la création d'une relation
 *  Hérite de QDialog
 * */

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
    void RelationAccepter(QString id, QString Description); /*!< \brief emet un signal qui permet la création d'une relation */
public slots:
    void valider(); /*!< \brief reçoit le signal de la button box puis et emet le signal RelationAccepter */
};



#endif // CREATIONRELATION_H
