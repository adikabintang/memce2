#ifndef ADC_H_
#define ADC_H_

#include "stm32f10x_adc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void ADCInit(void);
int read_adc(uint8_t ADC_Channel);

#endif
