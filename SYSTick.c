#include "SYSTick.h"


void Delay_Mili_SysTick(uint32_t time)
	{
		uint32_t Timingdelay = time;
		while(Timingdelay!=0)
			{
				while( (SysTick->CTRL&0x10000)==0x10000)
					{
						Timingdelay--;
					}
			}
	}

	
void Delay_Micro_SysTick(uint16_t time)
	{
		uint32_t Timingdelay = time;
		while(Timingdelay!=0)
			{
				while( (SysTick->CTRL&0x10000)==0x10000)
					{
						Timingdelay--;
					}
			}
	}
	

void SysTick_Configuration(void)
	{
		SysTick->CTRL = 0x00000005;
		SysTick->VAL =0;
		SysTick->LOAD = 48000-1;	
}

void delay_us(uint32_t nus)
{
 uint32_t temp;
 SysTick->LOAD=nus*48;
 SysTick->VAL=0x00;
 SysTick->CTRL=0x01 ;
 do
 {
 temp=SysTick->CTRL;
 }
 while(temp&0x01&&!(temp&(1<<16)));
 SysTick->CTRL=0x00;
 SysTick->VAL =0X00;
}
