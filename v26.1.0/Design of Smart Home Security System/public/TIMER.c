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
	TIM_TimeBaseStructure.TIM_Period = 2000 - 1; //初频
	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1; //预分频
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
void TIM3_NVIC_Configuration(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 ,ENABLE);//时钟使能
	TIM_InternalClockConfig(TIM3);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	TIM_TimeBaseStructure.TIM_Period = 3000 - 1; //初频
	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1; //预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(& NVIC_InitStructure);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	NVIC_ClearPendingIRQ(TIM3_IRQn);
	
	TIM_Cmd(TIM3,ENABLE);
}
void TIM4_NVIC_Configuration(void)		//用于检测按键并去抖动
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 ,ENABLE);//时钟使能
	TIM_InternalClockConfig(TIM4);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure; 
	TIM_TimeBaseStructure.TIM_Period = 50 - 1; //初频
	TIM_TimeBaseStructure.TIM_Prescaler = 36000 - 1; //预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, & TIM_TimeBaseStructure);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(& NVIC_InitStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);//使能中断
	NVIC_ClearPendingIRQ(TIM4_IRQn);

	TIM_Cmd(TIM4,ENABLE);
}
/*中断服务程序*/
extern u8 read,dat,temp,humi,data;
char hu[8];
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2,TIM_IT_Update)==SET)//查询标志位
	{
	read=1,dat=!dat;
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//清除标志位
	}
}
void TIM3_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		USART_Printf("当前温度"),USART_SendNum(temp,2),
		USART_Printf("当前湿度"),USART_SendNum(humi,2);
		
//	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE);	
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}
void TIM4_IRQHandler(void)
{
	extern u8 x,m,y,n;
		if(EXTI_GetFlagStatus (EXTI_Line6)==SET&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)==SET){x++;}
		else if(EXTI_GetFlagStatus (EXTI_Line4)==SET&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==SET&x==1){m++;}
		else if(EXTI_GetFlagStatus (EXTI_Line4)==SET&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)==SET&x==2){n++;}
		else if(EXTI_GetFlagStatus (EXTI_Line2)==SET&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==SET&x==1){m--;}
		else if(EXTI_GetFlagStatus (EXTI_Line2)==SET&GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_2)==SET&x==2){n--;}
		TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		EXTI_ClearITPendingBit(EXTI_Line6|EXTI_Line4|EXTI_Line2);

}
