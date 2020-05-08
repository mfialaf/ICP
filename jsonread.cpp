#include "jsonread.h"
JsonRead::JsonRead()
{

}

void JsonRead::ReadJson(QVector<Stop>* stopVector, QVector<Street>* streetVector, QMap <double, Path>* pathMap)
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
        qDebug() << "Kokotsky soubor se neotevrel";
    }
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    //qDebug() << val;

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = doc.object();

    // Streeet
    QJsonArray streetArray = obj["street"].toArray();
    for(int i = 0; i < streetArray.size(); i++)
    {
        QJsonObject streetAllO= streetArray[i].toObject();

        QJsonValue NameV = streetAllO.value(QString("name"));
        streetVector->append(Street(NameV.toString(), Coordinate(getXorYfrom(streetAllO,"begin","x"),getXorYfrom(streetAllO,"begin","y")), Coordinate(getXorYfrom(streetAllO,"end","x"),getXorYfrom(streetAllO,"end","y"))));
     //   qDebug() << "nazev + start konec x y jsou: " << NameV.toString() << getXorYfrom(streetAllO,"begin","x") << getXorYfrom(streetAllO,"begin","y") << getXorYfrom(streetAllO,"end","x") << getXorYfrom(streetAllO,"end","y");
    }

    // Stop
    QJsonArray stopArray = obj["stop"].toArray();
    for(int i = 0; i < stopArray.size(); i++)
    {
        QJsonObject stopAllO= stopArray[i].toObject();
        QJsonValue NameV = stopAllO.value(QString("name"));
        stopVector->append(Stop(NameV.toString(), Coordinate(getXorYfrom(stopAllO,"position","x"), getXorYfrom(stopAllO,"position","y"))));
        //qDebug() << "nazev zastavky + start konec x y jsou: " << NameV.toString() << getXorYfrom(stopAllO,"position","x") << getXorYfrom(stopAllO,"position","y");
    }

    // Path
    QJsonArray pathArray = obj["path"].toArray();
    for(int i = 0; i < pathArray.size(); i++)
    {
         QJsonObject pathAllO= pathArray[i].toObject();

         QJsonValue interval = pathAllO.value(QString("interval"));
         QJsonValue vehicleCount = pathAllO.value(QString("vehicleCount"));
         QJsonValue linkName = pathAllO.value(QString("linkName"));
         QJsonValue speed = pathAllO.value(QString("speed"));

         QJsonArray streetNamsesArray = pathAllO["streetNames"].toArray();
         QVector<QString> streetNamesVector;
        // for (int i: streetNamsesArray)
         //streetNamesVector.insert(streetNamesVector.begin(), std::begin(streetNamsesArray), std::end(streetNamsesArray));
         for(int j = 0; j < streetNamsesArray.size(); j++)
         {
                qDebug() << "JmenaUlic: " << streetNamsesArray[j].toString();
         }
         qDebug() << "interval + vehicleCount + linkName + speed" << interval.toString().toDouble() << vehicleCount.toString().toDouble() << linkName.toString().toDouble() << speed.toString().toDouble();
    }


}

double JsonRead::getXorYfrom(QJsonObject Object, QString name, QString XorY)
{
    //Zapis normalniho programatora
    QJsonValue value = Object.value(QString(name));
    QJsonObject Object2 = value.toObject();
    QJsonValue x = Object2.value(QString(XorY));
    return x.toString().toDouble();

    //Zapis Borise
    //return Object.value(QString(name)).toObject().value(QString(XorY)).toString().toDouble();
}


