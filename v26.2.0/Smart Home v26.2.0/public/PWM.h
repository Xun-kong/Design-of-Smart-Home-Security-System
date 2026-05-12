#include "stm32f10x.h"
#include "gpioinit.h"
#ifndef PWM_H
#define PWM_H
void pwmset(uint16_t Compare);
void PWM_Init(void);
void NVIC_Configuration(void);
void TIM2_EXTI(void);
#endif
