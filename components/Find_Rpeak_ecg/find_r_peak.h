#ifndef FIND_R_PEAK_H
#define FIND_R_PEAK_H

#pragma once

#include <stdio.h>
#include <stdint.h>
#include "filter_master_ecg.h"

/**
 * @note Cac ham duoi day duoc khai bao static vi chi gioi han pham vi cua chung trong source file
 * Khong can phai truy cap tu cac file khac (private)
 * => Tang tinh dong goi, toi uu hoa bien dich
 */
int peak_check(int value);

int search_back();

int get_peak();

int next_value(int value);

void save_RRInRR_recent(int RR);

void save_RRInRR_recent_ok(int RR);

void save_peak(int peak);

int calculate_RR();

int count_miss();

int count_peak();

int count_Rpeak();

int count_interval();

int cal_mving_avg(int latest_avg, int temp, int value, int N);

//Public 
int detect_peak(int sample);


#endif //FIND_R_PEAK_H