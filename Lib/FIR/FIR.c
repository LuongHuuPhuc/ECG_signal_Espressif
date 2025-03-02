/**
 * @note Thu vien bo loc so FIR (Finite Impulse Response)
 * @date 2025/03/01
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "FIR.h"
#include "FIRcoefficients.h"

fir_filter_t *FIR_filter_init(fir_coeff_t *coeff){
  fir_filter_t *fir = (fir_filter_t*)malloc(sizeof(fir_filter_t));
  fir->coefficients = coeff;
  fir->length = coeff->length;
  fir->values = (float*)malloc(fir->length * sizeof(float)); //Cap phat bo nho dong cho mang Values

  //Khoi tao mang value voi gia tri la 0
  for(int i = 0; i < fir->length; i++){
    fir->values[i] = 0;
  }
  return fir;
}

void FIR_filter_destroy(fir_filter_t *fir){
  if(fir){
    free(fir->values); //Giai phong bo nho cho mang values
    free(fir); //Giai phong bo nho cho cau truc fir_filter_t
  }
}

float FIR_filter_apply(fir_filter_t *fir, float currentInput){
  float result = 0.0f;

  //Cap nhap tung gia tri trong mang values va tinh toan
  for(int i = fir->length - 1; i > 0; i--){
    fir->values[i] = fir->values[i - 1];
    result += fir->values[i] * fir->coefficients->coefficents[i]; //Tinh toan voi he so FIR
  }

  //Cap nhat gia tri dao vao moi
  fir->values[0] = currentInput;
  result += fir->values[0] * fir->coefficients->coefficents[0];

  return result;
}
