#ifndef HEADER_H
#define HEADER_H

#include <QObject>

#pragma pack (push, 1)

struct Header
    {
     Header()                         ///---Конструктор по умолчанию
        {
            memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
        }
     int sender;
     int messtype;
     uint32_t checksum;
    };
#pragma pack(pop)

#endif // HEADER_H
