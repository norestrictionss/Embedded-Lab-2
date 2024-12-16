#include <string.h>
#include <stdio.h>
#include "stm32l476xx.h"
#include "SysClock.h"
#include "I2C.h"
#include "ssd1306.h"
#include "ssd1306_tests.h"
#include "keypad.h"

// Note: The code gets Warning L6989W
// Report: this is an known issue for STM32L4xx.
// https://www.keil.com/support/docs/3853.htm
// We can ignore this warning because we are not using
// external memory.

uint8_t Data_Receive[6];
uint8_t Data_Send[6];


void I2C_GPIO_init(void);

// Function to initialize the buffer
void init_keypress_buffer(char *keypress_buffer, int BUFFER_SIZE) {
			for (int i = 0; i < BUFFER_SIZE; i++) {
					keypress_buffer[i] = ' '; // Fill buffer with spaces
			}
}
	
int main(void){
	volatile int i;
	int count = 0;
	
	int a = 0;
	int n = 0;
	char message[64] = "ABCDEFGHIJK";
	char chr;
	char str[64];
	// init_keypress_buffer(str, 64);
	
	unsigned char key = 0xF;
	unsigned char len = 0;
	unsigned char last = ' ';
	Keypad_Pin_Init(); // Keypad initialization
	System_Clock_Init(); // Switch System Clock = 80 MHz
	I2C_GPIO_init();
	I2C_Initialization(I2C1);

	//ssd1306_TestAll();
	ssd1306_Init();
	ssd1306_Fill(White);
	ssd1306_SetCursor(2,0);
	
	ssd1306_WriteString(str, Font_11x18, Black);		
	ssd1306_UpdateScreen();

	
	
	// while(1);	 // Deadloop
	
	while(1){
		ssd1306_Fill(White);
		// GPIOC->IDR&= ~(0x1c10);
		// GPIOC->IDR |= 0x1c10;
		// GPIOC->ODR &= ~(0x0000000F);
		key = keypad_scan();
		while((GPIOC->IDR & 0x1c10)!=0x1c10);		
		for(int i = 0;i<1000000;i++);
		if(last!=key || last=='*'){
			switch(key){
				
				case '*':
					if(len>0){
						len--;
						str[len] = 0;
						
					}
					break;
				
				case '#':
					break;
				
				case 0xFF:
					break;
				
				default:
					
					//str[0] = key;
					str[len] = key;
					str[len+1] = 0;
					len++;
					if(len>=48) len = 0;
			}
			
			last = key;
			for(int i = 0;i<1000000;i++);			
		}
		
		ssd1306_WriteString(str, Font_11x18, Black);		
		ssd1306_UpdateScreen();
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2,0);
		for(int i = 0;i<10000;i++);			
	}
	
	
}

