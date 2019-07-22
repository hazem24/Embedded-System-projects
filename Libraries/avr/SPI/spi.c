/*
 * spi.c
 *
 *  Created on: Jun 11, 2019
 *      Author: LENOVO
 */


#include "spi.h"

/*
 * SPI init.
 */
void SPI_init()
{

	/*
	 * SPCR.
	 	 * SPE   -> SPI Enable.--init--.
	 	 * MSTR  -> 1/0 Select .. if this bit = 1 (1 Mode).--init--.
	 	 * CPOL  -> Clock Polarity.--init--.
	 	 * CPHA  -> Clock Phase.--init--.
	 	 * SPR1,SPR0 BIT1:0 SPI Clock Rate Select.--init--.
	 * SPSR.
	 	 * SPIF -> Set equal one whenever a serial transfer is complete .. cleared by set logic one on it.
	 * SPDR.
	 	 * SPI  -> data register is an 8-bit read/write register.
	 */
	SPCR = 1 << SPE & (~(1 << CPOL)) & (~(1 << CPHA));
#if MODE == 1
	/*
	 * Ports.
	 */
	SPI_DDR = 0xB0;
	SPCR |= 1 << MSTR | SCK_FREQUENCE;
#elif MODE == 0
	SPI_DDR = 0x40;
	CLEAR_BIT(SPCR, MSTR);
#endif
}

/*
 * SPI send Byte Logic.
 */
void SPI_sendByte( uint8 byte )
{
	/*
	 * To send Byte.
	 	 * SS = 0.
	 	 * writing then send data.
	 	 * SS = 1 To finish process.
	 * SPSR.
	 	 * SPIF -> Set equal one whenever a serial transfer is complete .. cleared by set logic one on it.
	 * SPDR.
	 	 * SPI  -> data register is an 8-bit read/write register.
	 */
#if MODE == 1
	CLEAR_BIT(SPI_PORT, SPI_SS);
#endif
	SPDR = byte;
	while( BIT_IS_CLEAR(SPSR, SPIF) );
#if MODE == 1
	SET_BIT(SPI_PORT, SPI_SS);
#endif
}

/*
 * SPI receive byte.
 */
uint8 SPI_receiveByte()
{
	while( BIT_IS_CLEAR(SPSR, SPIF) );
	return SPDR;
}
/*
 * SPI sendString.
 */
void SPI_sendString(uint8* string)
{
	uint8 i = 0;
	while( string[i] != '\0')
	{
		SPI_sendByte(string[i]);
	}
}

/*
 * SPI receive String.
 */
void SPI_receiveString(uint8* string)
{
	uint8 i;

	string[i] = SPI_receiveByte();
	while( string[i] != '#' )
	{
		i++;
		string[i] = SPI_receiveByte();
	}
	string[i] = '\0';
}
