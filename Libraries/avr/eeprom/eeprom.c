/*
 * eeprom.c
 *
 *  Created on: Jun 19, 2019
 *      Author: LENOVO
 */

/* Hazem EEPROM Have Sequ. mode (Burst mode) which can successfully impl. */

#include "eeprom.h"

/*
 * EEPROM init.
 */
void EEPROM_init()
{
	TWI_init();
}

/*
 * EEPROM writeData.
 */
void EEPROM_writeData( uint8 data, uint16 address )
{
	TWI_start();
		/*
		 * 1010(A10)(A9)(A8)(0)
		 */
		uint8 most_address_bit = (( (address  & 0x0700) >> 7));
		TWI_write( (uint8)(CONTROL_CODE | most_address_bit ));
		/* Write Address (8-LSB) */
		TWI_write( (uint8)address );
		TWI_write( data );
	TWI_stop();
}

/*
 * EEPROM readData
 */
void EEPROM_readData( uint16 address , uint8* data )
{
	TWI_start();
	/*
	 * 1010(A10)(A9)(A8)(1)
	 */
		uint8 most_address_bit = (( (address  & 0x0700) >> 7));
		*data = False;
		TWI_write( (uint8)(CONTROL_CODE | most_address_bit));
		/* Write Address (8-LSB) */
		TWI_write( (uint8)address );
		TWI_start();
		TWI_write((uint8)((0xA0) | ((address & 0x0700) >> 7) | 1));
		*data = TWI_read_with_nack();
	TWI_stop();
}
