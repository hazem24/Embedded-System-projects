/*
 * adc.h
 *
 *  Created on: Jun 7, 2019
 *      Author: LENOVO
 */

#ifndef ADC_H_
#define ADC_H_

#include "common_macros.h"
#include "data_type.h"
#include "micro_config.h"

#define ADC_DDR DDRA
/*
 * Comment #define INTERRUPT if you want to use POLLING type.
 */
//#define INTERRUPT

/*
 * This global variable have the value of ADC after converion by interrupt.
 */
#ifdef INTERRUPT
uint16 ADC_Value;
#endif
/*
 * Choose Prescaler from.
 	 * 0 = F_CPU/2
 	 * 1 = F_CPU/2
 	 * 2 = F_CPU/4
 	 * 3 = F_CPU/8
 	 * 4 = F_CPU/16
 	 * 5 = F_CPU/32
 	 * 6 = F_CPU/64
 	 * 7 = F_CPU/128
 * Note : ADC Must work at frequency less than or equal 200KHZ.
 */
#define PRESCALER 8
/*
 * This enum have all analog input channels in avr.
 */
typedef enum
{
	ADC0,ADC1,ADC2,ADC3,ADC4,ADC5,ADC6,ADC7
}ADC_Channel;

/*
 * Vref.
 */
typedef enum
{
	AREF,AVCC,INTERNAL = 3
}ADC_VoltageReference;

typedef struct
{
	ADC_VoltageReference vref;
}ADC_Configuration;


/*
 * init ADC.
 */

void ADC_init(ADC_Configuration *adc);

/*
 * return uint16 because ADC in AVR 10-bit resolution.
 */
#ifndef INTERRUPT
uint16 ADC_readChannel(ADC_Channel channel);
#endif

#ifdef INTERRUPT
void ADC_readChannel(ADC_Channel channel);
#endif

#ifdef INTERRUPT
ISR(ADC_vect)
{
	ADC_Value = ADC;
}
#endif
#endif /* ADC_H_ */
