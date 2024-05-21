#include "different_contour.h"
#include "mainwindow.h"

different_contour::different_contour(float delta)
{
    delta_t = delta;
    core_SU = new SU_CoreBlock(0.05);
}

void different_contour::main_block(float Input, int Regim, int flagUpravleniya)
{
    core_FeedBack_Distance_Speed();
    X[41][0] = Input;
    X[42][0] = X[41][0]*K[21];

    switch (Regim) ///--- 0 - ручной, 1 - автоматизированный, 3,4 - наведение
    {
        case 0:

            X[67][0] = X[42][0];

        break;

        case 1:
        case 2:

            if(flagUpravleniya)
            {
                X[43][0] = X[42][0];
                X[44][0] = X[43][0]*K[22];

                /*======= ПИ - регулятор ========*/
                /*==== C ЛБ, замораживающим накапливание =====*/
                X[45][0]=X[45][1]+((delta_t/2)*(X[44][0]+X[44][1])); ///---ПИ - регулятор
                if ((U_diff>=K[35])&&(X[44][0]>0))        X[45][0]=X[45][1]; ///---ЛБ
                if ((U_diff<=(-K[35]))&&(X[44][0]<0))     X[45][0]=X[45][1]; ///---ЛБ
                if (X[45][0]>K[23])      X[45][0]=K[23]; ///---Ограничение по максимальному углу
                if (X[45][0]<(K[301]))   X[45][0]=(K[301]); ///---Ограничение по максимальному углу
                X[45][1]=X[45][0];
                X[44][1]=X[44][0];

                Different_scheme_mainLogic();
            }

        break;

        case 3:
        case 4:
        case 5:

            X[45][0] = 0;
            Different_scheme_mainLogic();

        break;

    }
    U_diff = X[67][0];
}

void different_contour::Different_scheme_mainLogic()
{
    X[46][0] = X[45][0] - X[66][0];
    X[47][0] = X[46][0]*K[24];
    X[48][0] = X[47][0]*K[25];

    X[1102][0]=fabs(X[45][0]);
    if((X[1102][0]>=K[241]))
    {
        X[1103][0]=K[26]+((X[1102][0]-K[241])*K[242]);
    }
    else
    {
        X[1103][0]=K[26];
    }
    X[49][0]=X[49][1]+((delta_t/2)*(X[48][0]+X[48][1]));
    if (X[49][0]>X[1103][0])   X[49][0]=X[1103][0];
    if (X[49][0]<(-X[1103][0])) X[49][0]=(-X[1103][0]);

    X[49][1]=X[49][0]; X[48][1]=X[48][0];

    X[50][0] = X[49][0] + X[47][0];
    X[51][0] = X[44][0]*K[27];
    X[52][0] = X[50][0] + X[51][0];

    if (K[14] == 0) X[69][0] = X[52][0];
    else
    {
        X[52][0] = X[52][0]*K[243];
        X[53][0] = ( X[52][0]*cos(X[701][0]) )- K[245]*(X[13][0]*cos(X[700][0])*sin(X[701][0])); // в контуре дифферента
        X[69][0] = X[53][0]*K[246];
    }

    X[65][0] = X[69][0] - X[56][0];
    X[67][0] = X[65][0];
}

void different_contour::core_FeedBack_Distance_Speed()
{
    X[58][0] = (K[30] == 1 ? X[60][0] : X[885][0]);  // переключение ключа, обратная связь по угловой скорости из блендер или угловая скорость в углах Эйлера
    core_SU->sensor_filter(K[29], 0.005, X[58], X[57],highfreq_ims_reinit);
    X[56][0] = X[57][0]*K[28];
}
