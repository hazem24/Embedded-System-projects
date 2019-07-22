/*
 * icu.c
 *
 *  Created on: Jun 24, 2019
 *      Author: LENOVO
 */

#include "icu.h"

static void (*g_callBack)(uint16);


void ICU_init()
{
	/*
	 * Set pin as input.--init--.--DONE--.
	 * TCCR1A.
	 	 * Bit 7 .. 4 ( compare output mode ) set to zero to be in normal mode.
	 	 * bit 3 and 2 active in non-PWM mode.--init--.--DONE--.
	 	 * bit 1 and 0 set to 0 for normal mode.--init--.--DONE--.
	 * TCCR1B.
	 	 * ICNC1   -> input capture noise canceler.
	 	 * ICES1   -> input capture edge select .. 1 -> Raising .. 0 -> Falling.
	 	 * Bit 2:0 -> clock select at no prescaler set value to 1.--init--.--DONE--.
	 * TCNT1H and TCNT1L .. read directly from TCNT1.
	 * ICR1H  and ICR1L  .. Input capture is updated with the counter ( TCNT1 ) value each time and event occurs on ICP1 pin.
	 * TIMSK
	 	 * TICIE1 -> interrupt enable.--init--.--DONE--.
	 * TIFR.
	 	 * ICF1   -> input capture flag.
	 */
	ICU_DDR &= ~((1 << ICU_PIN));
	TCCR1A   = 0b00001100;
	TCCR1B   = 0x01;//No prescaler.
	TIMSK   |= ( 1 << TICIE1 );

}


/*
 * ICU activeInputCaptureNoise.
 */
void ICU_activeInputCaptureNoise()
{
	TCCR1B |= ( 1 << ICNC1 );
}

/*
 * ICU edgeSelection.
 */
void ICU_edgeSelection( ICU_edge edge )
{
	if ( edge == 0 )
		CLEAR_BIT( TCCR1B, ICES1 );
	else
		SET_BIT( TCCR1B,   ICES1 );
}

/*
 * ICU callBack.
 */
void ICU_callBack(void (*callback)(uint16))
{
	g_callBack = callback;
}


/*
 * ICU clearTimer.
 */
void ICU_clearTimer()
{
	TCNT1 =  0;
}


ISR ( TIMER1_CAPT_vect )
{
	(*( g_callBack ))(ICR1);
}
