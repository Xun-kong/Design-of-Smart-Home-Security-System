#include "DHT11.h"
#include "gpioinit.h"
void DHT11_Set(void)//主机发送信号
{
	gpioinit(DHT11_Port,DHT11_Pin,GPIO_Mode_Out_PP);
	GPIO_SetBits(DHT11_Port,Bit_RESET);
	delay_ms(20);
	GPIO_SetBits(DHT11_Port,Bit_SET);
	delay_us(13);
}
uint8_t DHT11_Check(void)//检查DHT11返回信号
{
	DHT11_Mode(IN);//配置引脚为输入模式
	u8 retry=0;
	while(GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin)&&retry<100)//等待低电平结束
		{retry++;delay_us(1);}
	if(retry>=100)return 1;
	else retry=0;
	while(!GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin)&&retry<100)//等待高电平结束
		{retry++;delay_us(1);}
	if(retry>=100)return 1;
	else retry=0;
return 0;
}
void DHT11_Mode(GPIOMode_TypeDef Mode)//配置引脚模式
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = DHT11_Pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = Mode;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_Init(DHT11_Port, &GPIO_InitStructure); 
}

uint8_t DHT11_Read_Bit()//读取一个位
{
	u8 retry=0;
	while(GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin)&&retry<100)//等待低电平结束
		{retry++;delay_us(1);}

		 retry=0;
	while(!GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin)&&retry<100)//等待高电平结束
		{retry++;delay_us(1);}
		
		delay_us(40);
		if(GPIO_ReadInputDataBit(DHT11_Port,DHT11_Pin))return 1;
		else return 0;
}
uint8_t DHT11_Read_Byte()//读取一个字节
{
	u8 i,dat=0;
	for(i=0;i<8;i++)
	{
		dat<<=1;
		dat|=DHT11_Read_Bit();
	}return dat;

}
uint8_t DHT11_Read_Data(u8 *humi,u8*temp)//读取数据
{
u8 i,data[5];
	DHT11_Set();
	if(DHT11_Check()==0)
	{for(i=0;i<5;i++){data[i]=DHT11_Read_Byte();}
		if((data[0]+data[1]+data[2]+data[3])==data[4])
			*humi=data[0],*temp=data[2];
	}
	else return 1;
	return 0;
}
