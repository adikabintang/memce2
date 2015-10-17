#ifndef SIM900A_H_
#define SIM900A_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "timer.h"
#include "misc.h"
#include "stdbool.h"

#define USART_WAIT(USARTx)                  do { while (!((USARTx)->SR & USART_FLAG_TXE)); } while (0)

bool udah;
char received_string[64];

void TM_USART_Puts(USART_TypeDef* USARTx, char* str);
void sendData(int suhu, int kelembaban, int kecAngin, int tekanan, int cahaya, int hujan);
void sendSMS();
void initializingGPIOSIM();
void delayBuatHttpReq(int lama);
void delayBuatSIM();
void SIM900A_init(void);
void USART1_IRQHandler(void);
void readUsart();
void initDeteksiSIM800L();
void turnOffSIM800L();
void turnOnSIM800L();
int stringToInt(char* a);
uint8_t getBatteryPercentageSIM();

#endif
