/*
 * mani.c
 *
 *  Created on: Jun 6, 2019
 *      Author: LENOVO
 */

#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "lcd.h"
#include "icu.h"

uint8 count = 0;
uint16 duty;

uint16 t1;
uint16 t2;
uint16 t3;
void dutyCycle(uint16 captureValue)
{
	if ( count == 0  )
	{
		ICU_clearTimer();
		ICU_edgeSelection(FALLING);
		count++;
	}else if ( count == 1 )
	{
		t1 = captureValue;
		ICU_edgeSelection(RAISING);
		count++;
	}else if ( count == 2 )
	{
		t2 = captureValue;
		ICU_edgeSelection(FALLING);
		count++;
	}else if (count == 3)
	{
		t3 = captureValue;
		count++;
	}
}
int main()
{
	/*
	 * init.
	 */
	LCD_init();
	ICU_init();
	ICU_edgeSelection(RAISING);
	ICU_callBack( dutyCycle );
	/*
	 * App.
	 */
	sei();
	while( True )
	{
		if (count == 4)
		{

			/* Disable the Input Capture interrupt */
			TIMSK &= ~(1<<TICIE1);

			count = 0;
			duty = 1000000/(t3 - t1);
			LCD_integerToString(duty);
		}
	}
}

