#ifndef JSONREAD_H
#define JSONREAD_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QDebug>
#include <QJsonArray>


class JsonRead
{
public:
    JsonRead();
    void ReadJson();
    double getXorYfrom(QJsonObject Object, QString name, QString XorY);
};

#endif // JSONREAD_H
