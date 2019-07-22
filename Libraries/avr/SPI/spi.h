/*
 * spi.h
 *
 *  Created on: Jun 11, 2019
 *      Author: LENOVO
 */

#ifndef SPI_H_
#define SPI_H_


#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"

/*
 * Option for Mode directive.
 	 * MASTER For Master Mode.
 	 * SLAVE  For Slave Mode.
 */
#define MODE MASTER

/*
 * SPI PINS.
 */
#define SPI_DDR  DDRB
#define SPI_PORT PORTB

#define SPI_SS   PB4
#define SPI_MOSI PB5
#define SPI_MISO PB6
#define SPI_CLK  PB7


/*
 * Clock freq.
 * Note : Clock freq. of master must be less than or equal Slave freq.
 */
#if MODE == MATER
/*
 * 0 -> F_CPU/4
 * 1 -> F_CPU/16
 * 2 -> F_CPU/64
 * 3 -> F_CPU/128
 */
#define SCK_FREQUENCE 1
#endif
/*
 * SPI init.
 */
void SPI_init();

/*
 * SPI send Byte Logic.
 */
void SPI_sendByte( uint8 byte );

/*
 * SPI receive byte.
 */
uint8 SPI_receiveByte();

/*
 * SPI receive String.
 */
void SPI_receiveString(uint8* string);
#endif /* SPI_H_ */
