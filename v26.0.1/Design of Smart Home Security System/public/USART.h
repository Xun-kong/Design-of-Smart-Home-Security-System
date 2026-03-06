#include "stm32f10x.h"
#ifndef USART_h
#define USART_h
	void Ble_Init(void);
	void USART_SendByte(u8 Byte);
	void USART_SendArray(u16 * Array , u8 Length);
	void USART_SendString(char * String);
	void USART_SendNum(u16 Num,u16 Lenght);
	void USART_Printf(char * format,...);		//串口打印
#endif
