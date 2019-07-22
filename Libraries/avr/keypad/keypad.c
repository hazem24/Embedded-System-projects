/*
 * keypad.c
 *
 *  Created on: Jun 5, 2019
 *      Author: LENOVO
 */

#include "keypad.h"

#if KEY_PAD_COLUMNS == 4
static uint8 KEY_PAD_CONSTRUCTION[KEY_PAD_ROWS][4] =
{
		{1,2,3,'A'},
		{4,5,6,'B'},
		{7,8,9,'C'},
		{'*',0,'#','D'}
};
#elif KEY_PAD_COLUMNS == 3
static uint8 KEY_PAD_CONSTRUCTION[KEY_PAD_ROWS][3] =
{
		{1,2,3},
		{4,5,6},
		{7,8,9},
		{'*',0,'#'}
};
#endif
/*
 * Init module.
 */

static uint8 getLetter(uint8,uint8);
void KEYPAD_Init()
{
	/*
	 * Init pins.
	 	 * Rows Pins as output.
	 	 * Columns Pins as input.
	 */
	KEYPAD_ROWS_DDR |=  0b00001111;
	KEYPAD_ROWS_PORT |= 0b00001111;
#if KEY_PAD_COLUMNS == 4
	//Input.
	KEYPAD_COLUMNS_DDR = KEYPAD_COLUMNS_DDR & 0b11110000;
	//Pull-Up Resistor.
	KEYPAD_COLUMNS_PORT = KEYPAD_COLUMNS_PORT | 0b00001111;
#elif KEY_PAD_COLUMNS == 3
	//Input.
	KEYPAD_COLUMNS_DDR  = KEYPAD_COLUMNS_DDR & 0b11111000;
	//Pull-Up Resistor.
	KEYPAD_COLUMNS_PORT = KEYPAD_COLUMNS_PORT | 0b00000111;
#else
	#error "Please Choose Number of columns 3 or 4 only"
#endif

	//Ground all rows.
	KEYPAD_ROWS_PORT = KEYPAD_ROWS_PORT & 0xF0;
}
/*
 * Function used to get key which pressed.
 */
uint8 KEYPAD_getPressedKey()
{
#if KEY_PAD_COLUMNS == 3
	uint8 mask = 7;
#elif KEY_PAD_COLUMNS == 4
	uint8 mask = 15;
#endif
	uint8 row = 0,col = 0;
	while( True )
	{

		if ((KEYPAD_COLUMNS_PIN & mask) != mask)
		{
			/*
			 * Key Is pressed.
			 * Delay 20 ms to ensure this pressed from user not spikes error.
			 * and prevent multiply interp.
			*/
			_delay_ms(20);
			for( row = 0;row < KEY_PAD_ROWS; row++  )
			{
				//Make this row to be grounded and make all the other high impedence.
				KEYPAD_ROWS_PORT = 0x0F;
				CLEAR_BIT(KEYPAD_ROWS_PORT, row);
				for( col = 0;col < KEY_PAD_COLUMNS; col++ )
				{
					if(BIT_IS_CLEAR(KEYPAD_COLUMNS_PIN, col))
					{
						//get letter.
						return getLetter( row, col );
					}
				}
			}
		}else
		{
			//Ground all output pins.
			KEYPAD_ROWS_PORT &= 0xF0;
		}

	}
}

static uint8 getLetter(uint8 row_number, uint8 column_number)
{
	return KEY_PAD_CONSTRUCTION[row_number][column_number];
}
