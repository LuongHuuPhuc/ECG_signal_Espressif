/**
 * @brief File khoi tao cau hinh ADC tu menuconfig
 * @author Luong Huu Phuc & chatGPT
 */
#include<stdio.h>
#include"adc_config.h"
#include"esp_log.h"

static const char *TAG = "ADC_CONFIG";

void adc_menuconfig(){
  ESP_LOGI(TAG, "ADC Calibration: %s", ADC_CALIBRATION_ENABLED ? "Enabled" : "Disabled");
  ESP_LOGI(TAG, "ADC DMA Mode: %s", ADC_DMA_ENABLED ? "Enabled" : "Disabled");
  ESP_LOGI(TAG, "ADC Bit Width: %d-bit", ADC_BIT_WIDTH);
  ESP_LOGI(TAG, "ADC Attenuation: %ddB", ADC_ATTENUATION);
  ESP_LOGI(TAG, "ADC Sampling Rate: %dHz", ADC_SAMPLING_RATE);
  ESP_LOGI(TAG, "ADC DMA Buffer Size: %dbytes", ADC_DMA_BUFFER_SIZE);
}