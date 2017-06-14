#ifndef AFFICHAGENOTE_H
#define AFFICHAGENOTE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QMdiSubWindow>
#include <QCloseEvent>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QDateTimeEdit>

#include "notemanager.h"

/*! \class AffichageNote
 *  \brief Classe abstraite pour l'affichage d'une Note
 *
 *  Hérite de QMdiSubWindow, gère l'affichage commun à toutes les notes (Articles, Taches ...)
 * */
class AffichageNote : public QMdiSubWindow
{
    Q_OBJECT
protected:
    QWidget *window; /*!< \brief Widget qui prend toute la surface du QMdiSubWindow */
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutId;
    QHBoxLayout *layoutTitre;

    QLabel *labelId;
    QLabel *labelTitre;

    QLineEdit *id;
    QLineEdit *titre;

    QComboBox *listeVersion; /*!< \brief Liste déroulante des différentes versions */

    QPushButton *save;

    QPushButton *supprimer;

    Note* note; /*!< \brief Pointeur sur la note qui correspond à l'affichage */

    void chargerListeVersion(); /*!< \brief Charge la liste de toutes les versions de la Note dans listeVersion */

public:
    AffichageNote(Note *n, QWidget *parent = 0); /*!< \brief Construit l'affichage à partir d'une note */
    virtual ~AffichageNote();

    void closeEvent(QCloseEvent *event); /*!< \brief Redéfinition de la fonction lorsque la fenetre est fermée */

    void focusInEvent(QFocusEvent* event); /*!< \brief Redéfinition de la fonciton lors que la fenetre passe au premier plan */

    QString getId() const {return id->text();}

    virtual void chargerVersion(unsigned int i) = 0; /*!< \brief Charge la version de la note afin de pouvoir l'éditer */

signals:
    void actualisation(Note *n); /*!< \brief Signal émit pour indiquer que des changements ont eu lieu sur la note */
    void fermetureNote(const QString& id); /*!< \brief Signal émit lors de la redéfinition de closeEvent() */
    void passagePremierPlan(Note *n); /*!< \brief Signal émit lorsque la note passe au premier plan */

public slots:
    virtual void nouvelleVersion() = 0; /*!< \brief Slot appelé quand on clic sur le bouton sauvegader */
    void restaurerNote();  /*!< \brief Restaure une note qui était à la corbeille ou archivé */
    void supprimerNote(); /*!< \brief Place une note à la corbeille ou dans les archives si elle est référencée */
    void selectionVersion(int i); /*!< \brief Permet de mettre l'affichage de la i-ème version de la note */

protected slots:
    void sauvegardePossible(); /*!< \brief Rends la sauvegarde possible en autorisant les clics sur le bouton save */
};

/*! \class AffichageArticle
 *  \brief Gère l'affichage des articles
 *
 *  Classe fille de AffichageNote qui permet la modification des articles
 * */
class AffichageArticle : public AffichageNote
{
    Q_OBJECT
protected:
    // un artcle n'as que un champ texte en plus
    QHBoxLayout *layoutTexte;

    QLabel *labelTexte;

    QTextEdit *texte;

public:
    AffichageArticle(Note* n, QWidget *parent = 0);
    ~AffichageArticle();

    void chargerVersion(unsigned int i); /*!< Redéfinition de la fonction virtuelle pure pour la gestion des articles */

public slots:
    void nouvelleVersion(); /*!< \brief Permet de créer une nouvelle version de la note */
};

class AffichageTache : public AffichageNote
{
    Q_OBJECT
private :

    Status statusAffichage; /*!< \brief Status de la tache */

    QHBoxLayout *layoutAction;
    QHBoxLayout *layoutPriorite;
    QHBoxLayout *layoutEcheance;
    QHBoxLayout *layoutStatus;
    QVBoxLayout *layoutButtons;

    QLabel *labelAction;
    QLabel *labelPriorite;
    QLabel *labelEcheance;
    QGroupBox *groupStatus;

    QTextEdit *action;
    QDateTimeEdit *echeance;
    QRadioButton *statusEnAttente;
    QRadioButton *statusEnCours;
    QRadioButton *statusTerminee;
    QLineEdit *priorite;

public :
    AffichageTache(Note* n,QWidget *parent = 0);
    ~AffichageTache();

    void chargerVersion(unsigned int i);

public slots :
    void nouvelleVersion();


};

#endif // AFFICHAGENOTE_H
