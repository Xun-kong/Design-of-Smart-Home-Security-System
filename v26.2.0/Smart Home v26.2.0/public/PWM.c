#include "PWM.h"
void PWM_Init(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Init(GPIOA, &GPIO_InitStructure); 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	TIM_TimeBaseStructure.TIM_Period = 100 - 1; //ARR
	TIM_TimeBaseStructure.TIM_Prescaler = 720 - 1; //PSC
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
	TIM_Cmd(TIM2,ENABLE);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
	TIM_OCInitStructure.TIM_Pulse = 50; //CCR 占空比为50％
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC1Init(TIM2, & TIM_OCInitStructure);

}

void pwmset(uint16_t Compare)
{
	TIM_SetCompare1(TIM2,Compare);
}
