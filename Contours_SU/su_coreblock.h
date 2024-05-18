#ifndef SU_COREBLOCK_H
#define SU_COREBLOCK_H
#include <QObject>
#include "../gamak_protocols/common/define.h"

extern float K[SIZE_OF_K];
extern float X[SIZE_OF_X][2];

class SU_CoreBlock : public QObject
{
public:
    SU_CoreBlock(float delta);

    unsigned short int highfreq_ims_reinit=1;
    float delta_t;

    void sensor_filter(float Tau, float Td, float *Data, float *DataF, int reinit_filter); ///----Функция фильтра. На схемах - Wф
    void core_EulerAngleSpeed(); ///---пересчитывает локальную угловую скорость ПА в глобальную
    void setSpeedInLocalAxis_EulerKrilovMatrix(int Regim); ///--совместная работа движителей при больших углах дифферента
    void set_Local_or_Global_AngleSpeed(); ///---при наличии больших углов дифференета переключает локальную угловую скорость на глобальную

};

#endif // SU_COREBLOCK_H
