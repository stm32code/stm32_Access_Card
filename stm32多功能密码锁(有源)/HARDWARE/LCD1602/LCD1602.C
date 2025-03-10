#include"lcd1602.h"
#include"delay.h"
void CheckLcdBusy()
{
    LCD_RW=1;
    delay_us(10);
    LCD_RS=0;
    delay_us(10);
    LCD_EN=0;
    delay_us(10);
    LCD_P7_IN();
    do
    {
        delay_us(2);
        LCD_EN=1;
        delay_us(2);
        LCD_EN=0;
    }
    while(LCD_READ_P7);
    LCD_P7_OUT();
}

void WriteLcdData(u8 Temp)
{
    u8 i;
	  CheckLcdBusy();
    LCD_RS=1;
	//  delay_us(1);
    LCD_RW=0;
	 // delay_us(1);
	  LCD_EN=0;
	//  delay_us(1);
//	    LCD_P7=1;
//	LCD_P6=1;
//	LCD_P5=1;
//	LCD_P4=1;
//	 delay_us(1);
    for(i=0; i<2; i++)
    {
       
        if(Temp&0x80)LCD_P7=1;
        else LCD_P7=0;
        if(Temp&0x40)LCD_P6=1;
        else LCD_P6=0;
        if(Temp&0x20)LCD_P5=1;
        else LCD_P5=0;
        if(Temp&0x10)LCD_P4=1;
        else LCD_P4=0;
			  delay_ms(1);
			  LCD_EN=1;
        delay_ms(1);
        LCD_EN=0;
        Temp=(Temp<<4);
			//  delay_ms(1);
        
    }
    
}
void WriteLcdCmd(u8 cmd)
{
    u8 i;
	  CheckLcdBusy();
    LCD_RS=0;
    LCD_RW=0;
	  LCD_EN=0;
    for(i=0; i<2; i++)
    {
       
        if(cmd&0x80)LCD_P7=1;
        else LCD_P7=0;
        if(cmd&0x40)LCD_P6=1;
        else LCD_P6=0;
        if(cmd&0x20)LCD_P5=1;
        else LCD_P5=0;
        if(cmd&0x10)LCD_P4=1;
        else LCD_P4=0;
			  delay_ms(1);
			  LCD_EN=1;
        delay_ms(1);
        LCD_EN=0;
        cmd=(cmd<<4);
    }
    
		
}

void Init1602(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=0XF000;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_11;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_11);
	GPIO_SetBits(GPIOB,0XF000);
  WriteLcdCmd(0x32);	 //将8位总线转为4位总线
	WriteLcdCmd(0x28);	 //在四位线下的初始化
	WriteLcdCmd(0x0c);  //开显示不显示光标
	WriteLcdCmd(0x06);  //写一个指针加1
	WriteLcdCmd(0x01);  //清屏
	//WriteLcdCmd(0x80);  //设置数据指针起点
//    WriteLcdCmd(0x01);//清屏
//    WriteLcdCmd(0x28);//设置4位操作，1行显示，5x8
//    WriteLcdCmd(0x02);//光标归位
//    WriteLcdCmd(0x06);//AC自动加1，画面不动
//    WriteLcdCmd(0x0f);//0x0f:光标闪烁开；
}
/*
parameter:
  x:1-16
  y:1-2
  val:显示字符
*/
void DisplayCharAt(u8 x,u8 y,u8 val)
{
	 u8 pos;
   if(y==1)pos=0x80+x-1;
	 else pos=0xc0+x-1;
	 WriteLcdCmd(pos);
	 WriteLcdData(val);
}
void DisplayString(u8 x,u8 y,u8 *str)
{
	u8 pos;
	if(y==1)pos=0x80+x-1;
	else pos=0xc0+x-1;
	WriteLcdCmd(pos);
  while(*str!=0)
	{
		WriteLcdData(*str);
		str++;
	}
}

u32 mypow(u8 m,u8 n)
{
	 long result=1;
	 while(n--)result*=m;
	 return result;
}

void shownum(u8 x,u8 y,u32 num,u8 len)
{
	 u8 i,temp,enshow=0,m=0,pos;
	 if(y==1)pos=0x80+x-1;
	 else pos=0xc0+x-1;
	 WriteLcdCmd(pos);
	 for(i=len;i>0;i--)
	 {
		  temp=num/mypow(10,i-1)%10;
		 
		  if(temp!=0)
			{
				enshow=1;
				temp+='0';
			}
		  else
			{  m++;
				 if(enshow)temp+='0';
				 else 
				 {
					 if(m!=len)temp+=' ';
					 else temp+='0';
				 }
			}
		  
		  WriteLcdData(temp);
	 }
}

void LCD1602_ShowHex(u8 x,u8 y,u32 num,u8 len)
{
	 u8 i,temp,enshow=0,m=0,pos;
		 if(y==1)pos=0x80+x-1;
	 else pos=0xc0+x-1;
	 WriteLcdCmd(pos);
	 for(i=len;i>0;i--)
	 {
		  temp=num/mypow(16,i-1)%16;
		 
//		  if(temp!=0)//去掉多余0
//			{
//				enshow=1;
//				if(temp<=9)temp+='0';
//				else temp+='7';
//			}
//		  else
//			{  m++;
//				 if(enshow)temp+='0';
//				 else 
//				 {
//					 if(m!=len)temp+=' ';
//					 else temp+='0';
//				 }
//			}
		  
		  if(temp<=9)temp+='0';
				else temp+='7';
		  WriteLcdData(temp);
	 }

}

