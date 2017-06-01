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


class AffichageNote : public QMdiSubWindow
{
    Q_OBJECT
protected:
    QWidget *window; // Widget qui prend tout l'écran du QMdiSubWindow
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutId;
    QHBoxLayout *layoutTitre;

    QLabel *labelId;
    QLabel *labelTitre;

    QLineEdit *id;
    QLineEdit *titre;

    QComboBox *listeVersion; // Liste déroulante des différentes versions

    QPushButton *save;

    Note* note; // Pointeur sur la note qui correspond à l'affichage

    void chargerListeVersion();

public:
    AffichageNote(Note *n, QWidget *parent = 0);
    virtual ~AffichageNote() {}

    void closeEvent(QCloseEvent *event); // Rédifini la fonction quand la sous fenetre est fermée

    QString getId() const {return id->text();}

    // Charge la version de la note pour l'éditer
    virtual void chargerVersion(unsigned int i) = 0;

signals:
    void fermetureNote(const QString& id); // Signal émit lors de la redéfinition de closeEvent()

public slots:
    void selectionVersion(int i);
};


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

    void chargerVersion(unsigned int i);

public slots:
    void nouvelleVersion();
};

#endif // AFFICHAGENOTE_H
