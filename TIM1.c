#include "TIM1.h"

void GPIO_TIM1_config (void)
{
//	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
//	GPIOA->AFR[1] |= 0x2 << ((9-8)*4);
	
	//PA9 TIM1_CH2  Alternate function push-pull
//	GPIOA->MODER &= ~GPIO_MODER_MODER9;
//	GPIOA->MODER |= GPIO_MODER_MODER9_1;
//	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_9;
//	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR9;
//	GPIOA->PUPDR &= ~GPIO_PUPDR_PUPDR9;
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; /* (1) */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (2) */
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9))
	| (GPIO_MODER_MODER9_1); /* (3) */
	GPIOA->AFR[1] |= 0x2 << ((9-8)*4); /* (4) */
	
	TIM1->CR1 &= ~TIM_CR1_CKD;//CLOCK DIVISION 1
	TIM1->CR1 |= TIM_CR1_ARPE;// TIMx_ARR register is buffered
	//TIM1->CR1 &= ~TIM_CR1_ARPE;// TIMx_ARR register is not buffered
	TIM1->CR1 &= ~TIM_CR1_CMS ;// Edge-aligned mode. The counter counts up or down depending on the direction bit(DIR).
	TIM1->CR1 &= ~TIM_CR1_DIR;//COUTER MODE UP
	TIM1->CR1 |= TIM_CR1_UDIS;
	TIM1->CR1 &= ~TIM_CR1_OPM; //Counter is not stopped at update event
	
	TIM1->PSC = 0;
	TIM1->ARR = 59;//59;//60-1
	//TIM1->CCR2 = 30;
	
	TIM1->CR1 &= ~TIM_CR1_UDIS;
	TIM1->EGR |= TIM_EGR_UG;
	
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 ;// 110 -> PWM mode 1'
	TIM1->CCMR1 |= TIM_CCMR1_OC2PE;  //Output Compare 1 preload enable
	

	//RepetitionCounter=0
	
	
	//TIM1->CR2 &= ~TIM_CR2_MMS;//TRGO : RESET
	//TIM_MASTERSLAVEMODE_DISABLE
	//TIM1->CCER &= ~TIM_CCER_CC2E; // DIsNABLE COMPARE 2  OUTPUT ENABLE
	//TIM1->CCMR1 |= TIM_CCMR1_CC2S; //CC1 channel is configured as output
	TIM1->CCER &= ~TIM_CCER_CC2P; //OC1 active high
	
	//TIM1->CCMR1 &= ~TIM_CCMR1_OC2FE;//Output Compare 1 fast enable
	TIM1->CCER |= TIM_CCER_CC2E; // ENABLE COMPARE 2  OUTPUT ENABLE
	
	//TIM1->CR2 &= ~TIM_CR2_OIS2;// /*!< Output Idle state: OCx=0 when MOE=0 */
	
	TIM1->BDTR |= TIM_BDTR_MOE;//Main output enable
	//TIM1->BDTR |= TIM_BDTR_AOE;//Automatic output enable
	//NVIC_EnableIRQ(TIM1_CC_IRQn);//Interrupt compare enable
	TIM1->CR1 |= TIM_CR1_CEN;//COUNTER ENABLE
}

void OPM_config (void)
{
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; /* (1) */
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN; /* (2) */
	GPIOA->MODER = (GPIOA->MODER & ~(GPIO_MODER_MODER9))
	| (GPIO_MODER_MODER9_1); /* (3) */
	GPIOA->AFR[1] |= 0x2 << ((9-8)*4); /* (4) */
	
//	TIM1->PSC = 0;
//	//Map TI2FP2 to TI2 by writing CC2S=’01’ in the TIMx_CCMR1 register
//	TIM1->CCER &= ~TIM_CCER_CC2E; // DIsNABLE COMPARE 2  OUTPUT ENABLE
//	TIM1->CCER &= ~TIM_CCMR1_CC2S; // DIsNABLE COMPARE 2  OUTPUT ENABLE
//	TIM1->CCMR1 |= TIM_CCMR1_CC2S_0;
//	//TIM1->CCER |= TIM_CCER_CC2E; // ENABLE COMPARE 2  OUTPUT ENABLE
	TIM1->PSC = 0;
	TIM1->ARR = 59;//60-1
	TIM1->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_0
	| TIM_CCMR1_OC2PE;
	TIM1->CCER |= TIM_CCER_CC2E; /* (5) */
	TIM1->BDTR |= TIM_BDTR_MOE; /* (6) */
	TIM1->CR1 |= TIM_CR1_OPM | TIM_CR1_ARPE; /* (7) */
	TIM1->CR1 |= TIM_CR1_CEN;//COUNTER ENABLE
}

