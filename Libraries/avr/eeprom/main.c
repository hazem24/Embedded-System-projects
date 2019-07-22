/*
 * main.c
 *
 *  Created on: Jun 9, 2019
 *      Author: LENOVO
 */

#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"
#include "eeprom.h"
#include "lcd.h"

int main()
{
	/*
	 * Init.
	 */
	DDRA = 0xFF;

	EEPROM_init();
	//_delay_ms(100);

	EEPROM_writeData(100, 0x0AA);

	_delay_ms(10);

	uint8 data;

	EEPROM_readData(0x0AA, &data);


	LCD_init();
	LCD_integerToString(data);

	/*
	 * App.
	 */
	while( True )
	{

	}
}
