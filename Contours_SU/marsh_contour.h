#ifndef MARSH_CONTOUR_H
#define MARSH_CONTOUR_H

#include "math.h"

#include "common/exchange_structures.h"


class Marsh_contour
{
public:
    Marsh_contour(Exchange_structures *_exch_str);

    Exchange_structures* exch_str;

    unsigned short int highfreq_ims_reinit=1;
    float U_marsh = 0;
    float delta_t;
    float distance; ///---расчитываемый радиус стабилизации
    bool navigate_complete; ///--- флаг о завершении алгоритма наведения

    void main_block();
};


#endif // MARSH_CONTOUR_H
