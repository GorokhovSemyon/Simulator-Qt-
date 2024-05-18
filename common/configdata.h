#ifndef CONFIGDATA_H
#define CONFIGDATA_H

/*
Это разбор наших конфигов. Считаю этот класс полностью отлаженным и не требующим никакой доработки
*/

#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QObject>
#include <QDebug>

struct Data
{
    QString macadress;
    QString ipadress;
    QString device;
    QString calibration;
    QString sender_ip;
    QString receiver_ip;
    float   device_frequency;
    qint32  baudRate;
    qint32  sender_port;
    qint32  receiver_port;
    float  sender_frequency;
    float  receiver_frequency;
    quint8  type;
    quint8  addr_x;
    quint8  addr_k;
    quint8  addr_pult;
    quint16 count;
    QString ki_file;
    quint8 pulttype;

///--- Добавлено
    QString tvs_file;           //Имя файла с настройками конфигураций телекамер аппарата и МТНПА
};

class ConfigData : public QObject
{
   Q_OBJECT

public:
    ConfigData(const QString & configFile, QObject *parent = 0);
    ConfigData(const QString & configFile, const QString &name, QObject *parent = 0);
    ~ConfigData();

    Data data;

    void getValue(const QString & name);

private:
    QTextStream  standardOutput;
    QFile  dataFile;
    QStringList list;
    int jmax;
};

#endif // CONFIGDATA_H
