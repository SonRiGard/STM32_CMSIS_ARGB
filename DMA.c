#include "DMA.h"

#define  MAX_LED 30
extern uint32_t numbled;
extern uint8_t time;
static uint8_t LED_Data[MAX_LED][4];
uint16_t effStep = 0;
static uint16_t pwmData[(24*MAX_LED)+50];

void DMA_config (void)
{
	RCC->AHBENR |= RCC_AHBENR_DMA1EN;
	
	DMA1_Channel3->CCR |= DMA_CCR_MSIZE_0;//memory size 16-bit
	DMA1_Channel3->CCR |= DMA_CCR_PSIZE_0;//peripheral size 16-bit
	DMA1_Channel3->CCR &= ~DMA_CCR_PSIZE_1;
	
	DMA1_Channel3->CCR |= DMA_CCR_MINC;//Memory increment mode enabled
	DMA1_Channel3->CCR &= ~DMA_CCR_PINC;//0: Peripheral increment mode disabled
	
	DMA1_Channel3->CCR |= DMA_CCR_CIRC;//Circular mode enabled
	
	DMA1_Channel3->CCR |= DMA_CCR_DIR;//read from memory
	
	DMA1_Channel3->CNDTR = ((24*MAX_LED)+50);
	//note Phai ep kieu uint32_t cho (TIM1->CCR2)
	DMA1_Channel3->CPAR = (uint32_t)(&TIM1->CCR2);//addr of pheripheral
	DMA1_Channel3->CMAR = (uint32_t)pwmData;
	//DMA enable
	DMA1_Channel3->CCR |= DMA_CCR_EN;
	
	TIM1->DIER |= TIM_DIER_CC2DE;
}



void Set_LED (uint8_t LEDnum, uint8_t Red, uint8_t Green, uint8_t Blue)
{
	LED_Data[LEDnum][0] = LEDnum;
	LED_Data[LEDnum][1] = Green;
	LED_Data[LEDnum][2] = Red;
	LED_Data[LEDnum][3] = Blue;
}

void WS2812_Send (void)
{
	uint32_t indx=0;
	uint32_t color;


	for (int i= 0; i<MAX_LED; i++)
	{

		color = (((uint32_t)LED_Data[i][1]<<16) | ((uint32_t)LED_Data[i][2]<<8) | ((uint32_t)LED_Data[i][3]));

		for (int j=23; j>=0; j--)
		{
			if (color&(1<<j))
			{
				pwmData[indx] = 38;  // 2/3 of 60
			}

			else pwmData[indx] = 19;  // 1/3 of 60

			indx++;
		}

	}

	for (int i=0; i<50; i++)
	{
		pwmData[indx] = 0;
		indx++;
	}
	
}

void test_red (void)
{
	for (uint8_t i=0; i<MAX_LED; i++)
	{
	Set_LED(i, 255,255,255);
	}
}

uint8_t rainbow_effect_right(void) {
    // Strip ID: 0 - Effect: Rainbow - LEDS: 15
    // Steps: 133 - Delay: 20
    // Colors: 3 (255.0.0, 0.255.0, 0.0.255)
    // Options: rainbowlen=126, toLeft=true, 
  float factor1, factor2;
  uint16_t ind;
  for(uint16_t j=0;j<30;j++) {
    ind = effStep + j * 4.15625;
    switch((int)((ind % 133) / 44.333333333333336)) {
      case 0: factor1 = 1.0 - ((float)(ind % 133 - 0 * 44.333333333333336) / 44.333333333333336);
              factor2 = (float)((int)(ind - 0) % 133) / 44.333333333333336;
              Set_LED(j, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2);
							WS2812_Send();
              break;
      case 1: factor1 = 1.0 - ((float)(ind % 133 - 1 * 44.333333333333336) / 44.333333333333336);
              factor2 = (float)((int)(ind - 44.333333333333336) % 133) / 44.333333333333336;
              Set_LED(j, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2, 0 * factor1 + 255 * factor2);
							WS2812_Send();
              break;
      case 2: factor1 = 1.0 - ((float)(ind % 133 - 2 * 44.333333333333336) / 44.333333333333336);
              factor2 = (float)((int)(ind - 88.66666666666667) % 133) / 44.333333333333336;
              Set_LED(j, 0 * factor1 + 255 * factor2, 0 * factor1 + 0 * factor2, 255 * factor1 + 0 * factor2);
							WS2812_Send();
              break;
    }
  }
  if(effStep >= 133) {effStep=0; return 0x03; }
  else effStep++;
  return 0x01;
}


void color_change (uint8_t r, uint8_t g, uint8_t b,uint8_t numb_high)
{
	for (uint8_t i=0; i<numb_high; i++)
	{ 
	Set_LED(i, r,g,b);
	}
	for (uint8_t i=numb_high; i<MAX_LED; i++)
	{
	Set_LED(i,0,255,255);
	}
		uint32_t indx=0;
		uint32_t color;


		for (int i= 0; i<MAX_LED; i++)
		{

			color = (((uint32_t)LED_Data[i][1]<<16) | ((uint32_t)LED_Data[i][2]<<8) | ((uint32_t)LED_Data[i][3]));

			for (int j=23; j>=0; j--)
			{
				if (color&(1<<j))
				{
					pwmData[indx] = 38;  // 2/3 of 60
				}

				else pwmData[indx] = 19;  // 1/3 of 60

				indx++;
			}

		}

		for (int i=0; i<50; i++)
		{
			pwmData[indx] = 0;
			indx++;
		}
}
