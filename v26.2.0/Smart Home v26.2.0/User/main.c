#include "stm32f10x.h"
#include "FreeRtos.h"
#include "task.h"
#include "TIMER.h"
#include "gpioinit.h"
#include "PWM.h"
#include "delay.h"
#include "OLED.h"
#include "KEY.h"
#include "mq2.h"
#include "DHT11.h"
#include "USART.h"
extern u8 tem,hum,warn,wron,sleeptime,Menu;
u16 value;float PPM;
u8 temp,humi,count;

u8 ble,flamewron,mq2wron,tempwron,humiwron;

TaskHandle_t DHT11TaskHandler,OLEDTaskHandler,BleTaskHandler,MQ2TaskHandler;

//创建任务每间隔1s调用DHT11模块读取数据并监测数据是否异常            
void DHT11Task(void *arg)
{
	while(1) {vTaskSuspendAll();
						DHT11_Read_Data(&humi,&temp);
						xTaskResumeAll();
						if(temp>tem) USART_Printf("注意火灾\n"),tempwron=1;else tempwron=0;//温度异常
						if(humi>hum) USART_Printf("注意水灾\n"),humiwron=1;else humiwron=0;//湿度异常
						vTaskDelay(pdMS_TO_TICKS(1000));
	}
}
//创建任务每间隔50ms调用菜单函数刷新OLED显示屏
void OLEDTask(void *oled)
{
		while(1) {if(wron) GPIO_SetBits(GPIOB,PA5),GPIO_ResetBits(GPIOB,PA6);
							else GPIO_ResetBits(GPIOB,PA5),GPIO_SetBits(GPIOB,PB6);
							OLED_Menu();
							vTaskDelay(pdMS_TO_TICKS(50));}
}
//创建任务每间隔50ms查询蓝牙模块接收数据内容改变标志位
void BleTask(void *Ble)
{
	while(1) {if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==SET)
						ble=USART_ReceiveData(USART1);
						vTaskDelay(pdMS_TO_TICKS(50));}
}
//创建任务每间隔3s控制蓝牙模块发送温湿度
void USARTTask(void *USART)
{
	while(1) {USART_Printf("当前温度:%d℃\n",temp);
						USART_Printf("当前湿度:%d%%RH\n",humi);
						USART_Printf("烟雾浓度:%.2fppm\n",PPM);
						vTaskDelay(pdMS_TO_TICKS(3000));}
}
//创建任务每间隔300ms控制MQ2模块读取烟雾浓度
void MQ2Task(void *MQ2)
{
	while(1) {vTaskSuspendAll();
						value=MQ2_GetData();
						PPM=MQ2_GetData_PPM();
						xTaskResumeAll();	
	#if MODE		
						if(value>600) USART_Printf("注意燃气，烟雾\n"),mq2wron=1;else mq2wron=0;//烟雾浓度异常
	#else
						if(MQ2_GetData()!=0) USART_Printf("注意燃气，烟雾\n"),mq2wron=1;else mq2wron=0;//烟雾浓度异常
	#endif	
						vTaskDelay(pdMS_TO_TICKS(300));}
}
//创建任务每间隔300ms控制火焰传感器模块检测明火
void FlameTask(void *Flame)
{
	while(1) {if(GPIO_ReadInputDataBit(GPIOA,PA11)==0) USART_Printf("注意火灾\n"),flamewron=1;else flamewron=0;//检测到明火
		        vTaskDelay(pdMS_TO_TICKS(300));}
}
//创建任务传感器检测到异常值则蜂鸣器间隔500ms响500ms
void BuzzerTask(void *Buzzer)
{
	while(1){if(warn&&wron) GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_RESET),vTaskDelay(pdMS_TO_TICKS(500)),GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET),vTaskDelay(pdMS_TO_TICKS(500));
		       else        		GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);}
}
//创建任务每间隔10ms查询按键键值改变标志位
void KEYTask(void *KEY)
{
while(1) {if(GPIO_ReadInputDataBit(KEY1_Port,KEY1_Pin)==1){vTaskDelay(pdMS_TO_TICKS(100));if(GPIO_ReadInputDataBit(KEY1_Port,KEY1_Pin)==1)ble=1;}
					else if(GPIO_ReadInputDataBit(KEY2_Port,KEY2_Pin)==1){vTaskDelay(pdMS_TO_TICKS(100));if(GPIO_ReadInputDataBit(KEY2_Port,KEY2_Pin)==1)ble=2;}
					else if(GPIO_ReadInputDataBit(KEY3_Port,KEY3_Pin)==1){vTaskDelay(pdMS_TO_TICKS(100));if(GPIO_ReadInputDataBit(KEY3_Port,KEY3_Pin)==1)ble=3;}
					else if(GPIO_ReadInputDataBit(KEY4_Port,KEY4_Pin)==1){vTaskDelay(pdMS_TO_TICKS(100));if(GPIO_ReadInputDataBit(KEY4_Port,KEY4_Pin)==1)ble=4;}
					vTaskDelay(pdMS_TO_TICKS(10));}
}
//创建任务控制OLED休眠
void OLEDSleepTask(void *sleep)
{
	while(1){if(Menu<7){vTaskDelay(pdMS_TO_TICKS(1000));count++;if(count==sleeptime)Menu=7,count=0;}}
}

int main(void)
{
OLED_Init();														//OLED初始化
KEY_SET();															//按键初始化
MQ2_Init();															//MQ-2初始化
TIM2_NVIC_Configuration();							//TIM2定时器实现us级延时（DHT11时基）
Ble_Init();															//蓝牙模块初始化
//gpioinit(GPIOA,PA5,GPIO_Mode_Out_PP);		//初始化LED引脚
//gpioinit(GPIOA,PA6,GPIO_Mode_Out_PP);
gpioinit(GPIOA,PA12,GPIO_Mode_Out_OD);		//初始化蜂鸣器引脚
gpioinit(GPIOA,PA11,GPIO_Mode_IN_FLOATING);			// 初始化火焰传感器引脚
GPIO_WriteBit(GPIOA,GPIO_Pin_12,Bit_SET);//关闭蜂鸣器（低电平触发）
OLED_Page1();
delay_s(2);
OLED_Clear();

//调用各任务并启动任务调度
	xTaskCreate(DHT11Task,"DHT11",256,NULL,2,&DHT11TaskHandler);
	xTaskCreate(OLEDTask,"OLED",512,NULL,1,&OLEDTaskHandler);
	xTaskCreate(OLEDSleepTask,"OLEDSleep",256,NULL,1,NULL);
	xTaskCreate(BleTask,"Ble",256,NULL,3,&BleTaskHandler);
	xTaskCreate(USARTTask,"USART",256,NULL,3,&BleTaskHandler);
	xTaskCreate(MQ2Task,"MQ2",256,NULL,1,&MQ2TaskHandler);
	xTaskCreate(FlameTask,"Flame",256,NULL,2,NULL);
	xTaskCreate(KEYTask,"Key",256,NULL,3,NULL);
	xTaskCreate(BuzzerTask,"Buzzer",256,NULL,1,NULL);
	vTaskStartScheduler();

}
//火焰传感器 PA0
