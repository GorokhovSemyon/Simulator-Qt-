#include "protocol_simulator.h"

Protocol_Simulator::Protocol_Simulator(ConfigData *config, const QString name, QObject *parent) : QObject(parent)
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

    connect(incomingsocket,&QUdpSocket::readyRead, this,&Protocol_Simulator::receive_data);
    connect(timer, &QTimer::timeout, this, &Protocol_Simulator::send_data);

    // timer -> start(int(1000./frequency));
}

void Protocol_Simulator::send_data()
{
    emit get_data();
    qDebug() << "Sending data..."<<port_Unity;

    to_data.header.checksum =  Crc32(reinterpret_cast<unsigned char*>(&to_data.voltage), sizeof(ToSimulator_data));
    /*qDebug() << */writesocket -> writeDatagram(reinterpret_cast<char*>(&to_data), sizeof(to_data), QHostAddress::LocalHost, port_Unity);
    // qDebug()<< writesocket->errorString();
}

void Protocol_Simulator::receive_data()
{
    QByteArray baDatagram;

    FromSimulator_protocol got_message;

    do
    {
        baDatagram.resize(incomingsocket->pendingDatagramSize());
        incomingsocket->readDatagram(baDatagram.data(), baDatagram.size());
    } while (incomingsocket->hasPendingDatagrams());

    QDataStream stream(baDatagram);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> got_message.header.sender
        >> got_message.header.messtype
        >> got_message.header.checksum;

    stream.readRawData(reinterpret_cast<char*>(&got_message.params.X), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Y), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Z), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Psi), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Gamma), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Tetta), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Vx), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Vy), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Vz), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Wx), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Wy), sizeof(float));
    stream.readRawData(reinterpret_cast<char*>(&got_message.params.Wz), sizeof(float));


    for (int i = 0; i < 5; ++i) {
        stream.readRawData(reinterpret_cast<char*>(&got_message.vma[i].U), sizeof(float));
        stream.readRawData(reinterpret_cast<char*>(&got_message.vma[i].SensorVMA), sizeof(float));
    }

    qDebug() << "Params.X ="<<got_message.params.X;
    qDebug() << "Params.Y ="<<got_message.params.Y;
    qDebug() << "Params.Z ="<<got_message.params.Z;
    qDebug() << "Params.Psi ="<<got_message.params.Psi;
    qDebug() << "Params.Gamma ="<<got_message.params.Gamma;
    qDebug() << "Params.Tetta ="<<got_message.params.Tetta;
    // qDebug() << "Params.Vx ="<<got_message.params.Vx;
    // qDebug() << "Params.Vy ="<<got_message.params.Vy;
    // qDebug() << "Params.Vz ="<<got_message.params.Vz;
    // qDebug() << "Params.Wx ="<<got_message.params.Wx;
    // qDebug() << "Params.Wy ="<<got_message.params.Wy;
    // qDebug() << "Params.Wz ="<<got_message.params.Wz;
    // qDebug() << "vma[0].U ="<<got_message.vma[0].U;
    // qDebug() << "vma[0].SensorVMA ="<<got_message.vma[0].SensorVMA;
    // qDebug() << "vma[1].U ="<<got_message.vma[1].U;
    // qDebug() << "vma[1].SensorVMA ="<<got_message.vma[1].SensorVMA;
    // qDebug() << "vma[2].U ="<<got_message.vma[2].U;
    // qDebug() << "vma[2].SensorVMA ="<<got_message.vma[2].SensorVMA;
    // qDebug() << "vma[3].U ="<<got_message.vma[3].U;
    // qDebug() << "vma[3].SensorVMA ="<<got_message.vma[3].SensorVMA;
    // qDebug() << "vma[4].U ="<<got_message.vma[4].U;
    // qDebug() << "vma[4].SensorVMA ="<<got_message.vma[4].SensorVMA;
    // qDebug() << "vma[5].U ="<<got_message.vma[5].U;
    // qDebug() << "vma[5].SensorVMA ="<<got_message.vma[5].SensorVMA;
    // qDebug() << "vma[6].U ="<<got_message.vma[6].U;
    // qDebug() << "vma[6].SensorVMA ="<<got_message.vma[6].SensorVMA;
    // qDebug() << "vma[7].U ="<<got_message.vma[7].U;
    // qDebug() << "vma[7].SensorVMA ="<<got_message.vma[7].SensorVMA;

    // Проверяем по хэдеру что за пакет получили
    if ((got_message.header.sender == UNITY_SENDER) && (got_message.header.messtype == QT_UNITY_MAIN_MESSTYPE))
    {
        uint_least32_t check;
        check = Crc32(reinterpret_cast<unsigned char*>(&got_message.params), sizeof(got_message.params) + sizeof(got_message.vma));

        if (check == got_message.header.checksum)
        {

            from_data = got_message;

            received++;
        }
        else
        {
            qDebug() << "from Protocol_BAU::receive_data(): Error checksum BAU!: check == " << check << " checksum == " << got_message.header.checksum << endl;
            lost_message_count++;
        }
    }
    else
    {
        qDebug() << "from Protocol_BAU::receive_data(): Error header BAU!: sender == " << got_message.header.sender << " messtype == " << got_message.header.messtype << endl;
        lost_message_count++;
    }

    emit set_data();
}
