#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "partiecentrale.h"
#include "partiegauche.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
