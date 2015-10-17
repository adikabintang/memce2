/*
 * Author: Adika Bintang Sulaeman
 * Tim Memce2 (Jendra R. Dwiputra, Sanadhi Sutandi, Adika Bintang Sulaeman)
 * Device: STM32F103C8 - Where to buy: Andra Risciawan (brontoseno.com)
 * Several libraries are taken from and inspired by:
 * stm32f4-discovery.com, http://www.diller-technologies.de/, https://github.com/ppkt
 *
 *  ---------------------------------------------------------------------------------
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *  ---------------------------------------------------------------------------------
 *
 */
#include <semihosting.h>
#include "sensor - adc/adc.h"
#include "sensor - i2c/bmp180.h"
#include "sensor - exti/exti.h"
#include "sensor - i2c/i2c_dma.h"
#include "sim900a/sim900a.h"
#include "utils.h"
#include "mytime.h"
#include "dht22.h"

//BMP180: SCL ke B10, SDA ke B11
//Tx ke A9

uint32_t timeStamp = 0;
uint32_t lastDHT22update = 0;

#define DHT_UPDATE_INTERVAL 2000 //10 seconds

DHT22_Data Current_DHT22_Reading;

void Configure_HSI_Clock()
{
	FLASH_SetLatency(FLASH_ACR_LATENCY_2);

	RCC_HSICmd(ENABLE);
	RCC_HSEConfig(DISABLE);
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_CFGR_PLLMULL16);
	RCC_PLLCmd(ENABLE);
	while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLK1Config(RCC_HCLK_Div1);
	RCC_PCLK2Config(RCC_HCLK_Div1);
	RCC_ADCCLKConfig(RCC_PCLK2_Div2);
}

void SetSystemClockOut()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2ENR_AFIOEN, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	RCC_MCOConfig(RCC_MCO_PLLCLK_Div2);
}


int main(void)
{
	int press = 0, i;
	SystemInit();
	InitializeTimer();
	EnableTimerInterrupt();
	ADCInit();
	I2C_LowLevel_Init(I2C2);
	initExti();
	SIM900A_init();
	initDeteksiSIM800L();
	Configure_HSI_Clock();
	Init_Time(MILLISEC,64);
	DHT22_Init();

	turnOffSIM800L();

	// Tick every 1 ms
	if (SysTick_Config(SystemCoreClock / 1000))  while (1);

	if (bmp180_check_presence()) {
		printf("Sensor is present\n\r");
	} else {
		printf("Sensor is NOT present\n\r");
		//while(1){}
	}

    while(1)
    {
    	if (menit >= 1) {
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
	uint16_t hujan, cahaya, angin, batteryMikon;
	batteryMikon = read_adc(ADC_Channel_4);
	cahaya = read_adc(ADC_Channel_5);//malem > 3490
	if (batteryMikon > 3965) {//bates batre udah 3.7v
		lastDHT22update = Millis();
		DHT22_Start_Read(&Current_DHT22_Reading);
		printf("%d\n\r", (int)Current_DHT22_Reading.Humid);
		CalibrationData data;
		data.oss = 3;
		bmp180_get_calibration_data(&data);
		bmp180_get_uncompensated_temperature(&data);
		bmp180_get_uncompensated_pressure(&data);
		bmp180_calculate_true_temperature(&data);
		bmp180_calculate_true_pressure(&data);
		bmp180_get_absolute_altitude(&data);

		suhu = data.T / 10;
		hujan = read_adc(ADC_Channel_6);
		angin = speed;
		turnOnSIM800L();
		if (getBatteryPercentageSIM() > 88) {
			sendData(suhu, (int)Current_DHT22_Reading.Humid, angin, data.p, cahaya, hujan);
		}
		turnOffSIM800L();
	}
}

/*
void SysTick_Handler(void)
{
  delay_decrement();
}
*/
