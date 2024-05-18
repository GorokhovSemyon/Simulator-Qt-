#ifndef SIMULATOR_STRUCTURE_H
#define SIMULATOR_STRUCTURE_H

#include <QObject>

#include "common/defines.h"
#include "common/header.h"

//-----------------------------------------------------------

#pragma pack(push,1)
struct Voltage_VMA
{
    Voltage_VMA()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
    }
    float U;

};
#pragma pack(pop)

struct VMAdata                                   ///---Текущие данные с ВМА; CommunicationQuality - качество связи ТНПА с ВМА
    {
     VMAdata()                                  ///---Конструктор по умолчанию
         {
            memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
         }                                      ///---Режим управления
     float U;                                   ///---Задающее воздействие (напряжение)
     float SensorVMA;                           ///---Неисправности движителей

    };

//-----------------------------------------------------------

#pragma pack(push,1)
struct Motion_Param
{
    Motion_Param()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
    }
        ///Координаты ПА
        float X;
        float Y;
        float Z;

        ///Углы ориентации ПА
        float Psi;
        float Gamma;
        float Tetta;

        ///Линейная скорость ПА
        float Vx;
        float Vy;
        float Vz;

        ///Угловая скорость ПА
        float Wx;
        float Wy;
        float Wz;
};
#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct ToSimulator_data
{
    ToSimulator_data(){}

    Voltage_VMA voltage[5];
};

#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct FromSimulator_data
{
    FromSimulator_data(){}

    Motion_Param params;
    VMAdata vma[5];
};

#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)
struct ToSimulator_protocol : ToSimulator_data
{
    ToSimulator_protocol()
    {
        header.sender = QT_SENDER;
        header.messtype = QT_UNITY_MAIN_MESSTYPE;
    }
    Header header;

};
#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)
struct FromSimulator_protocol : FromSimulator_data
{
    FromSimulator_protocol()
    {
        header.sender = UNITY_SENDER;
        header.messtype = QT_UNITY_MAIN_MESSTYPE;
    }
    Header header;
};
#pragma pack(pop)


#endif // SIMULATOR_STRUCTURE_H
