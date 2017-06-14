#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <QDialog>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QDialogButtonBox>

#include "notemanager.h"

class Preferences : public QDialog
{
    Q_OBJECT
private:
    QVBoxLayout *layout;

    QLabel *label;
    QCheckBox *viderCorbeille;
    QDialogButtonBox *button;

public:
    Preferences(QWidget *parent = 0);

signals:

private slots:
    void valider();
};

#endif // PREFERENCES_H
