#include "creationrelation.h"

CreationRelation::CreationRelation(QWidget *parent): QDialog(parent)
{
    QFormLayout form(this);
    layoutId = new QHBoxLayout();
    layoutDescription = new QHBoxLayout();

    labelId = new QLabel("Id : ", this);
    labelDescription = new QLabel("Description : ", this);

    id = new QLineEdit(this);
    description = new QTextEdit(this);

    QDialogButtonBox buttonbox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,Qt::Horizontal);
    connect(&buttonbox, SIGNAL(accepted()), this, SLOT(valider()));
    connect(&buttonbox, SIGNAL(rejected()), this, SLOT(reject()));

    layoutId->addWidget(labelId);
    layoutId->addWidget(id);

    layoutDescription->addWidget(labelDescription);
    layoutDescription->addWidget(description);

    form.addRow(layoutId);

    form.addRow(layoutDescription);

    form.addRow(&buttonbox);


}

void CreationRelation::valider()
{
    emit RelationAccepter(id->text(),description->toPlainText());
    accept();
}
