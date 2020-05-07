#include "jsonread.h"
JsonRead::JsonRead()
{

}

void JsonRead::ReadJson()
{

    QString val;
    QFile file("/home/mrfal/SKOLA/ICP/mhd_projekt/inputFile.json");
   //file.setFileName("./inputFile.json");
    if (!file.exists()) qDebug() << "Kokotsky soubor se neotevrel";
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();

    //qDebug() << val;

    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject obj = doc.object();

    QJsonArray streetArray = obj["street"].toArray();
    for(int i = 0; i < streetArray.size(); i++)
    {
        QJsonObject streetAllO= streetArray[i].toObject();

        QJsonValue NameV = streetAllO.value(QString("name"));
        qDebug() << "nazev + start konec x y jsou: " << NameV.toString() << getXorYfrom(streetAllO,"begin","x") << getXorYfrom(streetAllO,"begin","y") << getXorYfrom(streetAllO,"end","x") << getXorYfrom(streetAllO,"end","y");
    }

    QJsonArray stopArray = obj["stop"].toArray();
    for(int i = 0; i < stopArray.size(); i++)
    {
        QJsonObject stopAllO= stopArray[i].toObject();

        QJsonValue NameV = stopAllO.value(QString("name"));
        qDebug() << "nazev zastavky + start konec x y jsou: " << NameV.toString() << getXorYfrom(stopAllO,"position","x") << getXorYfrom(stopAllO,"position","y");
    }

    QJsonArray pathArray = obj["path"].toArray();
    for(int i = 0; i < pathArray.size(); i++)
    {
         QJsonObject pathAllO= pathArray[i].toObject();

         QJsonValue interval = pathAllO.value(QString("interval"));
         QJsonValue vehicleCount = pathAllO.value(QString("vehicleCount"));

         QJsonArray streetNamsesArray = pathAllO["streetNames"].toArray();
         for(int j = 0; j < streetNamsesArray.size(); j++)
         {
                qDebug() << "JmenaUlic: " << streetNamsesArray[j].toString();
         }
         qDebug() << "interval + vehicleCount" << interval.toString().toDouble() << vehicleCount.toString().toDouble();
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


