#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include <QVector>
#include <QString>
#include <QDebug>

#include "note.h"
#include "relationmanager.h"

/*! \class NoteManager
 *  \brief Singleton factory pour les Note
 *  Singleton qui s'occupe de la crétion et de la gestion des différentes Note
 *  */
class NoteManager : public QObject
{
    Q_OBJECT
private:
    QVector<Note*> notes;

    QString filename;

    NoteManager(); /*!< \brief Singleton, le constructeur est privé */
    ~NoteManager();
    NoteManager(const NoteManager& m);
    NoteManager& operator=(const NoteManager& m);

    static NoteManager* instance;

public:
    static NoteManager& getInstance(); /*!< \brief Récupère l'instance de la classe NoteManager */
    static void deleteInstance(); /*!< \brief Supprime l'instance de la classe NoteManager */

    /*! \brief Charge les notes du fichier de sauvegarde filename
     *  Appeler au lancement de l'application
     *  Appel de la fonction load() de RelationManager en même temps pour charger toutes les informations sur les Note et Relation
     * */
    void load();

    /*! \brief Sauvegarde toutes les notes dans un fichier XML
     *  Appeler à la fermeture de l'application
     *  Appel la fonction saveAll() de RelationManager pour sauvegarder en même temps les différentes Relations */
    void saveAll();


    /*! \brief Cree une nouvelle note sans Version, utilisé lors de la fonction load()
     *  */
    void nouvelleNote(const QString& id, const QDateTime& crea, const QDateTime& modif, bool archive, bool corbeille);

    Note* find(const QString& id) const; /*!< \brief Renvoie la note correspondant à l'id */


    /*! \class TypeIterator
     *  \brief Itérateur sur le d'une d'une note
     *  \example begin(ARTICLE) ==> Itérateur sur tous les articles
     * */
    class TypeIterator
    {
    private:
        friend class NoteManager;
        QVector<Note*>::iterator it;
        TypeNote type;
        int restant;

    public:
        TypeIterator(QVector<Note*>::iterator i, TypeNote t, int r) :it(i), type(t), restant(r)
        {
            while(restant > 0 && (*it)->type() != type) {
                it++;
                restant--;
            }
        }

        bool operator !=(const TypeIterator& i) const {return it != i.it;}
        TypeIterator& operator++()
        {
            it++; restant--;
            while(restant > 0 && (*it)->type() != type) {
                it++;
                restant--;
            }
            return *this;
        }

        Note* operator*() {return *it;}

    };


    TypeIterator begin(TypeNote type) {return TypeIterator(notes.begin(), type, notes.size());} /*!< \brief Retourne un itérateur sur le premier élément du type souhaité */

    TypeIterator end() {return TypeIterator(notes.end(), ARTICLE, 0);} // Ici le type d'itérateur n'as pas d'importance

public slots:
    void nouvelleArticle(const QString& id); /*!< \brief Cree un nouvel article avec une première version vide */

signals:
    void erreur(QString); /*!< \brief Signal émit lorqu'on rencontre une erreur, tel que la création d'une note dont l'id existe déjà */
    void creationNote(); /*!< \brief Signal qui indique qu'une nouvelle note a été créé, recharger la liste des notes */

};

#endif // NOTEMANAGER_H
