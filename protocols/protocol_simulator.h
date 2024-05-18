#ifndef PROTOCOL_SIMULATOR_H
#define PROTOCOL_SIMULATOR_H

#include <QObject>
#include <QtNetwork>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QTcpSocket>
#include <QDebug>

#include "structures/simulator_structure.h"
#include "common/configdata.h"
#include "common/crc32checksum.h"

class Protocol_Simulator : public QObject
{
    Q_OBJECT
public:
    explicit Protocol_Simulator(ConfigData *config, const QString name, QObject *parent = nullptr);

    ToSimulator_protocol to_data;
    FromSimulator_protocol from_data;

    QHostAddress *ip_Unity = nullptr;
    quint16  port_Unity;
    quint16  port_Qt;
    qint32 frequency;
    QUdpSocket *incomingsocket;
    QUdpSocket *writesocket;
    QTimer* timer;

    long int received;
    long int preceived;
    int lost_message_count;

signals:
    void set_data();
    void get_data();

public slots:
    void send_data();
    void receive_data();

};

#endif // PROTOCOL_SIMULATOR_H
