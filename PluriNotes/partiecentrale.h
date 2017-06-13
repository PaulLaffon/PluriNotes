#ifndef PARTIECENTRALE_H
#define PARTIECENTRALE_H

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QListWidgetItem>
#include <QTreeWidgetItem>

#include "affichagenote.h"
#include "affichagemultimedia.h"

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

    void ouvrirNote(const QString& id); /*!< \brief Ouverture d'une note, fonction appelée par tous les slots du même non */

signals:
    void rechargerArbre(Note *n); /*!< \brief Signal émit pour indiquer qu'on a besoin de recharger l'arbre des relations */

public slots:
    void ouvrirNote(QTreeWidgetItem* item, int column); /*!< \b Ouvre la note quand on double clic dessus dans l'arborescense à droite */
    void ouvrirNote(QListWidgetItem* item); /*!< \brief Ouvre la note quand on double clic dessus dans le menu de gauche */
    void fermerNote(const QString& id); /*!< \brief Retire la note du tableau quand l'affichage est fermé */

    void emitRechargerArbre(Note *n);
};

#endif // PARTIECENTRALE_H
