/*
 * main.c
 *
 *  Created on: Jun 7, 2019
 *      Author: LENOVO
 */

#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "adc.h"
#include "lcd.h"


int main()
{
	/*
	 * Init.
	 */
	LCD_init();
	ADC_Configuration config = {INTERNAL};
	ADC_init(&config);
	LCD_displayString("Temp = ");

	/*
	 * App.
	 */
	while( True )
	{
		LCD_goToRowColumn(1,8);
		LCD_integerToString((ADC_readChannel(ADC0)/4));
	}
}
