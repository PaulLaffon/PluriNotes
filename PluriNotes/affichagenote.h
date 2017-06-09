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

    Note* note; /*!< \brief Pointeur sur la note qui correspond à l'affichage */

    void chargerListeVersion(); /*!< \brief Charge la liste de toutes les versions de la Note dans listeVersion */

public:
    AffichageNote(Note *n, QWidget *parent = 0);
    virtual ~AffichageNote() {}

    void closeEvent(QCloseEvent *event); /*!< \brief Redéfinition de la fonction lorsque la fenetre est fermée */

    QString getId() const {return id->text();}

    virtual void chargerVersion(unsigned int i) = 0; /*!< \brief Charge la version de la note afin de pouvoir l'éditer */

signals:
    void fermetureNote(const QString& id); /*!< \brief Signal émit lors de la redéfinition de closeEvent() */

public slots:
    void selectionVersion(int i); /*!< \brief Permet de mettre l'affichage de la i-ème version de la note */
};

/*! \class AffichageArticle
 *  \brief Gère l'affichage des articles
 *
 *  Classe fille de AffichageNote qui permet la modification des articles
 * */
class AffichageArticle : public AffichageNote
{
    Q_OBJECT
private:
    // un artcle n'as que un champ texte en plus
    QHBoxLayout *layoutTexte;

    QLabel *labelTexte;

    QTextEdit *texte;

public:
    AffichageArticle(Note* n, QWidget *parent = 0);

    void chargerVersion(unsigned int i); /*!< Redéfinition de la fonction virtuelle pure pour la gestion des articles */

public slots:
    void nouvelleVersion(); /*!< \brief Permet de créer une nouvelle version de la note */
};

#endif // AFFICHAGENOTE_H
