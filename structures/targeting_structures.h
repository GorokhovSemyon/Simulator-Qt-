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
    }
    float des_Yaw;
    float des_Marsh;
    float des_Depth;
    float depth_U;
    float marsh_U;
    float kurs_U;
};
#pragma pack(pop)

#endif // TARGETING_STRUCTURES_H
