#include "gpioinit.h"
void gpioinit(GPIO_TypeDef*GPIOx,uint16_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode)
{

GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
GPIO_Init(GPIOx, &GPIO_InitStructure); 

}
