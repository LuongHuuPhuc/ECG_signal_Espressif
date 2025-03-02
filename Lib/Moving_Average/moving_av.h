/**
 * @brief Thu vien cua bo loc trung binh muot trong xu ly tin hieu so (digital)
 * @note Muc dich cua bo loc la giam nhieu, lam muot tin hieu bang cach tinh toan gia tri trung binh
 * cua 1 cua so du lieu lan can tai moi thoi diem thoi gian
 */
#ifndef MOVING_AV_H_
#define MOVING_AV_H_

#include <stdio.h>
#include <stdint.h>
#include "FIRcoefficients.h"
fir_coeff_t *Moving_average_coefficients_create(unsigned int length);

#endif //MOVING_AV_H_ 