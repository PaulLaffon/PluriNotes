#ifndef PARTIECENTRALE_H
#define PARTIECENTRALE_H

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QListWidgetItem>

#include "affichagenote.h"

/*! \class PartieCentrale
 *  \brief Classe qui gère la partie centrale de l'application, hérite de QMdiArea
 */

class PartieCentrale : public QMdiArea
{
    Q_OBJECT
private:
    QVector<AffichageNote*> notes; /*!< Tableau de tous les notes qui sont affichées */

    AffichageNote* dejaOuvert(const QString& id) const; /*!< \brief Renvoie un pointeur sur l'affichage de la note si elle est affichée, sinon nullptr */

public:
    PartieCentrale(QWidget *parent = 0);

signals:

public slots:
    void ouvrirNote(QListWidgetItem* item); /*!< \brief Ouvre la note quand on double clic dessus dans le menu de gauche */
    void fermerNote(const QString& id); /*!< \brief Retire la note du tableau quand l'affichage est fermé */
};

#endif // PARTIECENTRALE_H
