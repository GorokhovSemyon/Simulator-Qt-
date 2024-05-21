#include "marsh_contour.h"

Marsh_contour::Marsh_contour(Exchange_structures *_exch_str)
{
    exch_str = _exch_str;
}

void Marsh_contour::main_block()
{
    float Kout =1;
    float delta_x = exch_str->target_params.des_X - exch_str->from_data.params.X;
    float delta_z = exch_str->target_params.des_Z - exch_str->from_data.params.Z;
    distance = sqrt(pow(delta_x,2) + pow(delta_z,2));

    exch_str->target_params.marsh_U = (distance > exch_str->target_params.target_radius ? 1 : 0) * Kout; //10 - максимальное напряжение
    exch_str->target_params.navigate_complete = (distance > exch_str->target_params.target_radius ? false : true);

//    qDebug() << "distance == " << distance;
//    qDebug() << "exch_str->target_params.des_X == " << exch_str->target_params.des_X;
//    qDebug() << "exch_str->from_data.params.X == " << exch_str->from_data.params.X;
//    qDebug() << "exch_str->from_data.params.Y == " << exch_str->from_data.params.Y;
//    qDebug() << "exch_str->target_params.marsh_U == " << exch_str->target_params.marsh_U;

}
