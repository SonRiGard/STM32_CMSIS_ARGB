#include "stm32f0xx.h"

void DMA_config (void);
void Set_LED (uint8_t LEDnum, uint8_t Red, uint8_t Green, uint8_t Blue);
void WS2812_Send (void);
void test_red (void);
void eff (uint8_t red , uint8_t green , uint8_t blu);
uint8_t rainbow_effect_right(void);
void color_change (uint8_t r, uint8_t g, uint8_t b,uint8_t numb_high);
