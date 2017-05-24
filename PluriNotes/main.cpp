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
        Note& n = instance.find("premier");
        Article& a = dynamic_cast<Article&>(n.getLastVersion());
        qDebug() << a.getTexte() << '\n';
        //n.ajouterVersion("Titre de la deuxième version", "Texte de la deuxième version");
        instance.saveAll();
    }
    catch(QException& e)
    {
        qDebug() << e.what() << '\n';
    }




    return a.exec();
}
