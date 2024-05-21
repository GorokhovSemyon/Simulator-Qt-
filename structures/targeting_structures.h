#ifndef TARGETING_STRUCTURES_H
#define TARGETING_STRUCTURES_H

#include <QObject>

#include "common/defines.h"

#pragma pack(push,1)

struct TargetingParams
{
    TargetingParams()
    {
        memset(this, 0, sizeof(*this));    ///---Обнуление всех членов структуры
        target_radius = 5;
        des_Y = 50;
    }
    float des_Yaw;
    float des_X;
    float des_Y;
    float des_Z;
    float depth_U;
    float marsh_U;
    float kurs_U;
    float target_radius;
    int targeting_method;
    bool navigate_complete;
};
#pragma pack(pop)

#endif // TARGETING_STRUCTURES_H
