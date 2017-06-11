#include "partiedroite.h"

PartieDroite::PartieDroite(QWidget *parent) : QDockWidget(parent)
{
    window = new QWidget(this);

    layout = new QVBoxLayout(window);

    gestionRelation = new QPushButton("Detail Relation", window);

    arbre = new QTreeWidget(window);

    layout->addWidget(arbre);
    layout->addWidget(gestionRelation);

    this->setWidget(window);
}

PartieDroite::~PartieDroite()
{

}
