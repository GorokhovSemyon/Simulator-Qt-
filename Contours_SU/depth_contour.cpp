#include "depth_contour.h"

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

  sumErr = exch_str->target_params.des_Y - exch_str->from_data.params.Y; //вычисляем ошибку контура положения

  corrSumErr = sumErr * K1;


  //-------------------------------------------------------------------------
  //ПИ-регулятор

  dblCorrSumErr = corrSumErr * kInIntegr;

  integrOut =
      prevIntegrOut + ((delta_t / 2) * (dblCorrSumErr + prevDblCorrSumErr));

  if (integrOut > absLimit)
      integrOut = absLimit;

  if (integrOut < (-absLimit))
      integrOut = (-absLimit);

  prevIntegrOut = integrOut;

  prevDblCorrSumErr = dblCorrSumErr;

  outPI = corrSumErr + integrOut;

  //-------------------------------------------------------------------------

  //От датчиков
  currDepth = exch_str->from_data.params.Vy * K2;

  //Получаем напряжение
  midSumOut = outPI - currDepth;

  exch_str->target_params.depth_U = midSumOut * kConvert;
}


