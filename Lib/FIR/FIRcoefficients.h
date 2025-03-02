/**
 * @brief Thu vien chua cac he so (Coefficients) cua bo loc FIR 
 * @note Ham ma su dung pointer(*) se tra ve mot con tro toi kieu du lieu fir_coeff_t
 */
#ifndef FIRCOEFFICIENTS_H_
#define FIRCOEFFICIENTS_H_

typedef struct {
  unsigned int length;
  float *coefficents;
}fir_coeff_t;

/**
 * @note Ham tao coefficient voi do dai length
 * @param length Do dai FIR
 */
fir_coeff_t* FIR_coefficients_create(unsigned int length);

/**
 * @note Ham tao coefficient voi do dai length va mang coeffients da co san 
 */
fir_coeff_t* FIR_coefficients_create_with_coeffs(unsigned int length, float *coefficients);

/**
 * @note Ham giai phong bo nho dong cua FIRCoefficients
 */
void FIR_coefficients_destroy(fir_coeff_t *coeffs);

/**
 * @note Ham tra ve kich thuoc cua fir_coeff_t
 */
unsigned int FIR_cofficients_size_return(fir_coeff_t *coeffs);

/**
 * @note Ham truy xuat gia tri cua coefficients tai chi muc i 
 */
float FIR_coefficients_get(fir_coeff_t *coeffs, unsigned int i);

/**
 * @note Ham cap nhat gia tri cua coefficient tai muc i
 */
void FIR_coefficients_set(fir_coeff_t *coeffs, unsigned int i, float val);

#endif //FIRCOEFFICIENTS_H_