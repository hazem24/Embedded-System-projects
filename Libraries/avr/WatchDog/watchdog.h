/*
 * watchdog.h
 *
 *  Created on: Jul 20, 2019
 *      Author: LENOVO
 */

#ifndef WATCHDOG_H_
#define WATCHDOG_H_

#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"


typedef enum
{
	_16_3,_32_5,_65_,_0_13,_0_26,_0_52,_1_,_2_1
}WATCHDOG_Timer;

/*
 * watchDog Enable.
 */
void WATCHDOG_enable(WATCHDOG_Timer timer);


/*
 * watchDog disabled.
 */
void WATCHDOG_disable();
#endif /* WATCHDOG_H_ */
