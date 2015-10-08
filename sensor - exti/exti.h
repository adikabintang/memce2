#ifndef EXTI_H_
#define EXTI_H_

#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_conf.h"
#include "misc.h"

uint16_t encoder, last_encoder;

void initExti();

#endif
