/*
 * main.c
 *
 *  Created on: Jul 2, 2019
 *      Author: LENOVO
 */


#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"


uint8 counter = 0;
int main()
{
	/*
	 * Init.
	 */
	//OC0 as output.
	DDRC  |= 0x7F;
	PORTC  = 0;
	TCCR0  = ( 1 << CS00 ) | ( 1 << CS02 ) | ( 1 << FOC0 );
	/*
	 * App.
	 */
	while( True )
	{
		while( !(TIFR & ( ~( 1 << TOV0 ) )) );
		TIFR |= (1 << TOV0);//Clear Flag.
		counter++;
		//PORTD = 0x02;
		if ( counter >= 122 )
		{
			PORTC++;
			if ( PORTC > 9 ) PORTC = 0;
			counter = 0;
		}
		TCNT0 = 0;
	}
}
