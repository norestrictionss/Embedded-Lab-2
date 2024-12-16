
#include "stm32l476xx.h"
// PA.5 <--> Green LED
// PC.13 <--> Blue user button
#define LED_PIN 5
#define BUTTON_PIN 13

// User HSI (high-speed internal) as the processor clock
void enable_HSI(){
	// Enable High Speed Internal Clock (HSI = 16 MHz)
	RCC->CR |= ((uint32_t)RCC_CR_HSION);
	// wait until HSI is ready
	while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	// Select HSI as system clock source
	RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
	RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI; //01: HSI16 oscillator used as system clock
	// Wait till HSI is used as system clock source
	while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
}

unsigned char keypad_scan(void);

void Keypad_Pin_Init(){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	GPIOC->MODER &= ~(0x000000FF); 
	GPIOC->MODER |= (0x00000055); // Pin 0, 1, 2, 3 adjusted as output mode
	GPIOC->MODER &= ~(0x03f00300); // Pin 12, 11, 10, 4 adjusted as input mode
	
	// GPIOC->ODR &= ~(0x0000000F); // Pin 0, 1, 2, 3 configured as output
	// GPIOC->ODR |= (0x0000000F);
	
	// GPIOC->IDR &= ~(0x00001C10);
	// GPIOC->IDR |= ~(0x00001C10); // Pin 12, 11, 10, 4 configured as input
	
	GPIOC->PUPDR &= ~(0x03f00300); //
	
	GPIOC->OTYPER &= ~(0x0000000F); // Open-drain mode for output
	GPIOC->OTYPER |= (0x0000000F);
	
	
	
}