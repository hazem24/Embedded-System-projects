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
	DDRD  =  1 << PD0;
	TCCR0 = (1 << CS00) | (1 << CS02) | ( 1 << FOC0 );
	/*
	 * App.
	 */
	while( True )
	{
		while( !(TIFR & ( ~( 1 << TOV0 ) )) );
		counter++;
		if ( counter == 2 )
		{
			TIFR |= (1 << TOV0);//Clear Flag.
			PORTD = PORTD ^ ( 1 << PD0 );
			counter = 0;
		}
	}
}
