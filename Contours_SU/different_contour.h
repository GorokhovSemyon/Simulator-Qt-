#ifndef DIFFERENT_CONTOUR_H
#define DIFFERENT_CONTOUR_H
#include "su_coreblock.h"

extern float K[SIZE_OF_K];
extern float X[SIZE_OF_X][2];


class different_contour
{
public:
    different_contour(float delta);

    ComputingBlock* coreBlock;
    SU_CoreBlock* core_SU;

    unsigned short int highfreq_ims_reinit=1;
    float U_diff;
    float delta_t;

    void main_block(float Input, int Regim, int flagUpravleniya);
    void Different_scheme_mainLogic();
    void core_FeedBack_Distance_Speed();
};

#endif // DIFFERENT_CONTOUR_H
