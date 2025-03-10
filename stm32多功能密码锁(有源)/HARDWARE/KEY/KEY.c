#include"key.h"
#include"sys.h"
#include"delay.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = 0x3C0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;						//上拉电阻输入
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =0xf0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

}




/**************************************************************************
函数 KEY_Init2 功能：（用于IO工作方式的翻转）
初始化控制矩阵键盘的 GPIOB 口，9、5~7 为推挽输出，12~15 为上拉电阻输入
**************************************************************************/
void KEY_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = 0x3C0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = 0xf0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
u16 KEY_SCAN(void)//矩阵键盘扫描
{
	u16 keyvalue=16; //按键值
	u16 buf1=0, buf2=0;//临时变量
	KEY_Init2();//按键初始化 0xf0 输出判定输入数值从而判定哪一行
  GPIOA->BRR=0xf0;
	GPIOB->BSRR=0x3C0;
	if( (GPIOB->IDR&0x3C0)!=0x3C0)//有按键按下
	{
		if( (GPIOB->IDR&0x3C0)!=0x3C0)//不是抖动确实按下
		{
			buf1 = GPIOB->IDR&0x3C0;//获取io口电平
			switch(buf1)//判定行  赋值keyvalue
			{
				case 0x380:keyvalue=0;break;
				case 0x340:keyvalue=1;break;
				case 0x2C0:keyvalue=2;break;
				case 0x1C0:keyvalue=3;break;
			}
			KEY_Init();									//初始引脚输出0x0f从而判定列
		  GPIOB->BRR=0x3C0;
			GPIOA->BSRR=0xf0;
			delay_ms(3);
			buf2 = GPIOA->IDR&0xf0;
			switch(buf2)
			{
				case 0x70: keyvalue=keyvalue+12;		break;			//'+'  1列
				case 0xb0: keyvalue=keyvalue+8;	 		break;			//'-'2列
				case 0xd0: keyvalue=keyvalue+4; 		break;			//'*' 。。。
				case 0xe0: keyvalue=keyvalue; 		break;			//'/'
				
			}
			while(( GPIOA->IDR&0xf0) == buf2 );//检测按键是否松开
		}			
	}

	return keyvalue;//返回按键值  左-》右  上到下  是0-15
}




