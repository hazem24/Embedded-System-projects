/*
 * stepper.h
 *
 *  Created on: Jul 18, 2019
 *      Author: LENOVO
 */

#ifndef STEPPER_H_
#define STEPPER_H_
/*
 * This Library for stepper motor UNI-POLAR with L239D driver.
 */
#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"


#define STEPPER_DDR  DDRB
#define STEPPER_PORT PORTB

#define INPUT1   PB0
#define INPUT2   PB1

#define INPUT3   PB2
#define INPUT4   PB3


/*
 * Modes of stepSeq.
 * Full Mode -> four step seq.
 * Half Mode -> 8    step seq.
 */
typedef enum
{
	FULL_MODE = 1,HALF_MODE = 2
}STEPPER_StepMode;


/*
 * Direction.
 */
typedef enum
{
	STEPPER_CLOCK_WISE = 1,STEPPER_ANTI_CLOCK_WISE = 2
}STEPPER_Direction;


/*
 * STEPPER init.
 */
void STEPPER_init();

/*
 * STEPPER_start
 */
void STEPPER_start(uint8 pos);
/*
 * STEPPER newStep.
 */
void STEPPER_newStep(STEPPER_StepMode mode, STEPPER_Direction direction);

/*
 * STEPPER stop.
 */
void STEPPER_stop();

/*
 * STEPPER changeSpeed (Step/Sec).
 */
void STEPPER_changeSpeed(uint8 delay);
#endif /* STEPPER_H_ */
