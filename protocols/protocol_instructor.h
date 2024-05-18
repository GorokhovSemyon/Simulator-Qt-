#ifndef PROTOCOL_INSTRUCTOR_H
#define PROTOCOL_INSTRUCTOR_H

#include <QObject>
#include <QtNetwork>
#include <QTextStream>
#include <QTimer>
#include <QByteArray>
#include <QTcpSocket>
#include <QDebug>

#include "structures/instructor_structure.h"
#include "common/configdata.h"
#include "common/crc32checksum.h"

class Protocol_Instructor : public QObject
{
    Q_OBJECT
public:
    explicit Protocol_Instructor(ConfigData *config, const QString name, QObject *parent = nullptr);

    FromInstructor_protocol to_data;
    ToInstructor_protocol from_data;

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
    void start_main_exchange();


public slots:
    void send_data();
    void receive_data();

};

#endif // PROTOCOL_INSTRUCTOR_H
