#ifndef _BLUETOOTH_H
#define _BLUETOOTH_H
#include"sys.h"
#define BEEP PBout(1)
#define RELAY PBout(0)
void Usart1_Init(u32 bound);
extern u8 usart1_buf,RXD_DATA_EN;
extern u8 usart1_buf;
void beep_relay_init(void);
#endif

