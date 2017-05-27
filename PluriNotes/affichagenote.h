#ifndef AFFICHAGENOTE_H
#define AFFICHAGENOTE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

#include "notemanager.h"


class AffichageNote : public QWidget
{
    Q_OBJECT
protected:
    QVBoxLayout *layoutPrincipal;
    QHBoxLayout *layoutId;
    QHBoxLayout *layoutTitre;

    QLabel *labelId;
    QLabel *labelTitre;

    QLineEdit *id;
    QLineEdit *titre;


    QPushButton *save;

    Note* note;

public:
    AffichageNote(QWidget *parent = 0);

signals:

public slots:
};


class AffichageArticle : public AffichageNote
{
    Q_OBJECT
private:
    QHBoxLayout *layoutTexte;

    QLabel *labelTexte;

    QTextEdit *texte;

public:
    AffichageArticle(const QString& _id, unsigned int version, QWidget *parent = 0);
};

#endif // AFFICHAGENOTE_H
