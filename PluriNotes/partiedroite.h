#ifndef PARTIEDROITE_H
#define PARTIEDROITE_H

#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidget>

#include "notemanager.h"

class PartieDroite : public QDockWidget
{
    Q_OBJECT
private:
    QWidget *window; /*!< \brief Widget qui prends toute la surface afin de pouvoir contenir un layout */

    QVBoxLayout *layout;

    QPushButton *gestionRelation;

    QTreeWidget *arbre; /*!< \brief Arborescence des notes par rapport aux relation */

    void chargerArbreRecursif(QTreeWidgetItem *pere, Note *noteActu, QSet<Note*> &noteDejaAjoutes);

public:
    PartieDroite(QWidget *parent = 0);
    ~PartieDroite();
    QPushButton* getButton();

    QTreeWidget* getArbre() const {return arbre;}

public slots:
    void chargerArbre(Note *n);

};

#endif // PARTIEDROITE_H
