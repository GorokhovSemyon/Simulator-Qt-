#ifndef INSTRUCTOR_STRUCTURE_H
#define INSTRUCTOR_STRUCTURE_H

#include <QObject>

#include "common/defines.h"
#include "common/header.h"

//-----------------------------------------------------------

#pragma pack(push,1)

struct ANPA
{
    ANPA()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
    }
    float X;
    float Y;
    float Z;
};

#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct Flow
{
    Flow()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
    }
    float direction;
    float value;
};

#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct ToInstructor_data
{
    ToInstructor_data()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
    }
    int ok;


};
#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct FromInstructor_data
{
    FromInstructor_data()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
    }
    ANPA anpa;
    Flow flow;

};
#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct FromInstructor_protocol : FromInstructor_data
{
    FromInstructor_protocol()
    {
        header.sender = UNITY_SENDER;
        header.messtype = QT_UNITY_INIT_MESSTYPE;
    }
    Header header;

};
#pragma pack(pop)

//-----------------------------------------------------------

#pragma pack(push,1)

struct ToInstructor_protocol : ToInstructor_data
{
    ToInstructor_protocol()
    {
        header.sender = QT_SENDER;
        header.messtype = QT_UNITY_INIT_MESSTYPE;
    }
    Header header;

};
#pragma pack(pop)

#endif // INSTRUCTOR_STRUCTURE_H
