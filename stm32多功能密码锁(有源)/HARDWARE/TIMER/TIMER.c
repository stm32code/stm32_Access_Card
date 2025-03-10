#include"timer.h"
#include"delay.h"
#include"usart.h"
#include"bluetooth.h"

#include"passkey.h"

void TIM2_base_Init(u16 arr,u16 psc)//已经修改
{

	 TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	 TIM_ICInitTypeDef TIM_ICInitStruct;
	 NVIC_InitTypeDef NVIC_InitStruct;
	 RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
	 TIM_TimeBaseInitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	 TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	 TIM_TimeBaseInitStruct.TIM_Period=arr;
	 TIM_TimeBaseInitStruct.TIM_Prescaler=psc;
	 TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStruct);
	 
	 TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	 NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
	 NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
   NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
   NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;	 
	 NVIC_Init(&NVIC_InitStruct);
	 TIM_Cmd(TIM2,ENABLE);
}
u32 timout=0;
u16 as608_timeout=0;
void TIM2_IRQHandler(void)//已经修改
{
   if((TIM2->SR&TIM_IT_Update)!=RESET)//更新中断点
	 {
	//	   if(beepflag){BEEP=!BEEP;count++;}
	//		 if(USART_RX_STA==0)as608_timeout++;
		   count++;
			 timout++;
			 if(timout==500)
       {timout=0;
				 if(RELAY!=0){while((USART1->SR&0x40)==0);USART1->DR=0xdd;}
				 else {while((USART1->SR&0x40)==0);USART1->DR=0xaa;}
			 
			  }
	 }
	 TIM2->SR=~TIM_IT_Update;
	 
}


	
  

