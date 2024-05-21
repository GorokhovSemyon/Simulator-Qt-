#ifndef KURS_CONTOUR_H
#define KURS_CONTOUR_H

#include <QDebug>
#include <math.h>

#include "common/exchange_structures.h"

class kurs_contour : public QObject
{
public:
    kurs_contour(Exchange_structures *_exch_str);

    Exchange_structures* exch_str;

    unsigned short int highfreq_ims_reinit=1;
    float U_kurs = 0;
    float delta_t;
    float distance;

    void main_block();
    float Kurs_scheme_mainLogic();
    void core_FeedBack_Distance_Speed();

    float calc_hover_algorithm();
    float calc_successive_lead_method();
    float calc_target_setting_method();
};

#endif // KURS_CONTOUR_H
