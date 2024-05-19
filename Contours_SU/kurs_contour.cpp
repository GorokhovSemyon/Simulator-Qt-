#include "kurs_contour.h"

kurs_contour::kurs_contour(float delta)
{
    delta_t = delta;
    //nav_algorithm = new NavigationAlgoritm();
    target_radius = 10000;
    //core_SU = new SU_CoreBlock(0.05);
}

void kurs_contour::main_block(float Input, int Regim, int flagUpravleniya, float counter)
{
//   core_FeedBack_Distance_Speed();

//   X[12][0] = Input;
//   X[1][0] = X[12][0]*K[1];

//   switch (Regim) ///--- 0 - ручной, 1 - автоматизированный, 3,4 - наведение
//   {

//       case 0:

//           X[16][0] = X[1][0];
//           X[4][0] = X[31][0];

//       break;

//       case 1:
//       case 2:

//           if (flagUpravleniya)
//           {
//               X[2][0] = X[1][0];
//               X[3][0] = X[2][0]*K[2];

//               /*======= ПИ - регулятор ========*/
//               /*==== C ЛБ, замораживающим накапливание =====*/
//               X[4][0]=X[4][1]+((delta_t/2)*(X[3][0]+X[3][1])); ///---ПИ - регулятор
//               if ((U_kurs>=K[9])&&(X[3][0]>0))    X[4][0]=X[4][1]; ///--ЛБ
//               if ((U_kurs<=(-K[9]))&&(X[3][0]<0)) X[4][0]=X[4][1]; ///--ЛБ
//               X[4][1]=X[4][0]; X[3][1]=X[3][0];

//               Kurs_scheme_mainLogic();
//           }
//           else X[16][0] = X[1][0];

//       break;

//       case 3:

//               X[4][0] = X[31][0] - (dynam_su.MotionPapam.dir > 0 ? dynam_su.MotionPapam.dir : dynam_su.MotionPapam.dir);
//               Kurs_scheme_mainLogic();

//       break;
//       case 4:

//           if (dynam_su.MotionPapam.gans_dir > 180)
//           {// так как угол приходит от 0...360 разбиваем окружность на 180град.

//               dynam_su.MotionPapam.gans_dir = -(360 - dynam_su.MotionPapam.gans_dir);

//           }
//           else
//           {
//               dynam_su.MotionPapam.gans_dir = dynam_su.MotionPapam.gans_dir;
//           }

//           //CHECK
//           if (dynam_su.MotionPapam.gans_update_success == true && dynam_su.MotionPapam.gans_dist > targetParam->R)
//           {
//                X[4][0] = X[31][0] - roundf(dynam_su.MotionPapam.gans_dir*10)/10;
//                Kurs_scheme_mainLogic();
//           }
//           else
//           {
//                X[4][0] = X[31][0];
//                Kurs_scheme_mainLogic();
//           }

//       break;

//        case 5:

//               nav_algorithm->updateCounter(counter);
//               //CHECK
//               nav_algorithm->define_delta_XZ(targetParam->X, targetParam->X);
//               //CHECK
//               switch (targetParam->targetingMethod)
//               {
//               case 0:      //  Погоня
//                   nav_algorithm->calc_hover_algorithm(target_radius);
//                   break;
//               case 1:      // Упреждение
//                   nav_algorithm->calc_successive_lead_method(target_radius);
//                   break;
//               case 2:      // Линия визирования
//                   nav_algorithm->calc_target_setting_method(target_radius);
//                   break;

//               default:
//                   break;
//               }

//           Kurs_scheme_mainLogic();

//           break;

//   }
//   U_kurs = X[16][0];
}

void kurs_contour::Kurs_scheme_mainLogic()
{
//    X[6][0] = X[4][0] - X[31][0];

//    if ((K[418] == 1) && (fabs(X[6][0]) > K[417]))
//    {
//        X[922][0] = X[6][0];
//        if (X[922][0] > 0) X[923][0] = K[419];
//        else X[923][0] = K[420];

//        X[6][0] = 0.0f;
//        X[924][0] = 0.0f;
//        X[16][0] = X[923][0];
//    }else
//    {
//        X[7][0] = X[6][0]*K[3];
//        X[8][0] = X[7][0]*K[4];
//        X[1104][0] = K[5] + K[62]/(cos(X[1102][0]/180*3.14)* cos(X[1101][0]/180*3.14))*(3-cos(X[1101][0]/180*3.14))/2;

//        /*======= ПИ - регулятор ========*/
//        X[9][0]=X[9][1]+((delta_t/2)*(X[8][0]+X[8][1]));
//        if (X[9][0]>X[1104][0])     X[9][0]=X[1104][0];
//        if (X[9][0]<(-X[1104][0]))  X[9][0]=(-X[1104][0]);
//        X[9][1]=X[9][0]; X[8][1]=X[8][0];

//        X[10][0] = X[7][0] + X[9][0];
//        X[11][0] = X[3][0]*K[6];
//        X[13][0] = X[11][0] + X[10][0];

//        if (K[14] == 0) X[14][0] = X[13][0];
//        else
//        {
//            X[13][0] = X[13][0]*K[243];
//            X[14][0]= (cos(X[700][0])*cos(X[701][0])*X[13][0]) + K[244]*(X[52][0]*sin(X[701][0])); // в контуре курса
//            X[14][0]=(K[246])*X[14][0];
//        }
//        X[24][0] = X[14][0]*K[16];
//        X[515][0] = X[24][0] - X[17][0];
//        X[516][0]=1.0f;
//        X[517][0] = X[515][0];

//        if((fabs(X[170][0]))>=K[275])
//        {
//            X[517][0]=(X[515][0])*(1+K[274]*(fabs(X[170][0])-K[275]));
//            X[516][0]=(1+K[274]*(fabs(X[170][0])-K[275]));
//        }

//        X[518][0]=1.0f;
//        X[924][0]=(X[517][0]);

//        if((fabs(X[214][0]))>=K[67])
//        {
//            X[924][0]=(X[517][0])*(1+K[247]*(fabs(X[214][0])-K[67]));
//            X[518][0]=(1+K[247]*(fabs(X[214][0])-K[67]));
//        }

//        X[16][0] = X[924][0];

//    }
}

void kurs_contour::core_FeedBack_Distance_Speed()
{
//    X[19][0] = (K[15] == 1 ? X[32][0] : X[21][0]);  // переключение ключа, обратная связь по угловой скорости из блендер или угловая скорость в углах Эйлера
//    core_SU->sensor_filter(K[8], 0.005, X[19], X[18],highfreq_ims_reinit);
//    X[17][0] = X[18][0]*K[7];
}

//void kurs_contour::setTargetParam(PointTargetingParameters *value)
//{
//    targetParam = value;
//}
