/*
 * challenge2.c
 *
 *  Created on: Mar 29, 2019
 *      Author: LENOVO
 */


#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int number = 0;
int main()
{
	/* Intializing App. */
	DDRC = DDRC | (1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3);// Ouput -> 1.
	//Interrupt Switch.


	//Interrupt Pin.
	GICR = GICR | ( 1 << INT2);
	MCUCSR = MCUCSR | (1<<ISC2);


	sei();//SFR (I-BIT).

	while(1)
	{
		//Do Nothing.

	}

}


ISR(INT2_vect)
{

	if ( number >= 9 ) number = 0;
	else number++;
	PORTC = (number & 15);
}


