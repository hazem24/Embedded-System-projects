/*
 * eeprom.h
 *
 *  Created on: Jun 19, 2019
 *      Author: LENOVO
 */

#ifndef EEPROM_H_
#define EEPROM_H_


#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"
#include "twi.h"

#define CONTROL_CODE 0xA0

/*
 * EEPROM init.
 */
void EEPROM_init();

/*
 * EEPROM writeData.
 */
void EEPROM_writeData( uint8 data, uint16 address );

/*
 * EEPROM readData
 */
void EEPROM_readData( uint16 address , uint8* data);


#endif /* EEPROM_H_ */
