#include "stm32f10x.h"
#include "delay.h"
#ifndef gpioinit_h
#define gpioinit_h
#define PA0 GPIO_Pin_0
#define PA1 GPIO_Pin_1
#define PA2 GPIO_Pin_2
#define PA3 GPIO_Pin_3
#define PA4 GPIO_Pin_4
#define PA5 GPIO_Pin_5
#define PA6 GPIO_Pin_6
#define PA7 GPIO_Pin_7
#define PA8 GPIO_Pin_8
#define PA9 GPIO_Pin_9
#define PA10 GPIO_Pin_10
#define PA11 GPIO_Pin_11
#define PA12 GPIO_Pin_12
#define PA13 GPIO_Pin_13
#define PA14 GPIO_Pin_14
#define PA15 GPIO_Pin_15
#define PB0 GPIO_Pin_0
#define PB1 GPIO_Pin_1
#define PB2 GPIO_Pin_2
#define PB3 GPIO_Pin_3
#define PB4 GPIO_Pin_4
#define PB5 GPIO_Pin_5
#define PB6 GPIO_Pin_6
#define PB7 GPIO_Pin_7
#define PB8 GPIO_Pin_8
#define PB9 GPIO_Pin_9
#define PB10 GPIO_Pin_10
#define PB11 GPIO_Pin_11
#define PB12 GPIO_Pin_12
#define PB13 GPIO_Pin_13
#define PB14 GPIO_Pin_14
#define PB15 GPIO_Pin_15
#define ALL GPIO_Pin_All
void gpioinit(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode);
#endif
