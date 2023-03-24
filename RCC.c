#include "RCC.h"

void RCC_config (void)
{
	RCC->CR |= RCC_CR_HSION;
	while(!(RCC->CR & RCC_CR_HSIRDY));     //wait still HSE ready
	
	FLASH->ACR = FLASH_ACR_PRFTBE | FLASH_ACR_LATENCY; // Clock Flash memory
	
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;//AHB = SYSCLK
	RCC->CFGR |= RCC_CFGR_PPRE_DIV1;//APB1 = AHB
	RCC->CFGR |= RCC_CFGR_MCO_SYSCLK; //System clock (SYSCLK) selected for Clock OUTPUT
	
	RCC->CFGR &= ~RCC_CFGR_PLLMUL_Msk;  //Clear PLLBIL bits
	RCC->CFGR &= ~RCC_CFGR_PLLSRC;   //Clear PLLSRC bit
	RCC->APB2ENR |= RCC_APB2ENR_DBGMCUEN;//ENABLE CLOCK DEBUG
	
	RCC->CFGR |= RCC_CFGR_PLLMUL12; // PLL x12: clock = 4 MHz * 12 = 48 MHz
	
	RCC->CR |= RCC_CR_PLLON; //PLL on
	while((RCC->CR & RCC_CR_PLLRDY)==0); // wait till PLL ready
	
	RCC->CFGR &= ~RCC_CFGR_SW; //clear SW bits
	RCC->CFGR |= RCC_CFGR_SW_PLL; //PLL selected as system clock
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_1);		// wait till PLL is used	
	
}
