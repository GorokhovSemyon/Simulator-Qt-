#include "depth_contour.h"
#include <QDebug>

depth_contour::depth_contour(Exchange_structures *_exch_str)
{
    exch_str = _exch_str;
    delta_t = 0.05;

    currDepth = 0;
}

void depth_contour::main_block() {
  float sumErr = 0;
  float corrSumErr = 0;
  float dblCorrSumErr = 0;
  float prevDblCorrSumErr = 0;
  float integrOut = 0;
  float prevIntegrOut = 0;
  float outPI = 0;
  float midSumOut = 0;

  float absLimit = 10.0;

  float K1 = 1;
  float K2 = 1;
  float kInIntegr = 1;
  float kConvert = 1;

  //-------------------------------------------------------------------------
  //Ошибка контура положения

  // X[244][0] = targetParam->destY;  // задающее значение
  sumErr = exch_str->target_params.des_Depth - exch_str->from_data.params.Z; //вычисляем ошибку контура положения
  // X[245][0] = X[244][0] - X[260][0];  //значение ошибки
  corrSumErr = sumErr * K1;
  // X[246][0] = X[245][0] * K[136];  // K[136] - К1

  //-------------------------------------------------------------------------
  //ПИ-регулятор

  dblCorrSumErr = corrSumErr * kInIntegr;
  // X[247][0] = X[246][0] * K[137];
  integrOut =
      prevIntegrOut + ((delta_t / 2) * (dblCorrSumErr + prevDblCorrSumErr));
  //  X[248][0] = X[248][1] + ((delta_t / 2) * (X[247][0] + X[247][1]));
  if (integrOut > absLimit) integrOut = absLimit;
  //  if (X[248][0] > K[139]) X[248][0] = K[139];
  if (integrOut < (-absLimit)) integrOut = (-absLimit);
  //  if (X[248][0] < (-K[139])) X[248][0] = (-K[139]);
  prevIntegrOut = integrOut;
  //  X[248][1] = X[248][0];
  prevDblCorrSumErr = dblCorrSumErr;
  //  X[247][1] = X[247][0];
  outPI = corrSumErr + integrOut;
  //  X[251][0] = X[246][0] + X[248][0];

  //-------------------------------------------------------------------------

  //От датчиков
  currDepth = exch_str->from_data.params.Vz * K2;
  //X[254][0] = X[255][0] * K[141];  // X[255][0] - значение текущей глубины от
                                     // симулятора. K[141] - К2

  //Получаем напряжение
  midSumOut = outPI - currDepth;
  // X[252][0] = X[251][0] - X[254][0];
  exch_str->target_params.depth_U = midSumOut * kConvert;
  // X[918][0] = X[252][0] * K[140];
  //  X[253][0] = X[918][0];
  //  X[261][0] = X[253][0];
  //  X[268][0] = X[261][0];
  //  depthU = X[268][0];
}


