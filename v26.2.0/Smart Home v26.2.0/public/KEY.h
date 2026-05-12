#include "stm32f10x.h"
#ifndef KEY_H
#define	KEY_H
/******************根据需求修改***************************/
#define KEY1_Pin GPIO_Pin_6
#define KEY2_Pin GPIO_Pin_7
#define KEY3_Pin GPIO_Pin_8
#define KEY4_Pin GPIO_Pin_9

#define KEY1_Port GPIOB
#define KEY2_Port GPIOB
#define KEY3_Port GPIOB
#define KEY4_Port GPIOB

#define KEY1_EXTI_Line EXTI_Line6
#define KEY2_EXTI_Line EXTI_Line7
#define KEY3_EXTI_Line EXTI_Line8
#define KEY4_EXTI_Line EXTI_Line9

//#define KEY4_IRQChannel EXTI9_5_IRQn 
//#define KEY3_IRQChannel EXTI4_IRQn
//#define KEY2_IRQChannel EXTI2_IRQn
//#define KEY1_IRQChannel EXTI0_IRQn
/********************************************************/

void KEY_SET(void);
void KEY_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin);
void KEY_NVIC_EXTI(uint32_t EXTI_Line,IRQn_Type IRQn);
#endif
