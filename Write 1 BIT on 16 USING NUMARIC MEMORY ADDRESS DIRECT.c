
/* CREATED 15-10-2025

BY ENG: MOHAMED AMIN AFIFY*/


#include <stdio.h>
#include <stdint.h>

// FOR TESTING CODE IN C
uint32_t G_GPIO_ODR_variable = 0;                       // THOSE THE 2 LINES
#define GPIO_ODR  &G_GPIO_ODR_variable                   // U WILL COMMENT EM


// WHAEN U USE IT FOR MICROCONTROLLER U WILL REMOVE COMMENT HERE AND COMMENT THE 2 LINES UP

//#define gpio_odr 0x48000404


void main()
{

	// USING NUMARIC MEMORY ADDRESS DIRECT

	*(( volatile uint32_t *) GPIO_ODR ) |= 1UL << 14 ;
	printf("G_GPIO_ODR_variable = 0x%X", G_GPIO_ODR_variable);
}
