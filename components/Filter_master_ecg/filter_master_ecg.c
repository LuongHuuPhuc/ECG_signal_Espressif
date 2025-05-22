/**
 * @note Thuat toan tim ECG real-time ap ap dung cac bo loc
 * @link https://scispace.com/papers/a-real-time-qrs-detection-algorithm-5dqh3i09n2
 * @date 2025/08/03
 */
#include "filter_master_ecg.h"
#include "modulus.h"

#define MAX_X 13    //So luong toi da cua tin hieu vao x
#define MAX_LOW 33  //So luong toi da cua tin hieu da qua low-pass
#define MAX_HIGH 5  //So luong toi da cua tin hieu da qua high-pass
#define MAX_DER 1   //So luong toi da cua tin hieu da qua derivative filter
#define MAX_SQR 30  //So luong toi da cua tin hieu da binh phuong 

static int x[MAX_X] = {0}; //Mang chua gia tri cac tin hieu goc 
static int low[MAX_LOW] = {0}; //Mang chua gia tri cac tin hieu qua low-pass
static int high[MAX_HIGH] = {0}; //Mang chua gia tri cac tin hieu qua high-pass
static int der[MAX_DER] = {0}; //Mang chua gia tri cac tin hieu qua derivative filter
static int sqr[MAX_SQR] = {0}; //Mang chua gia tri cac tin hieu da binh phuong 
int mwi = 0;  //Bien luu gia tri cap nhat sau khi di qua MWI
unsigned long int GLOBAL_COUNT = 0;

unsigned long int global_count(void){
  return GLOBAL_COUNT++;
}

int low_pass_filter(int *x, int *y){
  int ym1 = y[modulus(GLOBAL_COUNT - 1, MAX_LOW)]; //m la minus
  int ym2 = y[modulus(GLOBAL_COUNT - 2, MAX_LOW)];
  int xm0 = x[modulus(GLOBAL_COUNT, MAX_X)];
  int xm6 = x[modulus(GLOBAL_COUNT - 6, MAX_X)];
  int xm12 = x[modulus(GLOBAL_COUNT - 12, MAX_X)];
  return (2 * ym1 - ym2 + (xm0 - 2 * xm6 + xm12) / 32);
}

int high_pass_filter(int *x, int *y){
  int ym1 = y[modulus(GLOBAL_COUNT - 1, MAX_HIGH)];
  int xm0 = x[modulus(GLOBAL_COUNT, MAX_LOW)];
  int xm16 = x[modulus(GLOBAL_COUNT - 16, MAX_LOW)];
  int xm17 = x[modulus(GLOBAL_COUNT - 17, MAX_LOW)];
  int xm32 = x[modulus(GLOBAL_COUNT - 32, MAX_LOW)];
  return (ym1 - (xm0 / 32) + xm16 - xm17 + (xm32 / 32));
}

int derivative_filter(int *x){
  int xm0 = x[modulus(GLOBAL_COUNT, MAX_HIGH)];
  int xm1 = x[modulus(GLOBAL_COUNT - 1, MAX_HIGH)];
  int xm3 = x[modulus(GLOBAL_COUNT - 3, MAX_HIGH)];
  int xm4 = x[modulus(GLOBAL_COUNT - 4, MAX_HIGH)];
  return ((2 * xm0 + xm1 - xm3 - 2 * xm4) / 8);
}

static int squared_old = 0;
static int squared_new = 0;
int squared_filter(int *x, int *y){
  int xm0 = x[modulus(GLOBAL_COUNT, MAX_DER)];
  squared_old = y[modulus(GLOBAL_COUNT, MAX_SQR)];
  squared_new = xm0 * xm0;
  return squared_new;
}

int moving_window(int ym0, int N){
  return (ym0 - (squared_old / N) + (squared_new / N));
}

int filter_master_ecg(int value){
  x[GLOBAL_COUNT % MAX_X] = value;
  low[GLOBAL_COUNT % MAX_LOW] = low_pass_filter(x, low);
  high[GLOBAL_COUNT % MAX_HIGH] = high_pass_filter(low, high);
  der[GLOBAL_COUNT % MAX_DER] = derivative_filter(high);
  sqr[GLOBAL_COUNT % MAX_SQR] = squared_filter(der, sqr);
  mwi = moving_window(mwi, 30);
  return mwi;
}