/**
 * @brief Thu vien bo loc danh cho ECG
 * @author Luong Huu Phuc 
 * @date 2025/03/07
 * @copyright brandicph
 * @link https://github.com/brandicph/ECGscanner-C/blob/master/README.md
 * 
 */
#ifndef FILTER_MASTER_ECG_H
#define FILTER_MASTER_ECG_H

#pragma once

#include <stdio.h>
#include <stdlib.h>
// #include "modulus.h"

extern unsigned long int GLOBAL_COUNT;

//Ham dem toan cuc
unsigned long int global_count(void);

/**
 * @note Cac ham duoi day duoc khai bao static vi chi gioi han pham vi cua chung trong source file
 * Khong can phai truy cap tu cac file khac (private)
 * => Tang tinh dong goi, toi uu hoa bien dich
 */
/**
 * @brief Bo loc thong thap de loai bo tan so cao hon tan so cat (cut-off frequency)
 * @param x Tin hieu dau vao 
 * @param y Tin hieu sau khi qua bo loc 
 * @note Cong thuc: y_n = 2y_n-1 - y_n-2 + 1/32 * (x_n - 2x_n-6 + x_n-12)
 * @note Bo loc nay thuc hien viec lam muot tin hieu 
 */
int low_pass_filter(int *x, int *y);

/**
 * @brief Bo loc thong cao de loai bo cac tan so thap hon tan so cat 
 * @param x Tin hieu dau vao 
 * @param y Tin hieu sau khi qua bo loc 
 * @note Cong thuc: y = y_n-1 - x_n/32 + x_n-16 - x_n-17 + x_n-32/32 //Gia tri tai cac thoi diem khac nhau 
 */
int high_pass_filter(int *x, int *y);

/**
 * @brief Bo loc dao ham de tinh su thay doi cua tin hieu bang cach chia nho tin hieu 
 * @return Giup thay ro su thay doi cua tin hieu 
 * @note Cong thuc: y_n = 1/8 * (2x_n + x_n-1 + x_n-3 + 2x_n-4)
 */
int derivative_filter(int *x);

/**
 * @brief Bo loc binh phuong, don gian chi binh phuong tin hieu thoi 
 * @note Cong thuc: y_n = (x_n)^2
 */
int squared_filter(int *x, int *y);

/**
 * @brief Cua so di dong (Moving Window Integration)
 * @note MWI la phep toan de tinh trung binh cac gia tri tin hieu trong 1 cua so thoi gian 
 * De lam muot tin hieu & giam nhieu de de dang phat hien cac dinh ECG
 * @note Cong thuc: y_n = 1/N * (x_n-(N-1) + x_n-(N-2) + ... + x_n)
 * @param N la so luong mau trong cua so 
 */
int moving_window(int ym0, int N);

//Public 
int filter_master_ecg(int value);

#endif //FILTER_MASTER_ECG_H