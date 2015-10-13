#include "timer.h"
#include "exti.h"
#include "stm32f10x_adc.h"
#include "bmp180.h"

void InitializeTimer()
{
	encoder = 0;
	last_encoder = 0;
	detik = 0;
	menit = 0;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	// TIM clock = 72 MHz,
	//Update event time = 1 / [(72 * 10^6) / (TIM_Prescaler * TIM_Period)]
    TIM_TimeBaseInitTypeDef timerInitStructure;

    timerInitStructure.TIM_Prescaler = 36000-1;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 2000-1;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
    TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
}

void EnableTimerInterrupt()
{
    NVIC_InitTypeDef nvicStructure;

    nvicStructure.NVIC_IRQChannel = TIM2_IRQn;
    nvicStructure.NVIC_IRQChannelPreemptionPriority = 0;
    nvicStructure.NVIC_IRQChannelSubPriority = 1;
    nvicStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvicStructure);
}

void TIM2_IRQHandler()
{
	int selisih = 0;
	int speed = 0;
	int rpm = 0;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

        //r = 6cm
        selisih = (encoder - last_encoder) < 0 ? ((encoder - last_encoder) * -1) : (encoder - last_encoder);
        rpm = (int)selisih/50 * 60;
        speed = 2 * 3.14 * 6 * 0.00001 * 60 * rpm;
        last_encoder = encoder;
        //printf("\tencoder: %d, rpm: %d, speed: %d\n", encoder, rpm, speed);
        encoder = 0;
        detik++;

        if (detik == 3 && menit != 10) {
        	menit++;

        	printf("detik: %d\n\r", detik);

        }


    }
}

void delayAbisI2C() {
	int i;
	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
	    	for (i = 0; i < 99999; i++);
}
