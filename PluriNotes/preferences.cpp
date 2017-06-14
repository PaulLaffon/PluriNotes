#include "preferences.h"

Preferences::Preferences(QWidget *parent) : QDialog(parent)
{
    NoteManager& instance = NoteManager::getInstance();

    layout = new QVBoxLayout();

    viderCorbeille = new QCheckBox("Vider automatiquement la corbeille", this);
    viderCorbeille->setChecked(instance.getViderCorbeilleAuto());

    button = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal);

    connect(button, SIGNAL(accepted()), this, SLOT(valider()));
    connect(button, SIGNAL(rejected()), this, SLOT(reject()));

    layout->addWidget(viderCorbeille);
    layout->addWidget(button);

    this->setLayout(layout);
}

void Preferences::valider()
{
    NoteManager& instance = NoteManager::getInstance();

    instance.setViderCorbeilleAuto(viderCorbeille->isChecked());
    accept();
}
