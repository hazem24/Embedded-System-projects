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


int main()
{
	/*
	 * Init.
	 */
	EEPROM_init();

	EEPROM_writeData(0x08, 0xA1);



	uint8 data;

	EEPROM_readData(0xA1, &data);
	DDRA = 0xFF;
	PORTA = data;

	/*
	 * App.
	 */
	while( True )
	{

	}
}
