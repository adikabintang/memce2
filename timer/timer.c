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
        printf("\tencoder: %d, rpm: %d, speed: %d\n", encoder, rpm, speed);
        encoder = 0;
        detik++;
        if (detik == 60 && menit != 10) {
        	menit++;
        	detik = 0;
        }

        if (menit >= 10) {
        	//do something...
        	//collect data & send, abis itu baru menit = 0
        	collectAndSend();
        	detik = 0;
        	menit = 0;
        }
    }
}

void collectAndSend() {
	uint8_t suhu;
	uint16_t hujan, kelembaban, cahaya, angin, tekanan;
	CalibrationData data;
	data.oss = 3;

	suhu = read_adc(ADC_Channel_1);
	hujan = read_adc(ADC_Channel_2);
	kelembaban = read_adc(ADC_Channel_3);
	cahaya = read_adc(ADC_Channel_4);
	angin = speed;
	tekanan = bmp180_calculate_true_pressure(&data);
	delayAbisI2C();
	sendData(suhu, kelembaban, angin, tekanan, cahaya, hujan);
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
