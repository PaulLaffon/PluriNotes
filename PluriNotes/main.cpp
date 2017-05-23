#include "mainwindow.h"
#include <QApplication>

#include "notemanager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    NoteManager& instance = NoteManager::getInstance();

    instance.load();

    try
    {
        const Note& n = instance.find("premier");
    }
    catch(QException& e)
    {
        qDebug() << e.what() << '\n';
    }




    return a.exec();
}
