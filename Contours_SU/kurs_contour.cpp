#include "kurs_contour.h"

kurs_contour::kurs_contour(Exchange_structures *_exch_str)
{
    exch_str = _exch_str;
    distance = 0;
}

void kurs_contour::main_block()
{
    float sumErr = 0;
    float corrSumErr = 0;
    float midSumOut = 0;

    float K1 = 1;
    float K2 = 1;
    float Kc = 57.3;
    float kConvert = 0.1;

    switch (exch_str->target_params.targeting_method)
    {
    case 0:      //  Погоня
       exch_str->target_params.des_Yaw = calc_hover_algorithm();
       break;
    case 1:      // Упреждение
       exch_str->target_params.des_Yaw = calc_successive_lead_method();
       break;
    case 2:      // Линия визирования
       exch_str->target_params.des_Yaw = calc_target_setting_method();
       break;

    default:
       break;
    }

    if (!exch_str->target_params.navigate_complete)
    sumErr = exch_str->target_params.des_Yaw - exch_str->from_data.params.Psi;

    if (sumErr < -180) sumErr = 360 + sumErr;
    else if (sumErr > 180) sumErr = -360 + sumErr;

    if (abs(sumErr) < 3) sumErr = 0;

    corrSumErr = sumErr * K1;

    //От датчиков
    midSumOut = corrSumErr - exch_str->from_data.params.Wy * K2;

    exch_str->target_params.kurs_U = corrSumErr * kConvert;
}

float kurs_contour::calc_hover_algorithm()
{
    float delta_x = exch_str->target_params.des_X - exch_str->from_data.params.X;
    float delta_z = exch_str->target_params.des_Z - exch_str->from_data.params.Z;
//    distance = sqrt(pow(delta_x,2) + pow(delta_y,2));

    qDebug() << "delta_x" << delta_x;
    qDebug() << "delta_z" << delta_z;

    qDebug() << "qAtan2(delta_z,delta_x)*180/M_PI == " << (qAtan2(delta_z,delta_x)*180/M_PI);

    if (delta_z < 0)
    {
        return 360 + qAtan2(delta_z,delta_x)*180/M_PI;
    }
    else
    {
        return qAtan2(delta_z,delta_x)*180/M_PI;
    }
}

float kurs_contour::calc_successive_lead_method()
{
//    stop_radius = sqrt(pow(delta_x,2) + pow(delta_z,2));

//    global_speed_PA = sqrt(pow(X[205][0],2) + pow(X[159][0],2));

//    X[608][0] = alpha_nav = sign(X[159][0])*(acos(X[205][0]/global_speed_PA))*57.3;
//    X[609][0] = betta_nav = sign(delta_z)*(acos(delta_x/sqrt(pow(delta_x,2) + pow(delta_z,2))))*57.3;

//    X[610][0] = error_angle = alpha_nav - betta_nav;

//    /*==============ОТРИЦАТЕЛЬНЫЙ ПОВОРОТ============*/
//    if ( (X[31][0] < 360*counter) &&  X[31][0] > (-90 + (90 - betta_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + error_angle;
//    }
//    if ( X[31][0] < ((-180 - betta_nav) + 360*counter) && X[31][0] > (360*(counter - 1)) )
//    {
//        X[4][0] = -(betta_nav) + 360*(counter - 1) + error_angle;
//    }
//    if ( X[31][0] < (-90 + (90 - betta_nav) + 360*counter) && X[31][0] > ((-180 - betta_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + error_angle;
//    }

//    if ( X[31][0] < 360*counter && X[31][0] > (-180 + (180 - betta_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + error_angle;
//    }
//    if ( X[31][0] > (-180 + betta_nav + 360*counter) && X[31][0] < (-180 + (180 - betta_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + error_angle;
//    }
//    if ( X[31][0] > 360*(counter - 1) && X[31][0] < ( -180 - betta_nav + 360*counter ) )
//    {
//        X[4][0] = -(alpha_nav) + 360*(counter - 1) + error_angle;
//    }

//    /*==============ПОЛОЖИТЕЛЬНЫЙ ПОВОРОТ============*/
//    if ( X[31][0] < (270 + (90 - betta_nav) + 360*counter) && X[31][0] > (180 - betta_nav + 360*counter) )
//    {
//        X[4][0] = (360 - (alpha_nav)) + 360*counter + error_angle;
//    }
//    if ( X[31][0] < 360*(counter + 1) && X[31][0] > (270 + (90 - betta_nav) + 360*counter) )
//    {
//        X[4][0] = (360 - (alpha_nav)) + 360*counter + error_angle;
//    }
//    if ( X[31][0] > 360*counter && X[31][0] < (180 - betta_nav + 360*counter) )
//    {
//        X[4][0] = (360 - (alpha_nav)) + 360*(counter - 1) + error_angle;
//    }

//    if ( X[31][0] < 360*counter && X[31][0] > (180 + (180 - betta_nav) + 360*counter) )
//    {
//        X[4][0] = (360 - alpha_nav) + 360*counter + error_angle;
//    }
//    if ( X[31][0] < (180 + (180 - betta_nav) + 360*counter) && X[31][0] > (180 - betta_nav + 360*counter) )
//    {
//        X[4][0] = (360 - alpha_nav) + 360*counter + error_angle;
//    }
//    if ( X[31][0] > 360*counter && X[31][0] < (180 - betta_nav + 360*counter) )
//    {
//        X[4][0] = (360 - alpha_nav) + 360*(counter - 1) + error_angle;
//    }

//    if (delta_x == 0) X[4][0] = -sign(delta_z)*(180/2);
//    if (delta_z == 0) X[4][0] = (180/2)*(1 + sign(delta_x)*1);

}

float kurs_contour::calc_target_setting_method()
{

//    stop_radius = sqrt(pow(delta_x,2) + pow(delta_z,2));

//    X[611][0] = prev_x = dynam_su.MotionPapam.X;
//    X[612][0] = prev_z = dynam_su.MotionPapam.Y;

//    X[613][0] = delta_x_prev = prev_x - current_x;
//    X[614][0] = delta_z_prev = prev_z - current_z;

//    global_speed_PA = sqrt(pow(X[205][0],2) + pow(X[159][0],2));

//    try
//    {
//        if (global_speed_PA == 0)
//        {
//            throw 0.000001f;
//        }
//    }
//    catch(float speed)
//    {
//        global_speed_PA = speed;
//    }

//    X[615][0] = tetta_nav = sign(current_z - prev_z)*(acos((current_x - prev_x)/sqrt(pow(current_x - prev_x,2) + pow(current_z - prev_z,2))))*57.3;

//    X[608][0] = alpha_nav = sign(target_z - prev_z)*(acos((target_x - prev_x)/sqrt(pow(target_x - prev_x,2) + pow(target_z - prev_z,2))))*57.3;

//    if (roundf(delta_x_prev*100)/100 != 0 || roundf(delta_z_prev*100)/100 != 0)
//    {
//        vector_ANPA_KP = sqrt(pow(delta_x_prev,2) + pow(delta_z_prev,2));
//        vector_ANPA_target = sqrt(pow(delta_x,2) + pow(delta_z,2));
//        if (vector_ANPA_KP !=0 || vector_ANPA_target !=0)
//        {
//            X[609][0] = betta_nav = acos( (delta_x_prev*delta_x + delta_z_prev*delta_z)/(vector_ANPA_KP*vector_ANPA_target) )*57.3;
//        }
//    }


//    /*==================================
//     *         ВИЗИРОВАНИЕ
//     * ===============================*/
//    X[616][0] = delta_x_Target_KP = prev_x - target_x;
//    X[617][0] = delta_z_Target_KP = prev_z - target_z;

//    vector_Target_ANPA = sqrt(pow(delta_x_Target_ANPA,2) + pow(delta_z_Target_ANPA,2));
//    vector_Target_KP = sqrt(pow(delta_x_Target_KP,2) + pow(delta_z_Target_KP,2));

//    X[618][0] = betta_visor = acos( (delta_x_Target_KP*delta_x_Target_ANPA + delta_z_Target_ANPA*delta_z_Target_KP)/(vector_Target_ANPA*vector_Target_KP) )*57.3;

//    try
//    {
//        if (betta_visor != betta_visor)
//        {
//            throw 0.00000001f;
//        }
//    }
//    catch (float betta_visor_new)
//    {
//        X[618][0] = betta_visor = betta_visor_new;
//    }

//    X[619][0] = X[619][1] + ((0.005/2)*(X[618][0] + X[618][1]));
//    if (X[619][0] > 4) X[619][0] = 4;
//    if (X[619][0] < -4) X[619][0] = -4;
//    X[619][1] = X[619][0];
//    X[618][1] = X[618][0];

//    X[618][0] = betta_visor = (tetta_nav - alpha_nav > 0 ? betta_visor : -betta_visor);

//    /*==============ОТРИЦАТЕЛЬНЫЙ ПОВОРОТ============*/
//    if ( (X[31][0] < 360*counter) && X[31][0] > (-90 + (90 - alpha_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] < ((-180 - alpha_nav) + 360*counter) && X[31][0] > (360*(counter - 1)) )
//    {
//        X[4][0] = -(alpha_nav) + 360*(counter - 1) + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] < (-90 + (90 - alpha_nav) + 360*counter) && X[31][0] > ((-180 - alpha_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + betta_visor + 0.15*X[619][0];
//    }

//    if ( X[31][0] < 360*counter && X[31][0] > (-180 + (180 - alpha_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] > (-180 + alpha_nav + 360*counter) && X[31][0] < (-180 + (180 - alpha_nav) + 360*counter) )
//    {
//        X[4][0] = -(alpha_nav) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] > 360*(counter - 1) && X[31][0] < ( -180 - alpha_nav + 360*counter ) )
//    {
//        X[4][0] = -(alpha_nav) + 360*(counter - 1) + betta_visor + 0.15*X[619][0];
//    }

//    /*==============ПОЛОЖИТЕЛЬНЫЙ ПОВОРОТ============*/
//    if ( X[31][0] < (270 + (90 - alpha_nav) + 360*counter) && X[31][0] > (180 - alpha_nav + 360*counter) )
//    {
//        X[4][0] = (360 - (alpha_nav)) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] < 360*(counter + 1) && X[31][0] > (270 + (90 - alpha_nav) + 360*counter) )
//    {
//        X[4][0] = (360 - (alpha_nav)) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] > 360*counter && X[31][0] < (180 - alpha_nav + 360*counter) )
//    {
//        X[4][0] = (360 - (alpha_nav)) + 360*(counter - 1) + betta_visor + 0.15*X[619][0];
//    }

//    if ( X[31][0] < 360*counter && X[31][0] > (180 + (180 - alpha_nav) + 360*counter) )
//    {
//        X[4][0] = (360 - alpha_nav) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] < (180 + (180 - alpha_nav) + 360*counter) && X[31][0] > (180 - alpha_nav + 360*counter) )
//    {
//      X[4][0] = (360 - alpha_nav) + 360*counter + betta_visor + 0.15*X[619][0];
//    }
//    if ( X[31][0] > 360*counter && X[31][0] < (180 - alpha_nav + 360*counter) )
//    {
//        X[4][0] = (360 - alpha_nav) + 360*(counter - 1) + betta_visor + 0.15*X[619][0];
//    }
}
