#ifndef PARTIEGAUCHE_H
#define PARTIEGAUCHE_H

#include <QDockWidget>
#include <QVBoxLayout>
#include <QListWidget>

#include "notemanager.h"

class PartieGauche : public QDockWidget
{
private:
    // On met un widget qui prend toute le surface, car un QDockWidget ne peut pas contenir de layout
    QWidget *widgetTotal;

    QVBoxLayout *layout;

    QListWidget *noteActive; // Liste de notes actives
    QListWidget *tache;

public:
    PartieGauche(QWidget *parent = 0);
    ~PartieGauche();

    QListWidget* getNoteActive() const {return noteActive;} // Pour connect avec partieCentrale dans mainWindow

    // Charge toute la liste des notes actives
    void chargerListeNote();
};

#endif // PARTIEGAUCHE_H
