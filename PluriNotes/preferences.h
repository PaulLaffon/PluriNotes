#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "notemanager.h"

/*! \class Preferences
 *  \brief Ouvre une fenetre de dialog pour afficher les préférences de l'utilisateur qui seront sauveagrdée
 * */
class Preferences : public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *layout;

    QCheckBox *viderCorbeille;
    QDialogButtonBox *button;

public:
    Preferences(QWidget *parent = 0);

signals:

private slots:
    void valider(); /*!< \brief Se charge de sauvegarder les préférences rentrer par l'utilisateur */
};

#endif // PREFERENCES_H
