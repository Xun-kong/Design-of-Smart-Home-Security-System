#include "TIMER.h"
#include "DHT11.h"
#include "OLED.h"
#include "KEY.h"
#include "USART.h"
#include "gpioinit.h"
void TIM2_NVIC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 ,ENABLE);//时钟使能
	TIM_InternalClockConfig(TIM2);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1; //初频
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; //预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(& NVIC_InitStructure);
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	NVIC_ClearPendingIRQ(TIM2_IRQn);//清中断
	
	TIM_Cmd(TIM2,ENABLE);
}

/*中断服务程序*/
extern u8 read,dat,temp,humi;
char hu[8];
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//查询标志位
	{
	
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除标志位
	}
}
