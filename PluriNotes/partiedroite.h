#ifndef PARTIEDROITE_H
#define PARTIEDROITE_H

#include <QWidget>
#include <QDockWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTreeWidget>

class PartieDroite : public QDockWidget
{
    Q_OBJECT
private:
    QWidget *window; /*!< \brief Widget qui prends toute la surface afin de pouvoir contenir un layout */

    QVBoxLayout *layout;

    QPushButton *gestionRelation;

    QTreeWidget *arbre; /*!< \brief Arborescence des notes par rapport aux relation */

public:
    PartieDroite(QWidget *parent = 0);
    ~PartieDroite();

};

#endif // PARTIEDROITE_H
