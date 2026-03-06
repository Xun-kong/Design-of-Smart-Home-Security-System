#include "stm32f10x.h"
#ifndef _DHT11
#define _DHT11
#define DHT11_Pin PB1
#define DHT11_Port GPIOB
#define IN GPIO_Mode_IPD
#define OUT GPIO_Mode_Out_PP
void DHT11_Set(void);
uint8_t DHT11_Check(void);
uint8_t DHT11_Read_Bit(void);
uint8_t DHT11_Read_Byte(void);
uint8_t DHT11_Read_Data(u8 *humi,u8 *temp);
void DHT11_Mode(GPIOMode_TypeDef Mode);
#endif
