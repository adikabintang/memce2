#include "sim900a.h"

int i;

void SIM900A_init(void)
{
    /* USART configuration structure for USART1 */
    USART_InitTypeDef usart1_init_struct;
    /* Bit configuration structure for GPIOA PIN9 and PIN10 */
    GPIO_InitTypeDef gpioa_init_struct;

    /* Enalbe clock for USART1, AFIO and GPIOA */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_AFIO |
                           RCC_APB2Periph_GPIOA, ENABLE);

    /* GPIOA PIN9 alternative function Tx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_9;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Init(GPIOA, &gpioa_init_struct);
    /* GPIOA PIN9 alternative function Rx */
    gpioa_init_struct.GPIO_Pin = GPIO_Pin_10;
    gpioa_init_struct.GPIO_Speed = GPIO_Speed_50MHz;
    gpioa_init_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &gpioa_init_struct);

    /* Enable USART1 */
    USART_Cmd(USART1, ENABLE);
    /* Baud rate 9600, 8-bit data, One stop bit
     * No parity, Do both Rx and Tx, No HW flow control
     */
    usart1_init_struct.USART_BaudRate = 19200; //9600
    usart1_init_struct.USART_WordLength = USART_WordLength_8b;
    usart1_init_struct.USART_StopBits = USART_StopBits_1;
    usart1_init_struct.USART_Parity = USART_Parity_No ;
    usart1_init_struct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    usart1_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    /* Configure USART1 */
    USART_Init(USART1, &usart1_init_struct);
    /* Enable RXNE interrupt */
    //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    /* Enable USART1 global interrupt */
    NVIC_EnableIRQ(USART1_IRQn);
}

void delayBuatSIM() {
	int i = 0;
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 300000; i++);
	for (i = 0; i < 500000; i++);
	for (i = 0; i < 500000; i++);
	for (i = 0; i < 500000; i++);
	for (i = 0; i < 500000; i++);
	for (i = 0; i < 500000; i++);
	for (i = 0; i < 500000; i++);
}

void delayBuatHttpReq(int lama) {
	int i, j;
	for (j = 0; j <= lama; j++) {
		for (i = 0; i < 500000; i++);
		for (i = 0; i < 300000; i++);
		for (i = 0; i < 300000; i++);
		for (i = 0; i < 300000; i++);
		for (i = 0; i < 300000; i++);
		for (i = 0; i < 300000; i++);
		for (i = 0; i < 300000; i++);
		for (i = 0; i < 300000; i++);
	}
}

void initializingGPIOSIM() {
	//SystemInit();
	GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitTypeDef GPIOKedua;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
   	GPIO_StructInit(&GPIOKedua);
   	GPIOKedua.GPIO_Pin = GPIO_Pin_13;
   	GPIOKedua.GPIO_Mode = GPIO_Mode_Out_PP;
   	GPIOKedua.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init( GPIOB, &GPIOKedua);
}

void sendSMS() {
	int i;
	for (i = 0; i < 12; i++) {
		delayBuatSIM();
	}
	delayBuatSIM();
	TM_USART_Puts(USART1, "AT+CMGF=1\r");
	delayBuatSIM();
	TM_USART_Puts(USART1, "AT + CMGS = \"+6285695737112\"\r");
	delayBuatSIM();
	TM_USART_Puts(USART1, "wei\r");
	delayBuatSIM();
	USART_SendData(USART1, 26);
	delayBuatSIM();
	USART_SendData(USART1, 13);
}

void sendData(int suhu, int kelembaban, int kecAngin, int tekanan, int cahaya, int hujan) {
	char url[420] = "AT+HTTPPARA=\"URL\",\"http://c146ec43.ngrok.io/memce2-web/web/index.php/location/getsuhu?suhu=";
	char danKelembaban[14] = "&kelembaban=";
	char danKecAngin[12] = "&kecAngin=";
	char danTekanan[12] = "&tekanan=";
	char danCahaya[11] = "&cahaya=";
	char danHujan[10] = "&hujan=";
	char buff[10];
	int i, j;

	for (i = 0; i < 14; i++) {
		delayBuatSIM();
	}

	sprintf(buff, "%d", suhu);
	j = strlen(url);
	for (i = 0; i < strlen(buff); i++) {
	    url[j++] = buff[i];
	}
	j = strlen(url);
	for (i = 0; i < strlen(danKelembaban); i++) {
	    url[j++] = danKelembaban[i];
	}
	sprintf(buff, "%d", kelembaban);
	j = strlen(url);
	for (i = 0; i < strlen(buff); i++) {
	    url[j++] = buff[i];
	}
	j = strlen(url);
	for (i = 0; i < strlen(danKecAngin); i++) {
	    url[j++] = danKecAngin[i];
	}
	sprintf(buff, "%d", kecAngin);
	j = strlen(url);
	for (i = 0; i < strlen(buff); i++) {
	    url[j++] = buff[i];
	}
	j = strlen(url);
	for (i = 0; i < strlen(danTekanan); i++) {
	    url[j++] = danTekanan[i];
	}
	sprintf(buff, "%d", tekanan);
	j = strlen(url);
	for (i = 0; i < strlen(buff); i++) {
	    url[j++] = buff[i];
	}
	j = strlen(url);
	for (i = 0; i < strlen(danCahaya); i++) {
	    url[j++] = danCahaya[i];
	}
	sprintf(buff, "%d", cahaya);
	j = strlen(url);
	for (i = 0; i < strlen(buff); i++) {
	    url[j++] = buff[i];
	}
	j = strlen(url);
	for (i = 0; i < strlen(danHujan); i++) {
	    url[j++] = danHujan[i];
	}
	sprintf(buff, "%d", hujan);
	j = strlen(url);
	for (i = 0; i < strlen(buff); i++) {
	    url[j++] = buff[i];
	}
	url[j++] = '"';
	url[j++] = '\r';
	url[j] = '\0';


	TM_USART_Puts(USART1, "AT+CSQ\r");
	delayBuatHttpReq(4);

	TM_USART_Puts(USART1, "AT+CGATT?\r");
	delayBuatHttpReq(4);

	TM_USART_Puts(USART1, "AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"\r");//setting the SAPBR, the connection type is using gprs
	delayBuatHttpReq(15);

	TM_USART_Puts(USART1, "AT+SAPBR=3,1,\"APN\",\"internet\"\r");//setting the APN, the second need you fill in your local apn server
	delayBuatHttpReq(48);

	TM_USART_Puts(USART1, "AT+SAPBR=1,1\r");//setting the SAPBR, for detail you can refer to the AT command mamual
	delayBuatHttpReq(30);

	TM_USART_Puts(USART1, "AT+HTTPINIT\r"); //init the HTTP request
	delayBuatHttpReq(30);

	//TM_USART_Puts(USART1, "AT+HTTPPARA=\"URL\",\"http://c146ec43.ngrok.io/memce2-web/web/index.php/location/getsuhu?suhu=28\"\r");// setting the httppara, the second parameter is the website you want to access
	TM_USART_Puts(USART1, url);// setting the httppara, the second parameter is the website you want to access
	delayBuatHttpReq(33);

	TM_USART_Puts(USART1, "AT+HTTPACTION=0\r");//submit the request
	delayBuatHttpReq(120);//the delay is very important, the delay time is base on the return from the website, if the return datas are very large, the time required longer.
}

typedef struct {
	uint8_t *Buffer;
	uint16_t Size;
	uint16_t Num;
	uint16_t In;
	uint16_t Out;
	uint8_t Initialized;
	uint8_t StringDelimiter;
} TM_USART_t;

uint8_t TM_USART1_Buffer[1024];

TM_USART_t TM_USART1 = {TM_USART1_Buffer, 1024, 0, 0, 0, 0, '\r'};

TM_USART_t* TM_USART_INT_GetUsart(USART_TypeDef* USARTx) {
	TM_USART_t* u;

#ifdef USE_USART1
	if (USARTx == USART1) {
		u = &TM_USART1;
	}
#endif
	return u;
}

void TM_USART_Puts(USART_TypeDef* USARTx, char* str) {
	TM_USART_t* u = TM_USART_INT_GetUsart(USARTx);
	/* If we are not initialized */
	/*if (u->Initialized == 0) {
		return;
	}*/

	/* Go through entire string */
	while (*str) {
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
		/* Send data */
		USARTx->DR = (uint16_t)(*str++ & 0x01FF);
		/* Wait to be ready, buffer empty */
		USART_WAIT(USARTx);
	}
}

/*
 * contoh cara pake:
int main(void)
{
	int i = 0, counter = 0;
	SystemInit();
	//initializingGPIO();
	SIM900A_init();
	sendData(12, 13, 14, 15, 16, 17);
	while(1)
    {
		//printf("oke\n");
		//USART_SendData(USART1, 'a');
    }
}
 */
