#include "stm32f10x.h"
#ifndef TIMER_H
#define TIMER_H
void TIM2_NVIC_Configuration(void);
void TIM3_NVIC_Configuration(void);
void TIM4_NVIC_Configuration(void);
void TIM3_IRQHandler(void);
void TIM2_IRQHandler(void);
#endif
