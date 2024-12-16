#include "stm32l476xx.h"

unsigned char key_map [4][4] = {
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'},
{'7', '8', '9', 'C'}, 
{'*', '0', '#', 'D'}, 
};

unsigned char keypad_scan(void){
	
	unsigned char row = 4, col, ColumnPressed;
	unsigned char key = 0xFF;
	
	// Check whether any key has been pressed.
	// 1. Output zeros on all row pins
	// 2. Delay shortly, and read inputs of column pins
	// 3. If inputs are 1 for all columns, then no key has been pressed.
	
	// If no key pressed, return 0xFF
	
	// Identify the column of the key pressed
	// Column scan
	
	GPIOC->ODR &= ~(0x0000000F);
	
	// for(int i = 0;i<1000;i++);
	
	int pc4 =1;
	int pc10 = 1;
	int pc11 = 1;
	int pc12 = 1;

	while(pc4 && pc10 && pc11 && pc12){
		pc4 = GPIOC->IDR & (1UL<<4);
		pc10 = GPIOC->IDR & (1UL<<10);
		pc11 = GPIOC->IDR & (1UL<<11);
		pc12 = GPIOC->IDR & (1UL<<12);
	}
		
	
	
	
	pc4 = pc4>>4;
	pc10 = pc10>>10;
	pc11 = pc11>>11;
	pc12 = pc12>>12;
	
	if(pc4==1 && pc10==1 && pc11==1 && pc12==1)
			return 0xFF;
	
	
	
	if(pc4==0) ColumnPressed = 0;
	else if(pc10==0) ColumnPressed = 1;
	else if(pc11==0) ColumnPressed = 2;
	else if(pc12==0) ColumnPressed = 3;
	
	/*
	int pc0 = GPIOC->ODR & (1UL<<0);
	int pc1 = GPIOC->ODR & (1UL<<1);
	int pc2 = GPIOC->ODR & (1UL<<2);
	int pc3 = GPIOC->ODR & (1UL<<3);
	

	
	pc0 = pc0>>0;
	pc1 = pc1>>1;
	pc2 = pc2>>2;
	pc3 = pc3>>3;
	
	// Identify the row of the column pressed
	
	if(pc0==0) key = key_map[0][ColumnPressed];
	else if(pc1==0) key = key_map[1][ColumnPressed];
	else if(pc2==0) key = key_map[2][ColumnPressed];
	else if(pc3==0) key = key_map[3][ColumnPressed];
	*/
	
	int binary_array[4] = {0b1110, 0b1101, 0b1011, 0b0111};

	for(int i = 0;i<row;i++){
			
		GPIOC->ODR = (GPIOC->ODR & ~0x0F) | binary_array[i];
		for(int i = 0;i<1000;i++);
		int result = 1;
		if(ColumnPressed ==0){
				result = GPIOC->IDR & (1UL<<4);
				result = result>>4;

		}
		
		else if(ColumnPressed ==1){
				result = GPIOC->IDR & (1UL<<10);
				result = result>>10;

		}
		
		else if(ColumnPressed ==2){
				result = GPIOC->IDR & (1UL<<11);
				result = result>>11;
		}
		else if(ColumnPressed ==3){
				result = GPIOC->IDR & (1UL<<12);
				result = result>>12;
		}
		
		if(result==0) key = key_map[i][ColumnPressed];
	}
	
	return key; 
	
}