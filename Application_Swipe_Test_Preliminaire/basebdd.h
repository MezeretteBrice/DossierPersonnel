#ifndef BASEBDD_H
#define BASEBDD_H

#include "QtSql/QSqlDatabase"
#include <QtSql/QtSql>
#include <QString>
#include <QObject>
#include <QDateTime>

class BaseBDD : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool erreurConnexion MEMBER erreurConnexion NOTIFY erreurChanged) ///Si il y a une erreur D'ouverture de la BDD.
    Q_PROPERTY(QStringList listeRonde READ getRonde NOTIFY listeRondeChanged) ///Affiche la liste des rondes dans le combobox.
    Q_PROPERTY(QStringList listePointeaux READ getPointeaux NOTIFY listePointeauxChanged) ///Affiche la liste des pointeaux dans le combobox.

public:

    explicit BaseBDD(QObject *parent = nullptr);
    QStringList getRonde();
    QStringList getPointeaux();
    Q_INVOKABLE bool choisirRonde(QString _nomRonde); ///Permet de recuperer le nom de la ronde choisie
    Q_INVOKABLE void enregistrer(const QString _donneeBDD); ///Permet d'enregistrer dans la table HistoriquePointeaux idAgent,nomPointeau,date,anomalie.
    Q_INVOKABLE void enregistrerPointeaux(const QString _donneeBDD);///Permet de récuperer le nom du pointeau actuel.
    Q_INVOKABLE void enregistrerAnomalie(const QString _donneeAnomalie);///Permet d'enregistrer l'anomalie dans la BDD.
    Q_INVOKABLE void pointeauxIgnorer();///Permet d'ignoré le pointeau si il ne marche pas.

private:

    int idronde = 0;

    QSqlDatabase DB;
    QString nomRonde;
    QString nomPointeaux;
    QStringList ronde;
    QStringList pointeaux;
    QString Serveur, Nom, ID, Pass;

    bool erreurConnexion;


    bool recupererPointeaux(QStringList &_donnees);///Permet de recuperer les pointeaux de la ronde choisie.
    bool recupererRonde(int _idAgent, QStringList & _donnees);///Permet de recuperer les rondes.
    bool recupererIdRonde(QString nomRonde);///Permet de recuperer idRonde de la ronde choisie.


signals:

    void erreurChanged();
    void listeRondeChanged();
    void listePointeauxChanged();

public slots:

};
#endif // BASEBDD_H

