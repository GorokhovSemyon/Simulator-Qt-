//#include "mainwindow.h"
#include "marsh_contour.h"
#include <QDebug>
//#include "navigationalgoritm.h"
//#include "navform.h"


Marsh_contour::Marsh_contour(float delta)
{
//    coreBlock = new ComputingBlock(delta);
//    core_SU = new SU_CoreBlock(0.05);
    delta_t = delta;
    accept_workDepthMArshTogerther = false;
}

void Marsh_contour::main_block(float Input, int Regim, int flagUpravleniya, int type_control)
{

//   if ( Regim == 0 || Regim == 1 ) navigate_complete = false;
//   core_FeedBack_Distance_Speed();


//   X[171][0] = Input;
//   X[172][0]=K[101]*X[171][0];

//   switch (Regim) ///--- 0 - ручной, 1 - автоматизированный, 3 - наведение на МДС, 4 - наведение на носитель, 5 - выход в точку
//   {
//       case 0:

//           if (fabs(dynam_su.MotionPapam.Tetta && accept_workDepthMArshTogerther == true) > K[800]) core_SU->setSpeedInLocalAxis_EulerKrilovMatrix(Regim);
//           else X[220][0] = X[172][0];
////           X[220][0] = X[172][0];

//           break;
//       case 1:
//       case 2:

//           if ( type_control == 0 ) //--- Включена система видеостабилизации
//           {
//               if (flagUpravleniya == 1)
//               {
//                   X[173][0] = X[172][0];
//                   X[175][0] = X[173][0]*K[102];

//                   //========Интегральный регулятор========
//                   X[176][0] = X[176][1]+((delta_t/2)*(X[175][0]+X[175][1]));
//                   if ( U_marsh > K[121] && X[175][0] > 0.0 )  X[176][0] = X[176][1];
//                   if ( U_marsh < (-K[121]) && X[175][0] < 0.0 )   X[176][0] = X[176][1];
//                   X[176][1] = X[176][0]; X[175][1]=X[175][0];

//                   Marsh_po_SVS();
//               }
//               else
//               {
//                   if (fabs(dynam_su.MotionPapam.Tetta) > K[800]) core_SU->setSpeedInLocalAxis_EulerKrilovMatrix(Regim);
//                   else X[220][0] = X[172][0];
//               }

//           }
//           if ( type_control == 1 ) //--- Управление по акустическому лагу
//           {
//               if (flagUpravleniya == 1)
//               {
//                   X[174][0] = X[172][0];
//                   X[193][0] = X[174][0]*K[111];

//                   //========Интегральный регулятор========
//                  X[194][0] = X[194][1]+((delta_t/2)*(X[193][0]+X[193][1]));
//                  if ( U_marsh > K[122] && X[193][0] > 0.0 )  X[194][0] = X[194][1];
//                  if (U_marsh < -K[122] && X[193][0] < 0.0 )   X[194][0]=X[194][1];
//                  X[193][1] = X[193][0]; X[194][1]=X[194][0];

//                  Marsh_po_AL();
//               }
//               else
//               {
//                   X[220][0] = X[172][0];
//               }

//           }
//           else
//           {
//               if (fabs(dynam_su.MotionPapam.Tetta) > K[800]) core_SU->setSpeedInLocalAxis_EulerKrilovMatrix(Regim);
//               else X[220][0] = X[172][0];
//           }

//           break;

//           case 3:
//       //CHECK
//               if (dynam_su.MotionPapam.update_pelengator == true && dynam_su.MotionPapam.dist > targetParam->R)
//               {
//                   X[220][0] = ((float)targetParam->Vmax/100)*K[101];
//                   navigate_complete = false;
//               }
//               else
//               {
//                   X[220][0] = 0;
//                   navigate_complete = true;
//               }
//           break;
//           case 4:
////CHECK
//               if (dynam_su.MotionPapam.gans_dist > targetParam->R && dynam_su.MotionPapam.gans_update_success == true)
//               {
//                   X[220][0] = ((float)targetParam->Vmax/100)*K[101];
//                   navigate_complete = false;
//               }
//               else
//               {
//                   X[220][0] = 0;
//                   navigate_complete = true;
//               }

//           break;

//           case 5:
////CHECK
//               X[220][0] = (*target_radius > targetParam->R ? ((float)targetParam->Vmax/100) : 0)*K[101];
//               navigate_complete = ( *target_radius > targetParam->R ? false : true );

//               break;
//       default:
//           break;
//   }
//   U_marsh = X[220][0];

}

void Marsh_contour::Marsh_po_SVS()
{

//    X[177][0] = X[176][0] - X[192][0];
//    X[178][0] = X[177][0]*K[103];

//    //=========ПИ - регулятор==========
//    X[179][0] = X[178][0]*K[104];
//    X[180][0] = X[180][1]+((delta_t/2)*(X[179][0]+X[179][1]));
//    if ( X[180][0] > K[105] )   X[180][0] = K[105];
//    if ( X[180][0] < (-K[105]) )   X[180][0] = (-K[105]);
//    X[180][1]=X[180][0]; X[179][1]=X[179][0];
//    //===========Конец ПИ - регулятора========

//    X[181][0] = X[180][0] + X[178][0];
//    X[184][0] = X[175][0]*K[106];
//    X[182][0] = X[181][0]+X[184][0];

//    X[185][0] = X[186][0]*K[107];
//    X[183][0] = X[182][0]-X[185][0];

//    X[220][0] = X[219][0] = X[210][0] = X[185][0];

}

void Marsh_contour::Marsh_po_AL()
{

//    X[195][0] = X[194][0] - X[206][0];
//    X[196][0] = X[195][0]*K[112];
//    X[197][0] = X[196][0]*K[113];

//    X[198][0] = X[198][1]+((delta_t/2)*(X[197][0]+X[197][1]));
//    if ( X[198][0] > K[114] )   X[198][0] = K[114];
//    if ( X[198][0] < (-K[114]) )   X[198][0] = (-K[114]);
//    X[197][1] = X[197][0]; X[198][1] = X[198][0];

//    X[199][0] = X[198][0] + X[196][0];
//    X[201][0] = X[193][0]*K[115];
//    X[200][0] = X[199][0] + X[201][0];

//    X[203][0] = X[204][0]*K[116];
//    X[202][0] = X[200][0] - X[203][0];
//    X[220][0] = X[219][0] = X[210][0] = X[202][0];

}

void Marsh_contour::core_FeedBack_Distance_Speed()
{
//    //==================AL===============
//    X[209][0] = X[207][0] - K[118];
//    X[205][0] = X[209][0]*K[119];
//    X[208][0] = X[205][0];
//    core_SU->sensor_filter(K[117], 0.005, X[208], X[204],highfreq_ims_reinit);
//    X[203][0] = X[204][0]*K[117];

//    X[206][0] = coreBlock->integrationInputValue(X[205], X[206]);

//    //=================SVS================

//    X[187][0]= X[896][0]*K[109];
//    X[192][0]= X[899][0]*K[123];
//    core_SU->sensor_filter(K[108], 0.005, X[187], X[186],highfreq_ims_reinit);
//    X[185][0]=X[186][0]*K[107];
}

//void Marsh_contour::setTargetParam(PointTargetingParameters *value)
//{
//    targetParam = value;
//}
