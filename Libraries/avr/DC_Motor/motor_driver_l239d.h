/*
 * motor_driver_l239d.h
 *
 *  Created on: Jul 16, 2019
 *      Author: LENOVO
 */

#ifndef MOTOR_DRIVER_L239D_H_
#define MOTOR_DRIVER_L239D_H_

#include "data_type.h"
#include "micro_config.h"
#include "common_macros.h"
#include "pwm.h"

#define MOTOR_DDR  DDRB
#define MOTOR_PORT PORTB
#define INPUT1 PB1
#define INPUT2 PB2
#define ENABLE_1 PB3

typedef enum
{
	STOP,CLOCK_WISE,ANTI_CLOCK_WISE
}MOTOR_DRIVER_L239D_Direction;



/*
 * MOTOR_init.
 */
void MOTOR_init();

/*
 * MOTOR_start
 */
void MOTOR_start(MOTOR_DRIVER_L239D_Direction direction);

/*
 * MOTOR stop.
 */
void MOTOR_stop();

/*
 * MOTOR changeSpeed
 */
void MOTOR_changeSpeed(uint8 duty);

/*
 * Motor reverse.
 */
void MOTOR_reverseDirection();
#endif /* MOTOR_DRIVER_L239D_H_ */
