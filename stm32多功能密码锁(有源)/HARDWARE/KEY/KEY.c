#include"key.h"
#include"sys.h"
#include"delay.h"
void KEY_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStructure.GPIO_Pin = 0x3C0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;						//������������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =0xf0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;				//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);

}




/**************************************************************************
���� KEY_Init2 ���ܣ�������IO������ʽ�ķ�ת��
��ʼ�����ƾ�����̵� GPIOB �ڣ�9��5~7 Ϊ���������12~15 Ϊ������������
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
u16 KEY_SCAN(void)//�������ɨ��
{
	u16 keyvalue=16; //����ֵ
	u16 buf1=0, buf2=0;//��ʱ����
	KEY_Init2();//������ʼ�� 0xf0 ����ж�������ֵ�Ӷ��ж���һ��
  GPIOA->BRR=0xf0;
	GPIOB->BSRR=0x3C0;
	if( (GPIOB->IDR&0x3C0)!=0x3C0)//�а�������
	{
		if( (GPIOB->IDR&0x3C0)!=0x3C0)//���Ƕ���ȷʵ����
		{
			buf1 = GPIOB->IDR&0x3C0;//��ȡio�ڵ�ƽ
			switch(buf1)//�ж���  ��ֵkeyvalue
			{
				case 0x380:keyvalue=0;break;
				case 0x340:keyvalue=1;break;
				case 0x2C0:keyvalue=2;break;
				case 0x1C0:keyvalue=3;break;
			}
			KEY_Init();									//��ʼ�������0x0f�Ӷ��ж���
		  GPIOB->BRR=0x3C0;
			GPIOA->BSRR=0xf0;
			delay_ms(3);
			buf2 = GPIOA->IDR&0xf0;
			switch(buf2)
			{
				case 0x70: keyvalue=keyvalue+12;		break;			//'+'  1��
				case 0xb0: keyvalue=keyvalue+8;	 		break;			//'-'2��
				case 0xd0: keyvalue=keyvalue+4; 		break;			//'*' ������
				case 0xe0: keyvalue=keyvalue; 		break;			//'/'
				
			}
			while(( GPIOA->IDR&0xf0) == buf2 );//��ⰴ���Ƿ��ɿ�
		}			
	}

	return keyvalue;//���ذ���ֵ  ��-����  �ϵ���  ��0-15
}




