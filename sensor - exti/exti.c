#include "exti.h"

void GPIO_Init_A() {
	GPIO_InitTypeDef GPIOKedua;

		/* Enable clock for SYSCFG */
	    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	   	GPIO_StructInit(&GPIOKedua);
	   	GPIOKedua.GPIO_Pin = GPIO_Pin_0;
	   	GPIOKedua.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	   	GPIOKedua.GPIO_Speed = GPIO_Speed_50MHz;
	    GPIO_Init(GPIOB, &GPIOKedua);

}

//ini buat exti
void initExti() {
	GPIO_Init_A();

	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	/* Tell system that you will use PD0 for EXTI_Line0 */
	//SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource0);

    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);
	/* PD0 is connected to EXTI_Line0 */
    EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	/* Enable interrupt */
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	/* Interrupt mode */
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	/* Triggers on rising and falling edge */
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	/* Add to EXTI */
	EXTI_Init(&EXTI_InitStruct);

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x03;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void EXTI0_IRQHandler(void){
  EXTI_ClearITPendingBit(EXTI_Line0);
  encoder++;
}
