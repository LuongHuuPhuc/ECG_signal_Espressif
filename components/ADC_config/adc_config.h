/**
 * @brief File cau hinh menuconfig ADC 
 * @author Luong Huu Phuc & chatGPT
 */
#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#include "sdkconfig.h"

#define ADC_CALIBRATION_ENABLED CONFIG_ADC_ENABLE_CALIBRATION
#define ADC_DMA_ENABLED CONFIG_ADC_ENABLE_DMA
#define ADC_BIT_WIDTH CONFIG_ADC_BIT_WIDTH 
#define ADC_ATTENUATION CONFIG_ADC_ATTENUATION
#define ADC_SAMPLING_RATE CONFIG_ADC_SAMPLING_RATE
#define ADC_DMA_BUFFER_SIZE CONFIG_ADC_DMA_BUFFER_SIZE

/**
 * @brief Ham tu dong cau hinh ADC
 */
void adc_menuconfig();

#endif //ADC_CONFIG_H_