#include "USART.h"
#include "gpioinit.h"
#include <stdio.h>
#include <stdarg.h>
void Ble_Init()
{
	gpioinit(GPIOA,PA9,GPIO_Mode_AF_PP);
	gpioinit(GPIOA,PA10,GPIO_Mode_IPU);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=9600;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1,ENABLE);
}
void USART_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
}

void USART_SendArray(u16 * Array , u8 Length)
{
	u8 i;
for (i=0;i<Length;i++)
USART_SendByte(Array[i]);
}

void USART_SendString(char * String)
{
	u8 i;
	for (i=0;String[i]!='\0';i++)
	USART_SendByte(String[i]);
}
u32 USART_POW(u32 X,u32 Y)
{
	u32 Result=1;
	while(Y--)
	{
		Result*=X;
	}
	return Result;
}

void USART_SendNum(u16 Num,u16 Lenght)
{
	u8 i;
	for(i=0;i<Lenght;i++)
	{
		USART_SendByte(Num/USART_POW(10,Lenght-i-1) %10+0x30);
	}
	
}


void USART_Printf(char * format,...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	USART_SendString(String);
}
