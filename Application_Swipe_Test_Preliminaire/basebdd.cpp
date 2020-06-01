#include "basebdd.h"
#include "QDebug"
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QMessageBox>
/**
 * @brief BaseBDD::choisirRonde
 * @param _nomRonde sert a récuperer le nom de la ronde actuelle
 * ChoisirRonde permet de récuperer le Ronde choisie.
 * @return
 */
bool BaseBDD::choisirRonde(QString _nomRonde)
{
    nomRonde = _nomRonde;
    qDebug() << Q_FUNC_INFO << "Le nom de la ronde est : " << nomRonde;
}

/**
 * @brief BaseBDD::enregistrer
 * @param _donneeBDD contient le nomPointeaux de notre combobox
 * La fonction enregistrer permet d'enregistrer les scannes de nos pointeaux tout au long de notre ronde.
 */
void BaseBDD::enregistrer(const QString _donneeBDD)
{
    int testidAgent = 1;
    QString anomalie = "aucune anomalie";
    QDateTime horodatageActuelle = QDateTime::currentDateTime();
    QSqlQuery requete;
    if(DB.isOpen()){
        requete.prepare(" INSERT INTO `HistoriquePointeaux` ( `idAgent` , `nomPointeaux` , `date` , `anomalie` ) "
                        " VALUES (:idAgent, :nompointeaux, :date, :anomalie);");

        requete.bindValue(":idAgent" , testidAgent);
        requete.bindValue(":nompointeaux", _donneeBDD);
        requete.bindValue(":date", horodatageActuelle);
        requete.bindValue(":anomalie", anomalie);

        if(!requete.exec()){
            qDebug() << Q_FUNC_INFO << "probleme dans la requete enregistrer";
        }
        qDebug() << Q_FUNC_INFO << "sa ses bien enregistrer" << testidAgent <<_donneeBDD << horodatageActuelle << anomalie;
    }else {
        qDebug() << Q_FUNC_INFO << "la BDD est pas ouverte";
    }
}
/**
 * @brief BaseBDD::enregistrerPointeaux
 * @param _donneeBDD récupère donc le nom du pointeau actuel pour que nomPointeaux,
 * un attribut que n'importe quelles fonctions peut avoir accès
 * prenne cette valeur pour pouvoir ensuite le scanner,
 * ce parametre sera utiliser dans la fonction pointeauxIgnorer() et enregistrerAnomalie().
 */
void BaseBDD::enregistrerPointeaux(const QString _donneeBDD)
{
    nomPointeaux = _donneeBDD;
}
/**
 * @brief BaseBDD::enregistrerAnomalie
 * @param _donneeAnomalie permet de récuperer la description de l'anomalie qui se trouve dans le textfield de notre application.
 * Qui nous servira ensuite pour enregistrer l'anomalie dans la base de données tout en enregistrant le pointeau actuel avec l'heure aussi.
 */
void BaseBDD::enregistrerAnomalie(const QString _donneeAnomalie)
{
    QDateTime horodatageActuelle = QDateTime::currentDateTime();
    QSqlQuery requete;
    int testidAgent = 1;
    if(DB.isOpen()){
        requete.prepare(" INSERT INTO `HistoriquePointeaux` ( `idAgent` , `nomPointeaux` , `date` , `anomalie` ) "
                        " VALUES (:idAgent, :nompointeaux, :date, :anomalie);");

        requete.bindValue(":idAgent" , testidAgent);
        requete.bindValue(":nompointeaux", nomPointeaux);
        requete.bindValue(":date", horodatageActuelle);
        requete.bindValue(":anomalie", _donneeAnomalie);

        if(!requete.exec()){
            qDebug() << Q_FUNC_INFO << "probleme dans la requete enregistrer";
        }
        qDebug() << Q_FUNC_INFO << "sa ses bien enregistrer" << testidAgent << nomPointeaux << horodatageActuelle << _donneeAnomalie;
    }else {
        qDebug() << Q_FUNC_INFO << "la BDD est pas ouverte";
    }
}
/**
 * @brief BaseBDD::pointeauxIgnorer
 * pointeauxIgnoré permet d'ignorer le pointeau actuel s'il ne fonctionne pas,
 * donc dans la BDD, dans le champ anomalie,
 * il sera écrit Pointeaux ignoré mais aussi cela va aussi enregistrer idAgent, nomPointeaux, date.
 */
void BaseBDD::pointeauxIgnorer()
{
    QDateTime horodatageActuelle = QDateTime::currentDateTime();
    QSqlQuery requete;
    int testidAgent = 1;
    QString _donneeIgnorerPointeaux = "Pointeau ignoré";
    if(DB.isOpen()){
        requete.prepare(" INSERT INTO `HistoriquePointeaux` ( `idPointeaux` , `nomPointeaux` , `date` , `anomalie` ) "
                        " VALUES (:idPointeaux, :nompointeaux, :date, :anomalie);");

        requete.bindValue(":idPointeaux" , testidAgent);
        requete.bindValue(":nompointeaux", nomPointeaux);
        requete.bindValue(":date", horodatageActuelle);
        requete.bindValue(":anomalie", _donneeIgnorerPointeaux);

        if(!requete.exec()){
            qDebug() << Q_FUNC_INFO << "probleme dans la requete enregistrer";
        }
        qDebug() << Q_FUNC_INFO << "sa ses bien enregistrer" << testidAgent << nomPointeaux << horodatageActuelle << _donneeIgnorerPointeaux;
    }else {
        qDebug() << Q_FUNC_INFO << "la BDD est pas ouverte";
    }
}
/**
 * @brief BaseBDD::BaseBDD
 * @param parent
 * Le constructeur permet d'ouvrir la BDD, si elle ne s'ouvre pas elle émet un signal qui appellera
 * la fonction erreurConnexion.
 */
BaseBDD::BaseBDD(QObject *parent): QObject(parent), erreurConnexion(false)
{
    DB = QSqlDatabase::addDatabase("QSQLITE");
    //DB.setHostName("localhost");

    DB.setDatabaseName("/home/bmezerette/Bureau/ControleurDeRonde2020");
    //DB.setDatabaseName("/sdcard/Antoine/data/com.project.rondierprojet/files/");

    DB.open();

    qDebug() << DB.connectionName();
    qDebug() << DB.isOpen();
    qDebug() << DB.contains();

    if(!DB.isOpen()) // Si l'ouverture as eu un problème ou non, afficher le message correspondant
    {
        qDebug() << Q_FUNC_INFO << "Erreur Ouverture";
    }
    else
    {
        qDebug("Ouverture reussie");
    }
    emit erreurChanged();
}
/**
 * @brief BaseBDD::getRonde
 * Cette fonction permet de récuperer le nom des rondes.
 */
QStringList BaseBDD::getRonde()
{
    if(!erreurConnexion)
    {
        ronde.clear();
        recupererRonde(1,ronde); // à la place de 1 =  nom variable pour identification
    }
    return ronde;
}
/**
 * @brief BaseBDD::getPointeaux
 * Cette fonction permet de récuperer tout d'abord l'id de la ronde.
 * Ensuite grâce à l'id de la ronde on récupere les pointeaux de la ronde.
 * @return
 */
QStringList BaseBDD::getPointeaux()
{
    if(!erreurConnexion)
    {
        pointeaux.clear();
        if(recupererIdRonde(nomRonde)){
            recupererPointeaux(pointeaux);
        }
    }
    return pointeaux;

}

/**
 * @brief BaseBDD::recupererPointeaux
 * @param _donnees permet de récuperer la liste des pointeaux en fonction du nom de la ronde choisie.
 * @return
 */

bool BaseBDD::recupererPointeaux(QStringList &_donnees)
{
    bool retour = false;
    qDebug() << Q_FUNC_INFO << idronde;
    if(DB.isOpen())
    {
        QSqlQuery r(DB.database());
        r.prepare("select Pointeaux.alias, Pointeaux.nom from AssociationsPointeauxRondes, "
                  "Pointeaux where AssociationsPointeauxRondes.idPointeau = Pointeaux.idPointeaux "
                  "AND AssociationsPointeauxRondes.idRonde = :ronde ORDER BY AssociationsPointeauxRondes .ordrePointeau;");
        r.bindValue(":ronde",idronde);
        if(r.exec()){
            while(r.next())
            {
                // on stocke l'enregistrement dans le QStringList
                _donnees << r.value("nom").toString();
                qDebug() << Q_FUNC_INFO << _donnees;
            }
            retour = true;
        }else
        {
            qDebug() << Q_FUNC_INFO << QString::fromUtf8("Erreur : %1 pour la requête %2").arg(r.lastError().text()).arg(idronde);
        }
    }
    return retour;
}
/**
 * @brief BaseBDD::recupererRonde
 * @param _idAgent permet de récuperer l'id de l'agent
 * @param _donnees étant la liste des rondes
 * Cette fonction permet de récuperer la liste des rondes en fonction de l'id de l'agent.
 * @return
 */
bool BaseBDD::recupererRonde(int _idAgent, QStringList &_donnees)
{
    bool retour = false;
    if(DB.isOpen())
    {
        QSqlQuery r(DB.database());
        r.prepare("select nomRonde from Ronde;"); //where idAgent = :idagent;
        r.bindValue(":idagent", _idAgent);
        if(r.exec()) {
            while(r.next()) {
                _donnees << r.value("nomRonde").toString();
                retour = true;
            }
        } else {
            qDebug() << Q_FUNC_INFO << "problème d'ouverture";
        }
    }
    return retour;
}
/**
 * @brief BaseBDD::recupererIdRonde
 * @param nomRonde permet de récuperer le nom de la ronde du combobox.
 * Cette fonction permet de récuperer l'id de la ronde.
 * @return
 */
bool BaseBDD::recupererIdRonde(QString nomRonde)
{
    bool retour = false;
    qDebug() << Q_FUNC_INFO << nomRonde;
    if(DB.isOpen())
    {
        QSqlQuery r(DB.database());
        r.prepare("select idRonde from Ronde where nomRonde like :nom ;");
        r.bindValue(":nom", nomRonde);
        qDebug() << Q_FUNC_INFO << nomRonde;
        if(r.exec()){
            qDebug() << Q_FUNC_INFO << "Dans la boucle r.exec() idronde = " << idronde;
            if(r.next()) {
                idronde = r.value("idRonde").toInt();
                qDebug() << Q_FUNC_INFO << idronde;
                retour = true;
            } else {
                qDebug() << Q_FUNC_INFO << "Probème boucle r.next";
            }
        } else {
            qDebug() << Q_FUNC_INFO << "problème r.exec";
        }
    }
    return  retour;
}
