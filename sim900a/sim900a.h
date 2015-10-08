#ifndef SIM900A_H_
#define SIM900A_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "timer.h"

#define USART_WAIT(USARTx)                  do { while (!((USARTx)->SR & USART_FLAG_TXE)); } while (0)

void TM_USART_Puts(USART_TypeDef* USARTx, char* str);
void sendData(int suhu, int kelembaban, int kecAngin, int tekanan, int cahaya, int hujan);
void sendSMS();
void initializingGPIOSIM();
void delayBuatHttpReq(int lama);
void delayBuatSIM();
void SIM900A_init(void);

#endif
