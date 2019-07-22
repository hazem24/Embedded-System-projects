/*
 * main.c
 *
 *  Created on: Jun 5, 2019
 *      Author: LENOVO
 */


#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"
#include "keypad.h"



int main()
{
	/*
	 * Init.
	 */
	KEYPAD_Init();

	DDRC = 0b01111111;

	uint8 key;
	/*
	 * App.
	 */
	while(True)
	{
		key   = KEYPAD_getPressedKey();
		PORTC = 1 << key;
	}
}
