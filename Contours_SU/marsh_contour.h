#ifndef MARSH_CONTOUR_H
#define MARSH_CONTOUR_H
//#include "../gamak_protocols/common/define.h"
//#include "computingblock.h"
//#include "../gamak_protocols/protocolFromPult.h"
//#include "navigationalgoritm.h"
//#include "su_coreblock.h"

//extern float K[SIZE_OF_K];
//extern float X[SIZE_OF_X][2];


class Marsh_contour
{
public:
    Marsh_contour(float delta);

//    ComputingBlock *coreBlock;
//    NavigationAlgoritm* nav_algorithm;
//    SU_CoreBlock* core_SU;

    unsigned short int highfreq_ims_reinit=1;
    float U_marsh;
    float delta_t;
    float* target_radius; ///---расчитываемый радиус стабилизации
    bool accept_workDepthMArshTogerther;
    bool navigate_complete; ///--- флаг о завершении алгоритма наведения

    void main_block(float Input, int Regim, int flagUpravleniya, int type_control);
    void Marsh_po_SVS();
    void Marsh_po_AL();
    void core_FeedBack_Distance_Speed();

//    void setTargetParam(PointTargetingParameters *value);

//private:
//    PointTargetingParameters* targetParam;
};


#endif // MARSH_CONTOUR_H
