#include "protocol_instructor.h"

Protocol_Instructor::Protocol_Instructor(ConfigData *config, const QString name, QObject *parent) : QObject(parent)
{
    config -> getValue(name);

    ip_Unity = new QHostAddress(config -> data.sender_ip);
    port_Unity = (quint16)(config -> data.sender_port);
    writesocket = new QUdpSocket(this);

    port_Qt = (quint16)(config -> data.receiver_port);
    incomingsocket = new QUdpSocket(this);
    incomingsocket -> bind(port_Qt);

    frequency = config -> data.receiver_frequency;
    timer = new QTimer();

    lost_message_count = 0;

    received = 0;
    preceived = 0;
    lost_message_count = 0;

    qDebug() << "frequency = " << frequency;

    connect(incomingsocket,&QUdpSocket::readyRead, this,&Protocol_Instructor::receive_data);
    connect(timer, &QTimer::timeout, this, &Protocol_Instructor::send_data);
}

void Protocol_Instructor::send_data()
{
    qDebug() << "Sending data..."<<port_Unity;

    to_data.header.checksum =  Crc32(reinterpret_cast<unsigned char*>(&to_data.anpa), sizeof(FromInstructor_data));
    /*qDebug() << */writesocket -> writeDatagram(reinterpret_cast<char*>(&to_data), sizeof(to_data), QHostAddress::LocalHost, port_Unity);
    // qDebug()<< writesocket->errorString();
}

void Protocol_Instructor::receive_data()
{
    QByteArray baDatagram;

    ToInstructor_protocol got_message;

    do
        {
         baDatagram.resize(incomingsocket -> pendingDatagramSize());
         incomingsocket -> readDatagram(baDatagram.data(), baDatagram.size());
        }
    while(incomingsocket -> hasPendingDatagrams());

     //Обработка пришедшего пакета:

    QDataStream stream(baDatagram);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> got_message.header.sender
        >> got_message.header.messtype
        >> got_message.header.checksum
        >> got_message.ok;

    //проверяем по хэдеру что за пакет получили

    if ((got_message.header.sender == UNITY_SENDER) && (got_message.header.messtype == QT_UNITY_MAIN_MESSTYPE))
         {
          uint_least32_t check;
          check = Crc32(reinterpret_cast<unsigned char*>(&got_message.ok), sizeof(got_message.ok));

        if (check == got_message.header.checksum)
            {
             memcpy(&from_data,baDatagram.data(),sizeof(ToInstructor_protocol));

             received++;

             emit start_main_exchange();
            }
        else
            {
             qDebug() << "Protocol_Instructor::receive_data(): Error checksum BAU!: check == " << check << " checksum == " << got_message.header.checksum << endl;
             lost_message_count++;
            }
        }
    else
        {
         qDebug() << "Protocol_Instructor::receive_data(): Error header BAU!: sender == " <<got_message.header.sender << " messtype == " << got_message.header.messtype << endl;
         lost_message_count++;
        }
}
