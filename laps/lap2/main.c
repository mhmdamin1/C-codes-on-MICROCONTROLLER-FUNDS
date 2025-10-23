//Mastering_Embedded System online diploma

typedef volatile unsigned int vuint32_t ;
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

// register address
#define RCC_BASE   0x40021000
#define RCC_CFGR  *(volatile uint32_t *)(RCC_BASE + 0x04)
#define RCC_CR  *(volatile uint32_t *)(RCC_BASE + 0x0)

void clock_init(){

	RCC_CFGR |= (0b10 << 0);

	RCC_CFGR |= (0b0110 << 18);

	RCC_CFGR |= (0b100 << 8);

	RCC_CFGR |= (0b101 << 11);

	RCC_CR |= (1 << 24);

}
int main(void){
	clock_init();
	 while(1){
	 }
}


