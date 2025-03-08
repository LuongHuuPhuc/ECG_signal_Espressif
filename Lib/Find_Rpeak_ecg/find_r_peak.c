/**
 * @note Thuat toan tim ECG real-time ap ap dung cac bo loc
 * @link https://scispace.com/papers/a-real-time-qrs-detection-algorithm-5dqh3i09n2
 * @date 2025/08/03
 * @author Luong Huu Phuc
 */
#include "find_r_peak.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include "modulus.h"

#define MAX_X 3
#define MAX_PEAKS 100
#define MAX_RR_RECENT 8
#define MAX_RR_RECENT_OK 8
#define MAX_MISS 5
#define MIN_RPEAK 2000


//Khoi tao bien toan cuc 
static int peak = 0; //Bien luu dinh moi nhat phat hien duoc
static int Rpeak = 0; //Bien luu dinh R moi nhat 
static int SPKF = 4500; //Gia tri uoc tinh cua dinh R (Signal Peak Detectin Factor)
static int NPKF = 2000; //Gia tri uoc tinh cua dinh nhieu (noise)
static int THRESHOLD1 = 2300; //Nguong dinh thap nhat phat hien - nguong chinh 
static int THRESHOLD2 = 1300; //Dung khi phat hien dinh khong ro rang
static int RR = 0; //Tgian giua 2 dinh R 
static int RR_Average1 = 150; 
static int RR_Average1_temp = 150;
static int RR_Average2 = 160;
static int RR_Average2_temp = 160;
static int RR_LOW = 120; //Nguong thap nhat giua 2 dinh khi co R peak 
static int RR_HIGH = 246; //Nguong cao nhat giua 2 dinh khi co R peak
static int RR_MISS = 352; //Neu threshold1 de len cao
static int RR_RECENT[MAX_RR_RECENT] = {100, 100, 100, 100, 100, 100, 100, 100};
static int RR_CECENT_OK[MAX_RR_RECENT_OK] = {212, 212, 212, 212, 212, 212, 212, 212};

static int x[MAX_X] = {0}; //Luu gia tri cua 3 dinh moi nhat - can de phat hien dinh
static int PEAKS[MAX_PEAKS];  //Mang chua tat ca cac dinh

static int intervals = 0;
static int peak_count = 0;
static int Rpeak_count = 0;
static int miss_count = 0;

int cal_mving_avg(int latest_avg, int temp, int value, int N){
  return (latest_avg - (temp / N)) +  (value / N);
}

int count_interval(){
  return intervals++;
}

int count_peak(){
  return peak_count++;
}

int count_Rpeak(){
  return Rpeak_count++;
}

int count_miss(){
  return miss_count++;
}

int calculate_RR(){
  int temp = intervals;
  intervals = 0; 
  return temp;
}

void save_peak(int peak){
  PEAKS[modulus(peak_count, MAX_PEAKS)] = peak; 
}

void save_RRInRR_recent(int RR){
  RR_RECENT[modulus(Rpeak_count, MAX_RR_RECENT)] = RR;
}

void save_RRInRR_recent_ok(int RR){
  RR_CECENT_OK[modulus(Rpeak_count, MAX_RR_RECENT_OK)] = RR;
}

int next_value(int value){
  x[GLOBAL_COUNT % MAX_X] = value;
  return value;
}

int get_peak(){
  return x[modulus(GLOBAL_COUNT - 1, MAX_X)];
}

int search_back(){
  int i = 0; 
  int peak2;
  while(i < MAX_PEAKS){
    peak2 = PEAKS[modulus(peak_count - i, MAX_PEAKS)];
    if(peak2 > THRESHOLD2){
      return 1;
    }
    i++;
  }
  return 0;
}

int peak_check(int value){
  int xm1 = x[modulus(GLOBAL_COUNT - 2, MAX_X)];
  int xm0 = x[modulus(GLOBAL_COUNT - 1, MAX_X)];
  int xp1 = x[modulus(GLOBAL_COUNT, MAX_X)];
  if(xm1 < xm0 && xm0 > xp1){
    return 1;
  }else{
    return 0;
  }
}

int detect_peak(int sample){
  //Check for peaks
  int next = next_value(sample); //Cho tin hieu moi vao
  int detected = 0; //Bien luu dinh da phat hien 

  if(peak_check(next)){
    int peak = get_peak();
    save_peak(peak);

    if(peak > THRESHOLD1){
      //Tgian giua 2 dinh
      RR = calculate_RR();
      if(RR_LOW < RR && RR < RR_HIGH){
        Rpeak = peak;
        save_RRInRR_recent(RR);
        save_RRInRR_recent_ok(RR);

        SPKF = (int)(0.125 * peak + 0.875 * SPKF);//peak la tin hieu dinh
        RR_Average1 = cal_mving_avg(RR_Average1, RR_Average1_temp, RR, MAX_RR_RECENT);
        RR_Average2 = cal_mving_avg(RR_Average2, RR_Average2_temp, RR, MAX_RR_RECENT_OK);

        RR_LOW = (int)(0.92 * RR_Average2);
        RR_HIGH = (int)(1.16 * RR_Average2);
        RR_MISS = (int)(1.66 * RR_Average2);

        THRESHOLD1 = (int)(NPKF + 0.25 * (SPKF - NPKF));
        THRESHOLD2 = (int)(0.5 * THRESHOLD1);

        //Gia tri trung binh tam thoi cho tinh toan moving average
        RR_Average1_temp = RR;
        RR_Average2_temp = RR;
        count_peak();

        miss_count = 0;
        detected = 1;
      }else{
        count_miss();
        if(RR < RR_MISS){
          if(search_back()){
            Rpeak = peak;
            save_RRInRR_recent(RR);

            SPKF = (int)(0.25 * peak + 0.75 * SPKF);
            RR_Average1 = cal_mving_avg(RR_Average1, RR_Average1_temp, RR, MAX_RR_RECENT);

            RR_LOW = (int)(0.92 * RR_Average2);
            RR_HIGH = (int)(1.16 * RR_Average2);
            RR_MISS = (int)(1.66 * RR_Average2);

            THRESHOLD1 = (int)(NPKF + 0.25 * (SPKF - NPKF));
            THRESHOLD2 = (int)(0.5 * THRESHOLD1);

            RR_Average1_temp = RR;
            count_Rpeak();
          }
        }
      }
    }else{
      //Neu peak < THRESHOLD1
      NPKF = (int)(0.125 * peak + 0.875 * NPKF); //peak day la tin hieu dinh nhieu
      THRESHOLD1 = (int)(NPKF + 0.25 * (SPKF - NPKF));
      THRESHOLD2 = (int)(0.5 * THRESHOLD1);
    }
    count_peak();
  }
  count_interval();
  return detected;
}