/*
 * icu.h
 *
 *  Created on: Jun 24, 2019
 *      Author: LENOVO
 */

#ifndef ICU_H_
#define ICU_H_

#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"

#define ICU_DDR DDRD
#define ICU_PIN PD6



typedef enum
{
	FALLING,RAISING
}ICU_edge;
/*
 * ICU init.
 */
void ICU_init();


/*
 * ICU activeInputCaptureNoise.
 */
void ICU_activeInputCaptureNoise();

/*
 * ICU edgeSelection.
 */
void ICU_edgeSelection( ICU_edge edge );

/*
 * ICU callBack.
 */
void ICU_callBack(void (*callback)(uint16));
void ICU_clearTimer();
#endif /* ICU_H_ */
