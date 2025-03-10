#include"bluetooth.h"
#include"timer.h"
#include"delay.h"
#include"passkey.h"
void beep_relay_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;//设置PA3 浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_0;//RELAY 0   BEEP 1
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
  RELAY=0;
	BEEP=0;
}
void Usart1_Init(u32 bound)//已经修改
{
	GPIO_InitTypeDef GPIO_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;//设置PA3 浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;//设置PA2 复用推挽输出
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=3;
	NVIC_Init(&NVIC_InitStruct);
	
	USART_InitStruct.USART_BaudRate=bound;
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity=USART_Parity_No;
	USART_InitStruct.USART_StopBits=USART_StopBits_1;
	USART_InitStruct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruct);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_Cmd(USART1,ENABLE);
	USART_ClearFlag(USART1,USART_FLAG_RXNE);
}
u8 usart1_buf=16;
u8 uartdate_en=0;
u8 tempdatauart=16;
void USART1_IRQHandler(void)//已经修改
{ 
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
	{
		  tempdatauart=USART_ReceiveData(USART1);
		  if(tempdatauart==0xff)uartdate_en=1;
		  else {
				if(uartdate_en){usart1_buf=tempdatauart;uartdate_en=0;}
			}
	    
		  
      		
    	
	}
	USART_ClearITPendingBit(USART1,USART_IT_RXNE);
}




	
