#include"spi.h"
#include"delay.h"
void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );//PORTB时钟使能 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_SPI1,  ENABLE );//SPI2时钟使能 	
	RCC_APB2PeriphClockCmd(	RCC_APB2ENR_AFIOEN,  ENABLE );
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
  GPIO_PinRemapConfig(GPIO_Remap_SPI1,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PB13/14/15复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOB
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 ;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOB
 	GPIO_ResetBits(GPIOB,GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5);  //PB13/14/15上拉
	GPIO_SetBits(GPIOA,GPIO_Pin_8);
  
	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;  //设置SPI单向或者双向的数据模式:SPI设置为双线双向全双工
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;		//设置SPI工作模式:设置为主SPI
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;		//设置SPI的数据大小:SPI发送接收8位帧结构
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;		//串行同步时钟的空闲状态为高电平
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;	//串行同步时钟的第二个跳变沿（上升或下降）数据被采样
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;		//NSS信号由硬件（NSS管脚）还是软件（使用SSI位）管理:内部NSS信号有SSI位控制
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;		//定义波特率预分频的值:波特率预分频值为256
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;	//指定数据传输从MSB位还是LSB位开始:数据传输从MSB位开始
	SPI_InitStructure.SPI_CRCPolynomial = 7;	//CRC值计算的多项式

	SPI_Init(SPI1, &SPI_InitStructure);  //根据SPI_InitStruct中指定的参数初始化外设SPIx寄存器
 
	SPI_Cmd(SPI1, ENABLE); //使能SPI外设
     
	
	//启动传输	
}
uint8_t SPI1SendByte(uint8_t data) {
	
	u8 retry=0;
	while((SPI1->SR&SPI_I2S_FLAG_TXE)==RESET)
	{
		retry++;
		if(retry>200)return 0;
	}
	SPI1->DR=data;
	retry=0;
	while((SPI1->SR&SPI_I2S_FLAG_RXNE)==RESET)
	{
		retry++;
	  if(retry>200)return 0;
	}
	return SPI1->DR;
}
