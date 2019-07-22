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

int main()
{
	/*
	 * init.
	 */
	LCD_init();
	LCD_displayString("Hello 4-bit Mode !");
	/*
	 * App.
	 */
	while( True )
	{

	}
}

