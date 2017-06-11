#include "creationrelation.h"

CreationRelation::CreationRelation(QWidget *parent): QDialog(parent)
{
    layout = new QVBoxLayout();

    labelId = new QLabel("Id : ", this);
    labelDescription = new QLabel("Description : ", this);

    id = new QLineEdit(this);
    description = new QTextEdit(this);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal);
    connect(buttonbox, SIGNAL(accepted()), this, SLOT(valider()));
    connect(buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    layout->addWidget(labelId);
    layout->addWidget(id);

    layout->addWidget(labelDescription);
    layout->addWidget(description);

    layout->addWidget(buttonbox);

    this->setLayout(layout);
}

void CreationRelation::valider()
{
    emit RelationAccepter(id->text(),description->toPlainText());
    accept();
}
