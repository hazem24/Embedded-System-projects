/*
 * App.c
 *
 *  Created on: Apr 17, 2019
 *      Author: LENOVO
 */

#define TRUE 1
#define F_CPU 1000000

#include <avr/io.h>
#include <avr/interrupt.h>

unsigned char tick = 0;

void initTimer0();
void incrementOneSec();
void resetTimer0();


int main( void )
{
	/* Initialization. */
	DDRC |= ( 1 << PC0 ) | ( 1 << PC1 ) | ( 1<<PC2 ) | ( 1 << PC3 );//Output.

	DDRA = 0b0111111;
	DDRD &= (~( 1 << PD2 ));//Input.
	PORTD |= ( 1 << PD2 );//Interrnal Pull Up Resistor.

	/* Initi. timer0. */
	initTimer0();
	/* Interrupt Button Which Reset Clock. */
	GICR |= ( 1 << INT0 );
	MCUCR |= ( 1 << ISC01 );


	sei();

	while(TRUE)
	{

		/* Code */
	}


}




void initTimer0()
{
	TCCR0 |= ( 1 << FOC0 ) | ( 1 << CS00 ) | ( 1 << CS02 );
	/* Interrupt For Timer0 Overflow. */
	TIMSK = ( 1 << TOIE0 );
	TCNT0 = 0;
}

void resetTimer0()
{
	TCCR0 = 0;
	initTimer0();

}
void incrementOneSec()
{
	tick++;
	if ( tick == 4 ) PORTC++;
}

ISR( INT0_vect )
{
	//Interrupt Happen Reset Clock.
	incrementOneSec();
}

ISR( TIMER0_OVF_vect )
{
	PORTC++;
}


