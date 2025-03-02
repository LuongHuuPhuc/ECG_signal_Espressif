/**
 * @date 2025/03/01
 */
#include <stdio.h>
#include <stdint.h>
#include "FIRcoefficients.h"
#include "moving_av.h"

fir_coeff_t *Moving_average_coefficients_create(unsigned int length){
  fir_coeff_t *coeff = (fir_coeff_t*)malloc(sizeof(fir_coeff_t));
  coeff->length = length + 1;
  coeff->coefficents = (float*)malloc(coeff->length * sizeof(float)); //Cap phat bo nho dong cho mang coefficients

  //Cai dat he so cho bo loc trung binh muot
  coeff->coefficents[0] = 1.0f;
  for(int i = 1; i <= length; i++){
      coeff->coefficents[i] = -1.0 / (float)length;
  }
  return coeff;
}