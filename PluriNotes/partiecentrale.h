#ifndef PARTIECENTRALE_H
#define PARTIECENTRALE_H

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QListWidgetItem>

#include "affichagenote.h"

class PartieCentrale : public QMdiArea
{
    Q_OBJECT
private:
    QVector<AffichageNote*> notes; // Tableau de tous les notes qui sont affichées

    // Renvoie un pointeur sur l'affichage de la note si elle est affichée, sinon nullptr
    AffichageNote* dejaOuvert(const QString& id) const;

public:
    PartieCentrale(QWidget *parent = 0);

signals:

public slots:
    void ouvrirNote(QListWidgetItem* item); // ouvre une note quand on double clic dans le menu de gauche
    void fermerNote(const QString& id); // Retire la note du tableau quand l'affichage est fermé
};

#endif // PARTIECENTRALE_H
