/*
 * twi.c
 *
 *  Created on: Jun 19, 2019
 *      Author: LENOVO
 */

#include "twi.h"


void TWI_init()
{
	/*
	 * TWBR -> it selects the division factor to control SCL frequency in master mode.--init--.--DONE--.
	 	 * Equation SCL Frequency = (CPU CLOCK / (16 + 2 ( TWBR )) * 4 ^ (TWPS)).
	 * TWCR -> TWI Control Register.
	 	 * TWINT -> This bit is set by hardware when the TWI has finished it's current job .. ( Cleared By set logic one to it).
	  	 * TWEA  -> enable ACK pulse.--init--.--DONE--.
	  	 * TWSTA -> TWI Start Condition bit.--DONE--.
	  	 * TWSTO -> Write one to this bit in Master Mode will generate stop bit.--DONE--.
	  	 * TWEN  -> TWI Enable Bit.--init--.--DONE--.
	 * TWSR -> TWI Status Register.
	 	 * TWI Status from bit 7 .. 3 -> these five bits reflect the status of the TWI logic and the Two-wire serial bus.
	 	 	 * NOTE : 2-bit prescaler value must be Masked to get the status of the bus.
	 	 * TWPS from bit 1 .. 0 -> TWI Prescaler Bits .. these bits can be read and written, and control the bit rate.--init--.--DONE--.
	 	 	 * 0 0 -> 1.
	 	 	 * 0 1 -> 4.
	 	 	 * 1 0 -> 16.
	 	 	 * 1 1 -> 64.
	 * TWDR -> In transmit mode, TWDR contains the next byte to be transmitted, in receive mode, the TWDR contains the last byte received.
	 * TWAR.
	 	 *bit from 7 .. 1  -> Slave address register.--init--.--DONE--.
	 */
#if MODE == 1
	TWBR  = TWBR_VALUE;
	TWSR |= TWPS_VALUE;
#endif
	TWAR |= ( DEVICE_ADDRESS << 1);
	TWCR  = ( 1 << TWEN );
}

/*
 * TWI start bit.
 */
void TWI_start()
{
	/*
	 * TWCR -> TWI Control Register.
	 	 * TWSTA -> TWI Start Condition bit.--DONE--.
	 */
	TWCR |= ( 1 << TWSTA ) | ( 1 << TWEN );
}


/*
 * TWI repeated start.
 */
void TWI_repeatedStart()
{
	TWCR |= ( 1 << TWSTA );
}
/*
 * TWI stop bit.
 */
void TWI_stop()
{
	/*
	 * TWCR -> TWI Control Register.
	 	 * TWSTO -> Write one to this bit in Master Mode will generate stop bit.--DONE--.
	 */
	TWCR |= ( 1 << TWSTO) | ( 1 << TWINT );
}

/*
 * TWI write.
 */
void TWI_write( uint8 data )
{
	/*
	 * TWDR -> In transmit mode, TWDR contains the next byte to be transmitted, in receive mode, the TWDR contains the last byte received.--DONE--.
	 * TWCR -> TWI Control Register.
	 	 * TWINT -> This bit is set by hardware when the TWI has finished it's current job .. ( Cleared By set logic one to it).--DONE--.
	 * I can check here for an error.
	 */
    /* Put data On TWI data Register */
    TWDR = data;
    /*
	 * Clear the TWINT flag before sending the data TWINT=1
	 * Enable TWI Module TWEN=1
	 */
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register(data is send successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
}


/*
 * TWI_read_with_ack.
 */
uint8 TWI_read_with_ack()
{
	TWCR  |= ( 1 << TWEA );
	while(!(TWCR & (~(1 << TWINT))));
	TWCR |= ( 1 << TWINT);
	return TWDR;
}

/*
 * TWI_read_with_nack.
 */
uint8 TWI_read_with_nack()
{
    TWCR = (1 << TWINT) | (1 << TWEN);
    /* Wait for TWINT flag set in TWCR Register (data received successfully) */
    while(BIT_IS_CLEAR(TWCR,TWINT));
    /* Read Data */
    return TWDR;
}



/*
 * TWI get status.
 */
uint8 TWI_getStatus()
{
	/*
	 * TWSR -> TWI Status Register.
	 	 * TWI Status from bit 7 .. 3 -> these five bits reflect the status of the TWI logic and the Two-wire serial bus.
	 */
	/*LCD_integerToString(TWSR & 0xF8);
	LCD_displayCharacter('-');*/
	return TWSR & 0xF8;

}
