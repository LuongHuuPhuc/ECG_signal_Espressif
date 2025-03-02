#ifndef FIR_H_
#define FIR_H_

#include <stdio.h>
#include <stdlib.h>
#include "FIRcoefficients.h"

typedef struct FIR{
  float *values;
  unsigned int length;
  fir_coeff_t *coefficients;
}fir_filter_t;

fir_filter_t *FIR_filter_init(fir_coeff_t *coeff);

void FIR_filter_destroy(fir_filter_t *fir);

float FIR_filter_apply(fir_filter_t *fir, float currentInput);

#endif //FIR_H_
