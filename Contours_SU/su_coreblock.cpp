#include "su_coreblock.h"

SU_CoreBlock::SU_CoreBlock(float delta)
{
    delta_t = delta;
}

void SU_CoreBlock::sensor_filter(float Tau, float Td, float *Data, float * DataF, int reinit_filter)
{
    float Par;

    Par= 2*Tau/Td;
    if (reinit_filter)
    {
        DataF[0]=Data[0];
        DataF[1]=Data[0];
        Data[1]=Data[0];
    }
    else
    {
        DataF[0]=(1/(1+Par))*((Data[1]+Data[0])-((1-Par)*DataF[1]));
        Data[1]=Data[0]; DataF[1]=DataF[0];
    }
}

void SU_CoreBlock::core_EulerAngleSpeed()
{
    /*
     * Данная функция вызывается при углах дифферента, больших 60 градусов
     *
    */

    /*
     * угловые скорости в радианах
     * X[21][0] - угловая скорость Wz
     * X[885][0] - угловая скорость Wy
     * X[883][0] - угловая скорость Wx
    */

    /*
     * X[32][0] - dPsi
     * X[60][0] - dTeta
     * X[104][0] - dGamma
    */

    /*========================================
     * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

       В данном случае угловые скорости Wy и Wz поменяны местами относительно мат модели НПА

     * !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    ========================================*/

    X[32][0] = (1/cos(dynam_su.MotionPapam.Tetta/180*3.14))*(X[21][0]*cos(dynam_su.MotionPapam.Gamma/180*3.14) - X[885][0]*sin(dynam_su.MotionPapam.Gamma/180*3.14)); // угловая скорость по курсу в градусах
    X[60][0] = X[21][0]*sin(dynam_su.MotionPapam.Gamma/180*3.14) + X[885][0]*cos(dynam_su.MotionPapam.Gamma/180*3.14); // угловая скорость по дифференту в градусах
    X[104][0] = X[883][0] - tan(dynam_su.MotionPapam.Tetta/180*3.14)*(X[21][0]*cos(dynam_su.MotionPapam.Gamma/180*3.14) - X[885][0]*sin(dynam_su.MotionPapam.Gamma/180*3.14)); // угловая скорость по крену в градусах
}

void SU_CoreBlock::setSpeedInLocalAxis_EulerKrilovMatrix(int Regim)
{
    /*
     * X700 - angle_rad_diff (mainwindow.cpp)
     * X701 - angle_rad_kren (mainwindow.cpp)
     * X702 - angle_rad_kurs (mainwindow.cpp)
     *
    */
    float Xg_signal, Yg_signal, Zg_signal;
    float marsh_voltage_regulator = K[300]; ///---ограничение мощности маршевых движетелей
    Xg_signal = (Regim == 1 ? X[172][0] : X[172][0]);
    Yg_signal = (Regim == 1 ? X[261][0] : X[222][0]);
    Zg_signal = (Regim == 1 ? X[161][0] : X[122][0]);
    X[220][0] = (cos(X[700][0])*Xg_signal)*marsh_voltage_regulator + sin(X[700][0])*Yg_signal;
    X[268][0] = (-cos(X[701][0]))*sin(X[700][0])*Xg_signal + cos(X[701][0])*cos(X[700][0])*Yg_signal;
    X[170][0] = (-sin(X[700][0]))*sin(X[701][0])*Xg_signal + cos(X[700][0])*sin(X[701][0])*Yg_signal;
}

void SU_CoreBlock::set_Local_or_Global_AngleSpeed()
{
    K[14] = (fabs(dynam_su.MotionPapam.Tetta) > K[800] ? 1 : 0);
    K[30] = (fabs(dynam_su.MotionPapam.Tetta) > K[800] ? 0 :1);
    K[15] = (fabs(dynam_su.MotionPapam.Tetta) > K[800] ? 0 :1);
    K[56] = (fabs(dynam_su.MotionPapam.Tetta) > K[800] ? 0 :1);
}
