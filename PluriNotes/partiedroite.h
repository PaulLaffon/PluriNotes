#ifndef PARTIEDROITE_H
#define PARTIEDROITE_H

#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidget>
#include <QLabel>

#include "notemanager.h"

class PartieDroite : public QDockWidget
{
    Q_OBJECT
private:
    QWidget *window; /*!< \brief Widget qui prends toute la surface afin de pouvoir contenir un layout */

    QVBoxLayout *layout;

    QPushButton *gestionRelation;

    QTreeWidget *arbreFils; /*!< \brief Arborescence des notes filles par rapport aux relation */
    QTreeWidget *arbrePere; /*!< \brief Arborescence des notes mères par rapport aux relation */

    void chargerArbreRecursif(QTreeWidgetItem *pere, Note *noteActu, QSet<Note*> &noteDejaAjoutes, bool successeur);

public:
    PartieDroite(QWidget *parent = 0);
    ~PartieDroite();
    QPushButton* getButton();

    QTreeWidget* getArbreFils() const {return arbreFils;}
    QTreeWidget* getArbrePere() const {return arbrePere;}

public slots:
    void chargerArbre(Note *n);

};

#endif // PARTIEDROITE_H
