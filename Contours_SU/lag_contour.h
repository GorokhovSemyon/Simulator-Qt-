#ifndef LAG_CONTOUR_H
#define LAG_CONTOUR_H
#include "su_coreblock.h"

extern float K[SIZE_OF_K];
extern float X[SIZE_OF_X][2];

class lag_contour
{
public:
    lag_contour(float delta);

    ComputingBlock *coreBlock;
    SU_CoreBlock* core_SU;

    unsigned short int highfreq_ims_reinit=1;
    float delta_t;
    float U_lag;

    void main_block(float Input, int Regim, int flagUpravleniya, int type_control);
    void Lag_po_SVS();
    void Lag_po_AL();
    void core_FeedBack_Distance_Speed();
};

#endif // LAG_CONTOUR_H
