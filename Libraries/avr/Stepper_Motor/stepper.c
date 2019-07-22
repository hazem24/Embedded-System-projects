/*
 * stepper.c
 *
 *  Created on: Jul 18, 2019
 *      Author: LENOVO
 */

#include "stepper.h"


static uint8 full_mode[4] = { 0x0C, 0x06, 0x03, 0x09};
static uint8 half_mode[8] = {0x0C,0x04,0x06,0x02,0x03,0x01,0x09,0x08};
static uint8 lastPos = 0;
/*
 * STEPPER init.
 */
void STEPPER_init()
{
	STEPPER_DDR |= ( 1 << INPUT1 ) | ( 1 << INPUT2 ) | ( 1 << INPUT3 ) | ( 1 << INPUT4 );
}


/*
 * STEPPER_start
 */
void STEPPER_start(uint8 pos)
{
	if ( pos > 0 && pos <= 3 )
	{
		STEPPER_PORT = (STEPPER_PORT & 0xF0) | full_mode[pos];
		lastPos = pos;
	}
}
/*
 * STEPPER newStep.
 */
void STEPPER_newStep(STEPPER_StepMode mode, STEPPER_Direction direction)
{
	if (direction == STEPPER_CLOCK_WISE)
	{
		lastPos++;
		if ( mode == FULL_MODE && lastPos > 3 )  lastPos = 0;
		if ( mode == HALF_MODE && lastPos > 7  ) lastPos = 0;
	}else if ( direction == STEPPER_ANTI_CLOCK_WISE )
	{
		lastPos--;
		if (  mode == FULL_MODE && lastPos < 0) lastPos = 3;
		if (  mode == HALF_MODE && lastPos < 0) lastPos = 7;
	}
	if ( mode ==  FULL_MODE)
	{
		if ( lastPos <= 3) STEPPER_PORT = (STEPPER_PORT & 0xF0) | (full_mode[lastPos]);
	}else if ( mode == HALF_MODE )
	{
		if ( lastPos <= 7 ) STEPPER_PORT = (STEPPER_PORT & 0xF0) | half_mode[lastPos];
	}
}

/*
 * STEPPER stop.
 */
void STEPPER_stop()
{
	STEPPER_PORT &= 0xF0;
}

/*
 * STEPPER changeSpeed (Step/Sec).
 */
void STEPPER_changeSpeed(uint8 delay)
{
	_delay_ms(delay);
}
