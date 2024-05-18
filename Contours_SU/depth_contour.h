#ifndef DEPTH_CONTOUR_H
#define DEPTH_CONTOUR_H

//#include "../gamak_protocols/protocolFromPult.h"

//#include "../gamak_protocols/common/define.h"
//#include "computingblock.h"
//#include "su_coreblock.h"

//extern float K[SIZE_OF_K];
//extern float X[SIZE_OF_X][2];

#include "common/exchange_structures.h"

class depth_contour
{
public:
    depth_contour(Exchange_structures *_exch_str);
//    SU_CoreBlock* core_SU;

    Exchange_structures* exch_str;

    unsigned short int highfreq_ims_reinit=1;
    float delta_t;
    float U_depth;
    float H_or_h, H_or_h_previos;
    int prev_nav_flag;
    int prev_depth_contour;
    bool accept_workDepthMArshTogerther;
    bool nav_depth_set; //Определна глубина/отстование следования при наведении

    float currDepth;

    void main_block();
    void po_glubine(int flagUpravleniya, int Regim);
    void po_otstoyaniu(int flagUpravleniya, int Regim);
    void core_FeedBack_Distance_Speed();

//    void setTargetParam(PointTargetingParameters *value);

//private:

//    PointTargetingParameters* targetParam;
};

#endif // DEPTH_CONTOUR_H
