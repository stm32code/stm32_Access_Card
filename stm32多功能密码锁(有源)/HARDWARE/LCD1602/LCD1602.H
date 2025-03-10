#ifndef _lcd1602_h

#define _lcd1602_h
#include"sys.h"
#define LCD_RS PAout(0)
#define LCD_RW PAout(1)
#define LCD_EN PAout(11)
#define LCD_P7 PBout(12)
#define LCD_P6 PBout(13)
#define LCD_P5 PBout(14)
#define LCD_P4 PBout(15)
#define LCD_P7_IN() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=0X00080000;}
#define LCD_P7_OUT() {GPIOB->CRH&=0XFFF0FFFF;GPIOB->CRH|=0X00030000;}
#define LCD_READ_P7 PBin(12)

void Init1602(void);
void DisplayCharAt(u8 x,u8 y,u8 val);
void DisplayString(u8 x,u8 y,u8 *str);
void shownum(u8 x,u8 y,u32 num,u8 len);
void LCD1602_ShowHex(u8 x,u8 y,u32 num,u8 len);
void WriteLcdCmd(u8 cmd);
#endif




