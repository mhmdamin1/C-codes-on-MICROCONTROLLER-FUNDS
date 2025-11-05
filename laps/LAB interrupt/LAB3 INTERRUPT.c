/*
 * @file           : main.c for LAB 2 interrupt
 * created by mohamed amiin 
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

 #include "stdint.h"

typedef volatile unsigned int vuint32_t ;
//register address
//RCC
#define RCC_BASE	0x40021000
#define RCC_APB2ENR	*(volatile uint32_t *)(RCC_BASE + 0x18)
#define RCC_IOPAEN (1<<2)

//GPIO
#define GPIO_BASE	0x40010800
#define GPIO_CRH	*(volatile uint32_t *)(GPIO_BASE + 0x04)
#define GPIO_CRL	*(volatile uint32_t *)(GPIO_BASE + 0x00)
#define GPIO_ODR	*(volatile uint32_t *)(GPIO_BASE + 0x0C)
#define GPIOA13 (1UL<<13)

//EXTI
#define EXTI_BASE 0x40010400
#define EXTI_IMR	*(volatile uint32_t *)(EXTI_BASE + 0x00)
#define EXTI_RTSR	*(volatile uint32_t *)(EXTI_BASE + 0x08)
#define EXTI_PR	*(volatile uint32_t *)(EXTI_BASE + 0x14)

//AFIO
#define AFIO_BASE 0x40010000
#define AFIO_EXTIR1 *(volatile uint32_t *)(AFIO_BASE + 0x08)


//NVIC
#define NVIC_ISER0 *(volatile uint32_t *)(0xE000E100)

void clock_init()
{
	//enable GPIO clock
	RCC_APB2ENR |= RCC_IOPAEN ;
	//enable AFIO clock >> bit 0 AFIOEN
	RCC_APB2ENR |= (1<<0) ;
}

void GPIO_init()
{
	//make pin 13 in port A output
	GPIO_CRH &= 0xff0fffff ;
	GPIO_CRH |= 0x00200000 ;
	//to make pinA0 floating input
	GPIO_CRL |= (1<<2) ;
}

int main(void)
{
	clock_init();
	GPIO_init();
	//EXTI0 configuration (x=0) to portA0
	AFIO_EXTIR1 = 0;

	//enable interrupt mask
	EXTI_IMR |= (1<<0) ;

	//enable RTSR
	EXTI_RTSR |= (1<<0) ;

	//enable NVIC IRQ6 because EXTI0 is connected to IRQ6 in vector table
	NVIC_ISER0 |= (1<<6) ;

	while(1);

}

void EXTI0_IRQHandler(void)
{
	//IRQ happened which means EXTI0 >> portA pin 0 has rising edge _|-

	//toggle pin A 13
	GPIO_ODR ^= (1 << 13);
	//clear pending register to avoid interrupt overload
	EXTI_PR |= (1<<0);

}