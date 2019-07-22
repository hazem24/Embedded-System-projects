/*
 * three_freq_portc.c
 *
 *  Created on: Apr 10, 2019
 *      Author: LENOVO
 */


/*
 * led_brighness.c
 *
 *  Created on: Apr 10, 2019
 *      Author: LENOVO
 */


#define F_CPU 1000000
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void timer_init0();
unsigned char counter = 0;
int main( void )
{

	/* App Init. */
	DDRB = DDRB | ( 1 << PB3 );//Output.
	PORTB |= ( 1 << PC0 ) | ( 1 << PC1 ) | ( 1 << PC2 );//Output.
	GICR |= (1 << INT0);
	timer_init0();
	sei();
	while( 1 )
	{
	}
}

void timer_init0(  )
{

	TCCR0 |= (1<<FOC0) | ( 1 << WGM01 ) | ( 1 << CS00 );
	TCNT0 = 0;
	OCR0  = 56;// 200 Counting.
	TIMSK |= (1	<< OCIE0 );//Module Interrupt Enable.
}


ISR(TIMER0_COMP_vect)
{
	PORTC++;
}
