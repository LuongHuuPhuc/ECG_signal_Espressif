/**
 * @brief ECG su dung vTaskDelay() cua CPU
 * @note vTaskDelay() van phu thuoc vao FreeRTOS scheduler
 * @warning Neu in ra qua nhieu (dung printf() trong vong lap nhanh)
 *    - Chiem toan bo thoi gian CPU va task he thong 
 *    - Ngan khong cho cac task he thong chay: Task reset Watchdog, Idle Task, FreeRTOS housekeeping
 * Vi vay, sau mot thoi gian ngan neu WDT phat hien he thong "treo" do khong co task nao nha CPU thi reset ngay lap tuc
 * Ngoai ra con de bi Jitter (rung lac) tu scheduler
 */
#include <stdio.h>
#include <stdint.h>
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"
#include "filter.h" //Khai bao ca file source moi duoc =))) /???

#define ADC_CHANNEL ADC_CHANNEL_6 //GPIO34
#define ADC_UNIT ADC_UNIT_1
#define ADC_ATTEN ADC_ATTEN_DB_12 //Tang pham vi do 
#define ADC_WIDTH ADC_WIDTH_BIT_12
#define ADC_SAMPLE_RATE 100
#define BUZZER_PIN  17

//Buzzer configure
#define PWM_FREQ 1000
#define PWM_RES LEDC_TIMER_13_BIT
#define PWM_CHANNEL LEDC_CHANNEL_0
#define PWM_TIMER LEDC_TIMER_0
#define R_PEAK_THREASHOLD 3000 //Nguong toi thieu de phat hien dinh
#define NO_SIGNAL 0

static int prev_val = 0;
static int current_val = 0;
/**
 * @return 1 => Tim thay dinh
 * @return 0 => Khong thay dinh
 */
static int peak_detected = 0; 
btw_lowPass_filter_t butterworth_low_pass_filter;
static const char *TAG = "ADC";
TaskHandle_t readADTask_handle = NULL;

void __attribute__((unused))pwm_init(){
  ledc_timer_config_t ledc_timer = {
    .duty_resolution = PWM_RES,
    .freq_hz = PWM_FREQ,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .timer_num = PWM_TIMER, 
  };

  ledc_timer_config(&ledc_timer);

  //Cau hinh kenh PWM
  ledc_channel_config_t ledc_channel = {
    .channel = PWM_CHANNEL,
    .duty = 0,
    .gpio_num = BUZZER_PIN,
    .speed_mode = LEDC_HIGH_SPEED_MODE,
    .timer_sel = PWM_TIMER,
    .hpoint = 0,
  };

  ledc_channel_config(&ledc_channel);
}

//Ham dieu khien buzzer su dung PWM duty cycle
void buzzer_on_pwm(){
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, 4095); //Max duty
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
}

void buzzer_off_pwm(){
  ledc_set_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL, 0); //Max duty
  ledc_update_duty(LEDC_HIGH_SPEED_MODE, PWM_CHANNEL);
}

void __attribute__((unused))buzzer_for_peak(int status){
  if(status == 1){
    buzzer_on_pwm();
    vTaskDelay(pdMS_TO_TICKS(100));
    buzzer_off_pwm();
  }else if(status == 2){
    buzzer_on_pwm(); //Keu lien tuc 
  }
} 

int __attribute__((unused))detect_peak(int sample){
  current_val = sample;
  //Neu gia tri lon hon nguong toi thieu va gia tri truoc do be hon nguong toi thieu
  if(current_val > R_PEAK_THREASHOLD && prev_val <= R_PEAK_THREASHOLD){
    peak_detected = 1;
  }else if(current_val == NO_SIGNAL){ //Neu bien do bang khong (ko co tin hieu)
    peak_detected = 2;
  }else{
    peak_detected = 0;
  }
  prev_val = sample;
  return peak_detected;
}

void adc_configure(){
  adc1_config_width(ADC_WIDTH);
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN); //Suy hao
  ESP_LOGI(TAG, "ADC Configured: Channel: %d, Attenuation: %d", ADC_CHANNEL, ADC_ATTEN);
}

void read_AD8232(void *pvParameter){
  adc_configure();
  ESP_LOGI(TAG, "Bat dau doc cam bien AD8232");

  //Low-pass butterworth de loai bo tan so tren 50Hz
  // butterworth_filter_init(&butterworth_low_pass_filter, 200.0f, 50.0f);
  while(true){
    int sample = (adc1_get_raw(ADC_CHANNEL));
    printf("%d\n", sample);
    // buzzer_for_peak(detect_peak(sample));
    vTaskDelay(pdMS_TO_TICKS(1000 / ADC_SAMPLE_RATE)); //Tan so lay mau cua ADC duoc the hien qua ham nay
    /**
     * @bug De tan so lay mau 100Hz -> delay 10ms thi chay duoc nhung de tu 200Hz tro len thi bi WDT reset ?
     */
  }
}

void app_main(void){
  // pwm_init();
  xTaskCreatePinnedToCore(read_AD8232, "Read AD8323", 1024 * 4, NULL, 5, &readADTask_handle, 1);
}
