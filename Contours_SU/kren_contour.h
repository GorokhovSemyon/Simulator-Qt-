#ifndef KREN_CONTOUR_H
#define KREN_CONTOUR_H
#include "su_coreblock.h"

extern float K[SIZE_OF_K];
extern float X[SIZE_OF_X][2];



class kren_contour
{
public:
    kren_contour(float delta);

    ComputingBlock *coreBlock;
    SU_CoreBlock* core_SU;

    unsigned short int highfreq_ims_reinit=1;
    float U_kren;
    float delta_t;

    void main_block(float Input, int Regim, int flagUpravleniya);
    void Kren_scheme_mainLogic();
    void core_FeedBack_Distance_Speed();
};

#endif // KREN_CONTOUR_H
