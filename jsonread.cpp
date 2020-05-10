#include "jsonread.h"
JsonRead::JsonRead()
{

}

/*
 * Funkce pro zpracovani vstupniho souboru
 */
void JsonRead::ReadJson(QVector<Stop>* stopVector, QVector<Street*>* streetVector, QVector <Path>* pathVector)
{

//    QDir dir = dir.currentPath();
//    qDebug() << dir;
//   //QString srt = dir.toString();
//    QFileInfo fi(dir, "inputFile.json");
//    QString canonical = fi.absoluteFilePath();

//    qDebug() << "cesta" << canonical;
//    canonical.replace("build_mhd_projekt","mhd_projekt");
//    qDebug() << "cesta" << canonical;

    QString val;
    QFile file;
    file.setFileName("../inputFile.json");
    if (!file.exists())
    {
        qDebug() << "Vstupni soubor se neporadilo otevrit";
        exit(-10);
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = doc.object();

    // Streeet
    QJsonArray streetArray = obj["street"].toArray();
    for(int i = 0; i < streetArray.size(); i++)
    {
        QJsonObject streetAllO= streetArray[i].toObject();

        QJsonValue NameV = streetAllO.value(QString("name"));
        streetVector->append(new Street(NameV.toString(), Coordinate(getXorYfrom(streetAllO,"begin","x"),getXorYfrom(streetAllO,"begin","y")), Coordinate(getXorYfrom(streetAllO,"end","x"),getXorYfrom(streetAllO,"end","y"))));
    }

    // Stop
    QJsonArray stopArray = obj["stop"].toArray();
    for(int i = 0; i < stopArray.size(); i++)
    {
        QJsonObject stopAllO= stopArray[i].toObject();
        QJsonValue NameV = stopAllO.value(QString("name"));
        stopVector->append(Stop(NameV.toString(), Coordinate(getXorYfrom(stopAllO,"position","x"), getXorYfrom(stopAllO,"position","y"))));
    }

    // Path
    QJsonArray pathArray = obj["path"].toArray();
    for(int i = 0; i < pathArray.size(); i++)
    {
         QJsonObject pathAllO= pathArray[i].toObject();

         //Prevedeni seznamu ulic do vektoru
         QJsonArray streetNamsesArray = pathAllO["streetNames"].toArray();
         QVector<QString> streetNamesVector;
         for(int j = 0; j < streetNamsesArray.size(); j++)
         {
             streetNamesVector.append(streetNamsesArray[j].toString());
         }

         //Ziskani sbylych promennych
         QJsonValue interval = pathAllO.value(QString("interval"));
         QJsonValue linkName = pathAllO.value(QString("linkName"));
         QJsonValue speed = pathAllO.value(QString("speed"));

         pathVector->append(Path(streetNamesVector,(speed.toString().toDouble()),linkName.toString().toDouble(),interval.toString().toDouble(), rand() % 16770000));
    }


}

/*
 * Funkce vracejici pozadovanou souradnici z daneho objektu
 */
double JsonRead::getXorYfrom(QJsonObject Object, QString name, QString XorY)
{
    //Zapis normalniho programatora
    QJsonValue value = Object.value(QString(name));
    QJsonObject Object2 = value.toObject();
    QJsonValue x = Object2.value(QString(XorY));
    return x.toString().toDouble();
}


