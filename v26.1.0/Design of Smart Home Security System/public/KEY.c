#include "KEY.h"
#include "gpioinit.h"

void KEY_SET()
{
KEY_Init(KEY1_Port,KEY1_Pin,KEY1_EXTI_Line,KEY1_IRQChannel);
KEY_Init(KEY2_Port,KEY2_Pin,KEY2_EXTI_Line,KEY2_IRQChannel);
KEY_Init(KEY3_Port,KEY3_Pin,KEY3_EXTI_Line,KEY3_IRQChannel);
}


void KEY_Init(GPIO_TypeDef *GPIOx,uint16_t GPIO_Pin,uint32_t EXTI_Line,IRQn_Type IRQn)
{
GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB,ENABLE);
GPIO_Init(GPIOx, &GPIO_InitStructure); 
KEY_NVIC_EXTI(EXTI_Line,IRQn);
}


void KEY_NVIC_EXTI(uint32_t EXTI_Line,IRQn_Type IRQn)
{
		EXTI_InitTypeDef EXTI_InitStructure;													//定义结构体，配置外部中断
		EXTI_ClearITPendingBit(EXTI_Line);												//清除中断标志位
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);						//GPIO复用使能
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,KEY1_Pin);//设置中断使用的GPIO口和引脚
		EXTI_InitStructure.EXTI_Line=EXTI_Line;//|EXTI_Line4|EXTI_Line2;									//设置中断源
		EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt;							//设置中断模式为外部中断
		EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising;				//设置中断触发方式
		EXTI_InitStructure.EXTI_LineCmd=ENABLE;												//使能选中线路的新状态
		EXTI_Init(&EXTI_InitStructure);					

		NVIC_InitTypeDef NVIC_InitStructure;
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		NVIC_InitStructure.NVIC_IRQChannel=IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4; 
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
		NVIC_Init(& NVIC_InitStructure);
		NVIC_ClearPendingIRQ(IRQn);//清中断
}


void EXTI9_5_IRQHandler()
{
	if(EXTI_GetFlagStatus (EXTI_Line6)==SET)//按键3按下
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//使能进入TIM4中断函数用于按键消抖
	 

}


void EXTI4_IRQHandler()
{
	if(EXTI_GetFlagStatus (EXTI_Line4)==SET)//按键2按下
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
}



//void EXTI3_IRQHandler()
//{
//	if(EXTI_GetFlagStatus (EXTI_Line3)==SET)
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
//}


void EXTI2_IRQHandler()
{
	if(EXTI_GetFlagStatus (EXTI_Line2)==SET)////按键1按下
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
}


//void EXTI1_IRQHandler()
//{
//	if(EXTI_GetFlagStatus (EXTI_Line1)==SET)//
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
//}

//void EXTI0_IRQHandler()
//{
//	if(EXTI_GetFlagStatus (EXTI_Line1)==SET)//
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
//}
