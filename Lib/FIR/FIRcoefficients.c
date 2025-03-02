/**
 * @date 2025//03/01
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "FIRcoefficients.h"

fir_coeff_t* FIR_coefficients_create(unsigned int length){
  fir_coeff_t *coeffs = (fir_coeff_t*)malloc(sizeof(fir_coeff_t));
  coeffs->length = length;
  coeffs->coefficents = (float*)malloc(length * sizeof(float)); //Cap phat bo nho cho mang coefficients
  return coeffs;
}

fir_coeff_t* FIR_coefficients_create_with_coeffs(unsigned int length, float *coefficients){
  fir_coeff_t *coeffs = (fir_coeff_t*)malloc(sizeof(fir_coeff_t));
  coeffs->length = length;
  coeffs->coefficents = coefficients;
  return coeffs;
}

void FIR_coefficients_destroy(fir_coeff_t *coeffs){
  if(coeffs){
    free(coeffs->coefficents);  //Giai phong mang coefficients
    free(coeffs); //Giai phong cau truc fir_coeff_t
  }
}

unsigned int FIR_cofficients_size_return(fir_coeff_t *coeffs){
  return coeffs->length;
}

float FIR_coefficients_get(fir_coeff_t *coeffs, unsigned int i){
  return coeffs->coefficents[i];
}

void FIR_coefficients_set(fir_coeff_t *coeffs, unsigned int i, float val){
  coeffs->coefficents[i] = val;
}
