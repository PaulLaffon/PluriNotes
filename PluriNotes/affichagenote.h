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


    QPushButton *save;

    Note* note; // Pointeur sur la note qui correspond à l'affichage

public:
    AffichageNote(QWidget *parent = 0);

    void closeEvent(QCloseEvent *event); // Rédifini la fonction quand la sous fenetre est fermée

    QString getId() const {return id->text();}

signals:
    void fermetureNote(const QString& id); // Signal émit lors de la redéfinition de closeEvent()

public slots:
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
};

#endif // AFFICHAGENOTE_H
