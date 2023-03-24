#include "main.h"

uint16_t adc_val;
uint8_t numbled;
//uint16_t buf[4]={40,20,40,20};
int main(void){

	RCC_config();
	//uint8_t boo=0;
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//port A
	//GPIOA->MODER |= GPIO_MODER_MODER15_0;
	GPIOA->MODER |= 0x555555555;
	GPIOA->ODR |= 0xFFFF;
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	GPIOB->MODER |= 0x555555555;
	GPIOB->ODR |= 0xFF;
	RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
	GPIOF->MODER |= 0x555555555;
	GPIOF->ODR |= 0xFF;

	GPIOA->MODER &= ~GPIO_MODER_MODER8;//Alternate function
	GPIOA->MODER |= GPIO_MODER_MODER8_1;//Alternate function
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_8;//output PP
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR8;
	
	SysTick_Configuration();
	GPIO_TIM1_config();
	DMA_config();
	//test_red();
	//OPM_config();
	ADC_config();

	while(1){
		//rainbow_effect_right();
//		if (((ADC1->DR) > 1216) && ((ADC1->DR) < 1425)){
//		adc_val =	((ADC1->DR)-1216);
//	}
//	else{
//		if ((ADC1->DR) < 1216)	adc_val = 0 ;
//				else adc_val=209;
//			}
		
	
	numbled = (uint8_t) ((ADC1->DR)/140);
		color_change(255,0,0,numbled);
			
		//TIM1->CCR2 = (ADC1->DR);
		//TIM1->CR1 |= TIM_CR1_CEN;//COUNTER ENABLE
		
		//TIM1->CCR2 = 20;
//		if (boo == 0)
//		{
//		GPIOA->ODR |= GPIO_ODR_15;
//		boo=1;
//		}
//		else
//		{
//		GPIOA->ODR &= ~GPIO_ODR_15;
//			boo=0;
//		}
		  //Delay_Micro_SysTick(1000);
	}
}






