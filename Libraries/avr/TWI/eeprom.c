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
	uint8 most_address_bit = (((( address ) & 0x700) >> 7));
	TWI_write( CONTROL_CODE | most_address_bit );

	if (TWI_getStatus() == SLA_WRITE_ACK)
	{
		/* Write Address (8-LSB) */
		TWI_write( address );
		if (TWI_getStatus() == SLA_WRITE_ACK)
		{
			TWI_write( data );
		}
	}
	TWI_stop();
}

/*
 * EEPROM readData
 */
void EEPROM_readData( uint16 address , uint8* data)
{
	TWI_start();
	/*
	 * 1010(A10)(A9)(A8)(1)
	 */
	uint8 most_address_bit = (((( address ) & 0x700) >> 7));
	data = False;
	TWI_write( CONTROL_CODE | most_address_bit | 1 );

	if (TWI_getStatus() == SLA_WRITE_ACK)
	{
		/* Write Address (8-LSB) */
		TWI_write( address );
		if (TWI_getStatus() == SLA_READ_ACK)
		{
			*data = TWI_read_with_ack();
		}
	}
	TWI_stop();
}
