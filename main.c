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

int main(void)
{
	SystemInit();
	ADCInit();
	I2C_LowLevel_Init(I2C1);
	initExti();
	SIM900A_init();

	if (bmp180_check_presence()) {
		printf("Sensor is present\n\r");
	} else {
		printf("Sensor is NOT present\n\r");
		//while(1){}
	}

    while(1)
    {

    }
}
