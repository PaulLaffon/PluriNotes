#include "mainwindow.h"
#include <QApplication>

#include "notemanager.h"
#include "affichagenote.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();

    NoteManager& instance = NoteManager::getInstance();

    instance.load();

    try
    {
        AffichageArticle fen("premier", 0);
        fen.show();
        //n.ajouterVersion("Titre de la deuxième version", "Texte de la deuxième version");
        instance.saveAll();
        return a.exec();
    }
    catch(QException& e)
    {
        qDebug() << e.what() << '\n';
    }





}
