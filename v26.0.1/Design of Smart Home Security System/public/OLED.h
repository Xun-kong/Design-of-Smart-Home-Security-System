#include "stm32f10x.h"
#ifndef __OLED_H
#define __OLED_H
//OLED_Page1(void);加载页面1
/**************************************************************************************************************************************************

OLED_WriteData(uint8_t Data)----------------------------------------------向OLED屏幕写入16进制数据Data（如0xff）
OLED_Init(void)-----------------------------------------------------------OLED屏幕初始化
OLED_SetCursor(uint8_t X, uint8_t Page)-----------------------------------设置显示坐标X（横坐标，取值0～127），Page（纵坐标，取值0～7）
OLED_Clear(void)----------------------------------------------------------清屏
OLED_ShowChar(uint8_t X, uint8_t Page, char Char, uint8_t FontSize)-------显示字符（横坐标X,纵坐标Page,字符 '' ,字号FontSize取值6或8）
OLED_ShowString(uint8_t X, uint8_t Page, char *String, uint8_t FontSize)--显示字符串（横坐标X,纵坐标Page,字符串 " " ,字号FontSize取值6或8）
OLED_ShowImage(uint8_t X, uint8_t Page, uint8_t Width, uint8_t Height, const uint8_t *Image);--显示图片（横坐标X,纵坐标Page,图宽Width取值0～127,图高Height取值0～7）
OLED_ShowChinese(uint8_t X, uint8_t Page, char *Chinese);-----------------显示中文（横坐标X,纵坐标Page,中文 " "）

****************************************************************************************************************************************************/
void OLED_WriteCommand(uint8_t Command);
void OLED_WriteData(uint8_t Data);
void OLED_Init(void);
void OLED_SetCursor(uint8_t X, uint8_t Page);
void OLED_Clear(void);
void OLED_ShowChar(uint8_t X, uint8_t Page, char Char, uint8_t FontSize);
void OLED_ShowString(uint8_t X, uint8_t Page, char *String, uint8_t FontSize);
void OLED_ShowImage(uint8_t X, uint8_t Page, uint8_t Width, uint8_t Height, const uint8_t *Image);
void OLED_ShowChinese(uint8_t X, uint8_t Page, char *Chinese);
void OLED_ShowNum(u8 X,u8 Page,u8 Num,u8 FontSize);
void OLED_Page1(void);
void OLED_Page2(void);
void OLED_Page3(void);
void OLED_Page4(void);
void OLED(void);
#endif
