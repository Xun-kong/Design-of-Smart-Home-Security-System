#include "stm32f10x.h"
#include "TIMER.h"
#include "gpioinit.h"
#include "PWM.h"
#include "delay.h"
#include "OLED.h"
#include "KEY.h"
#include "mq2.h"
#include "USART.h"
extern u8 temp,humi,t,h,m,n,x;
u8 value,Flame,data;
int main(void)
{
Ble_Init();														//蓝牙模块初始化
gpioinit(GPIOA,PA11,GPIO_Mode_Out_PP);//初始化LED引脚
gpioinit(GPIOA,PA8,GPIO_Mode_Out_PP);
gpioinit(GPIOA,PA1,GPIO_Mode_Out_PP);//初始化蜂鸣器引脚
gpioinit(GPIOA,PB0,GPIO_Mode_IPU);// 初始化火焰传感器引脚
GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET);//关闭蜂鸣器（低电平触发）
TIM2_NVIC_Configuration();
TIM3_NVIC_Configuration();
TIM4_NVIC_Configuration();
OLED_Page1();
KEY_SET();
MQ2_Init();
GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);	
while(1)
{
	
	value = MQ2_GetData();
	Flame=GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0);
	OLED();
	
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
		data=USART_ReceiveData(USART1);														//蓝牙模块接收数据
	
/************************超过阈值蜂鸣器报警*************************/
	//if (temp>=t)  OLED_ShowChinese(0,4,"注意火灾"),GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);
	if (Flame==0|temp>=t) OLED_ShowChinese(0,4,"注意火灾"),GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET),GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET),GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);
	else if (humi>=h)  OLED_ShowChinese(0,4,"注意水灾"),GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET),GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET),GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);
	else if (value==1) OLED_ShowChinese(0,4,"注意燃气，烟雾"),GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET),GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_SET),GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_RESET);
	else OLED_ShowString(0,4,"                ",8),GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET),GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET),GPIO_WriteBit(GPIOA,GPIO_Pin_11,Bit_RESET);
/********************************app遥控****************************/	
	
	if(data==1)x++,data=0;
	if(data==2&x==2)n++,data=0;
	if(data==3&x==2)n--,data=0;
	if(data==2&x==1)m++,data=0;
	if(data==3&x==1)m--,data=0;
	if(data==4)	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);				//app开启蜂鸣器
	if(data==5)	GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_SET),data=0;					//app关闭蜂鸣器
	//OLED_ShowNum(0,4,data,8);
}
}
//火焰传感器 PA0
