#ifndef KURS_CONTOUR_H
#define KURS_CONTOUR_H
//#include "../gamak_protocols/common/define.h"
//#include "computingblock.h"
//#include "../gamak_protocols/protocolFromPult.h"
//#include "navigationalgoritm.h"
//#include "su_coreblock.h"

//extern float K[SIZE_OF_K];
//extern float X[SIZE_OF_X][2];


class kurs_contour /*: public QObject*/
{
public:
    kurs_contour(float delta);
//    NavigationAlgoritm* nav_algorithm;
//    SU_CoreBlock* core_SU;

    unsigned short int highfreq_ims_reinit=1;
    float U_kurs;
    float delta_t;
    float target_radius; ///---Рассчитываемое расстояние до объекта, сравнивается с заданным радиусом стабилизации
                         ///---Для определения завершения навигации

    void main_block(float Input, int Regim, int flagUpravleniya, float counter);
    void Kurs_scheme_mainLogic();
    void core_FeedBack_Distance_Speed();

//    void setTargetParam(PointTargetingParameters *value);

//private:

//    PointTargetingParameters* targetParam;
};

#endif // KURS_CONTOUR_H
