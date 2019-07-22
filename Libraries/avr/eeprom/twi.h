/*
 * twi.h
 *
 *  Created on: Jun 19, 2019
 *      Author: LENOVO
 */

#ifndef TWI_H_
#define TWI_H_

#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"
#include "twi.h"
#include "lcd.h"
/*
* TWBR_REG  -> it selects the division factor to control SCL frequency in master mode.
* TWPS from bit 1 .. 0 -> TWI Prescaler Bits .. these bits can be read and written, and control the bit rate.--init--.
	* 0 0 -> 1.
	* 0 1 -> 4.
	* 1 0 -> 16.
	* 1 1 -> 64.
* Frequency equation = (F_CPU/ (16 + (2 ( TWBR ) * 4 ^ (TWPS)))
 */
#define TWBR_VALUE 2
#define TWPS_VALUE 0


/*
 * MODE == 1
 	 * Master Mode.
 * MODE == 0
 	 * Slave Mode.
 */
#define MODE 1

/*
 * Set Address of this device i case of ..
 	 * Master be addressed to be slave with other devices.
 	 * Slave addressed.
 */
#define DEVICE_ADDRESS 0x50


/*
 * Defining status that happen on the bus.
 */
#if MODE == 1
	/* Status Codes for Master Transmitter Mode. */
#define START_CONDITON 0x08
#define REPEATED_START 0x10
#define SLA_WRITE_ACK  0x18
#define SLA_WRITE_NACK 0x20
#define DATA_ACK       0x28
#define DATA_NACK      0x30
   /* Status Codes for Master Receiver Mode. */
#define SLA_READ_ACK   0x40
#define SLA_READ_NACK  0x48
#define DATA_READ_ACK  0x50
#define DATA_READ_NACK 0x58

#elif MODE == 0
	/* Status Codes for Slave Receiver Mode. */
#define SLA_WRITE_ACK  0x60
	/* Status Codes for Slave Transmitter Mode. */
#define SLA_READ_ACK   0xA8
#define DATA_ACK       0xB8
#define DATA_NACK      0xC0

#endif
/*
 * TWI initialization.
 */
void TWI_init();


/*
 * TWI start bit.
 */
void TWI_start();


/*
 * TWI repeated start.
 */
void TWI_repeatedStart();
/*
 * TWI stop bit.
 */
void TWI_stop();

/*
 * TWI write.
 */
void TWI_write( uint8 data );


/*
 * TWI_read_with_ack.
 */
uint8 TWI_read_with_ack();

/*
 * TWI_read_with_nack.
 */
uint8 TWI_read_with_nack();



/*
 * TWI get status.
 */
uint8 TWI_getStatus();
#endif /* TWI_H_ */
