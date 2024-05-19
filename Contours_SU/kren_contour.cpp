#include "kren_contour.h"

kren_contour::kren_contour(float delta)
{
    delta_t = delta;
    core_SU = new SU_CoreBlock(0.05);
}

void kren_contour::main_block(float Input, int Regim, int flagUpravleniya)
{
    X[81][0]=Input;
    X[82][0]=K[46]*X[81][0];

    switch (Regim) ///--- 0 - ручной, 1 - автоматизированный, 3,4 - наведение
    {

        case 0:

            X[96][0] = X[82][0];

        break;

        case 1:
        case 2:

           if (flagUpravleniya == 1)
           {
               X[83][0] = X[82][0];
               X[84][0] = X[83][0]*K[47];

               /*======= ПИ - регулятор ========*/
               /*==== C ЛБ, замораживающим накапливание =====*/
               X[85][0] = (fabs(dynam_su.MotionPapam.Tetta) > K[800] ? 0 : X[85][1]+((delta_t/2)*(X[84][0]+X[84][1]))); ///---ПИ - регулятор
               if ((U_kren>=K[60])&&(X[84][0]>0))     X[85][0]=X[85][1]; ///--ЛБ
               if ((U_kren<=(-K[60]))&&(X[84][0]<0))  X[85][0]=X[85][1]; ///--ЛБ
               if  (X[85][0]>K[48])     X[85][0]=K[48]; ///---ограничение по максимальному углу крена
               if  (X[85][0]<(-K[48]))  X[85][0]=(-K[48]); ///---ограничение по максимальному углу крена
               X[85][1]=X[85][0]; X[84][1]=X[84][0];

               Kren_scheme_mainLogic();
           }

        break;

        case 3:
        case 4:
        case 5:

            X[85][0] = 0;
            Kren_scheme_mainLogic();
        break;
    }
    U_kren = X[96][0];
}

void kren_contour::Kren_scheme_mainLogic()
{
    X[86][0] = X[85][0] - X[110][0];
    X[87][0] = X[86][0]*K[49];
    X[88][0] = X[87][0]*K[50];

    X[1101][0]=fabs(X[85][0]);
    if((X[1101][0]>=K[65]))
    {
        X[1100][0]=K[51]+((X[1101][0]-K[65])*K[68]);
    }
    else
    {
        X[1100][0]=K[51];
    }
    X[89][0]=X[89][1]+((delta_t/2)*(X[88][0]+X[88][1]));
    if (X[89][0]>X[1100][0])      X[89][0]=X[1100][0];
    if (X[89][0]<(-X[1100][0]))   X[89][0]=(-X[1100][0]);

    X[89][1]=X[89][0]; X[88][1]=X[88][0];

    X[90][0] = X[87][0] + X[89][0];
    X[91][0] = X[84][0]*K[52];
    X[92][0] = X[90][0] + X[91][0];

    if (K[14] == 0) X[95][0] = X[92][0];
    else
    {
        X[93][0]= (X[92][0])+(K[64]*(X[13][0]*sin(X[700][0])));  //  в контуре крена
        X[95][0] = X[93][0];
    }

    X[510][0] = X[95][0] - X[100][0];

    X[506][0] = (X[505][0]-X[505][1])/0.05f;
    X[507][0] = X[506][0]*K[273];
    X[544][0] = X[886][0]*K[277];
    X[542][0] = cos(X[544][0]);
    X[543][0] = sin(X[885][0]);
    X[101][0] = X[542][0]*X[543][0];
    X[540][0] = X[101][0]*K[276];

    X[511][0] = X[510][0] - X[507][0];

    if(fabs(X[269][0])>=K[253])
    {
        X[94][0]=(X[511][0]+X[540][0])*( 1+K[252]*(fabs(X[269][0])-K[253]) );
        X[513][0]=( 1+K[253]*(fabs(X[269][0])-K[253]) );
    }
    X[514][0]=1.0f;
    if(fabs(X[68][0])>=K[256])
    {
        X[96][0]= X[94][0]*( 1+K[255]*(fabs(X[68][0])-K[256]) );
        X[514][0]=( 1+K[256]*(fabs(X[68][0])-K[256]) );
    }
}

void kren_contour::core_FeedBack_Distance_Speed()
{
    X[102][0] = (K[56] == 1 ? X[104][0] : X[883][0]); // переключение ключа, обратная связь по угловой скорости из блендер или угловая скорость в углах Эйлера
    core_SU->sensor_filter(K[55], 0.005, X[503], X[504],highfreq_ims_reinit);
    core_SU->sensor_filter(K[55], 0.005, X[102], X[101],highfreq_ims_reinit);
    X[100][0] = X[101][0]*K[53];
}
