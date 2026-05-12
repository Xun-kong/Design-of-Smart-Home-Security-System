#include "stm32f10x.h"
#ifndef KEY_H
#define	KEY_H
/******************根据需求修改***************************/
#define KEY1_Pin GPIO_Pin_6
#define KEY2_Pin GPIO_Pin_4
#define KEY3_Pin GPIO_Pin_2
#define KEY1_Port GPIOA
#define KEY2_Port GPIOA
#define KEY3_Port GPIOA
#define KEY1_EXTI_Line EXTI_Line6
#define KEY2_EXTI_Line EXTI_Line4
#define KEY3_EXTI_Line EXTI_Line2
#define KEY1_IRQChannel EXTI9_5_IRQn 
#define KEY2_IRQChannel EXTI4_IRQn
#define KEY3_IRQChannel EXTI2_IRQn
/********************************************************/

void KEY_SET(void);
void KEY_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,uint32_t EXTI_Line,IRQn_Type IRQn);
void KEY_NVIC_EXTI(uint32_t EXTI_Line,IRQn_Type IRQn);
#endif
