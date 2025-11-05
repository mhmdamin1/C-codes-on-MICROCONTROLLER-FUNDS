/**
 * \file
 * Created by mohamed amiin
 */
#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#define SET_BIT(ADDRESS, BIT) ADRESS |= (1<<BIT)
#define RESET_BIT(ADDRESS, BIT) ADRESS &= ~(1<<BIT)
#define TOGGLE_BIT(ADDRESS, BIT) ADRESS ^= (1<<BIT)
#define READ_BIT(ADDRESS, BIT) ((ADRESS & (1<<BIT))>>BIT)
/* MCUCR
Table 35. Interrupt 0 Sense Control ISC01 ISC00 Description 
Bit 1, 0 – ISC01, ISC00: Interrupt Sense Control 0 Bit 1 and Bit 0
0 0 The low level of INT0 generates an interrupt request.
0 1 Any logical change on INT0 generates an interrupt request.
1 0 The falling edge of INT0 generates an interrupt request.
1 1 The rising edge of INT0 generates an interrupt request.
*/

/* MCUCR
Bit 3, 2 – ISC11, ISC10: Interrupt Sense Control 1 Bit 1 and Bit 0
Table 34. Interrupt 1 Sense Control ISC11 ISC10 Description 
0 0 The low level of INT1 generates an interrupt request.
0 1 Any logical change on INT1 generates an interrupt request.
1 0 The falling edge of INT1 generates an interrupt request.
1 1 The rising edge of INT1 generates an interrupt request.
*/

/* MCUCSR
Bit 6 – ISC2: Interrupt Sense Control 2
*/

/*GICR
Bit 7 – INT1: External Interrupt Request 1 Enable
Bit 6 – INT0: External Interrupt Request 0 Enable
Bit 5 – INT2: External Interrupt Request 2 Enable
*/
int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */

	board_init();
	// INT0 any logical
	SET_BIT(MCUCR, 0);
	RESET_BIT(MCUCR,1);
	//MCUCR |= 1<<0;

	// INT1 rising edge
	SET_BIT(MCUCR, 2);
	SET_BIT(MCUCR, 3);
	//MCUCR |= (0b11<<2);

	// INT2 falling edge
	MCUCSR &= ~(1<<6);
	
	GICR |= (0b111<<5);   //SET_BIT(GICR,5);
                          //SET_BIT(GISC,6):
	                      //SET_BIT(GICR,7);
	
	// enable SREG
	sei();
	DDRD |= (0b111<<5);   //SET_BIT(DDRD,5);
                          //SET_BIT(DDRD,6):
	                      //SET_BIT(DDRD,7);

	while(1){
		PORTD &= ~(1<<5);
		PORTD &= ~(1<<6);
		PORTD &= ~(1<<7);
		_delay_ms(500);
	}
	/* Insert application code here, after the board has been initialized. */
}

ISR(INT0_vect){
	PORTD |= (1<<5);
	_delay_ms(500);
}
ISR(INT1_vect){
	PORTD |= (1<<6);
	_delay_ms(500);
}
ISR(INT2_vect){
	PORTD |= (1<<7);
	_delay_ms(500);
}
