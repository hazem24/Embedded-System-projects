/*
 * adc.c
 *
 *  Created on: Jun 7, 2019
 *      Author: LENOVO
 */


#include "adc.h"



/*
 * init ADC.
 */

void ADC_init(ADC_Configuration *adc)
{
	/*
	 * Define ADC channel as input.
	 * ADMUX.
	 	 * REFS1:0 are used to choose the reference voltage.
	 * ADCSRA.
	 	 * ADEN Enable ADC Module.
	 	 * ADSC ADC Start Conversion.
	 	 * ADIF ADC Interrupt Enable.
	 	 * ADPS2:0 ADC Prescaler Select Bits.
	 * ADCL - ADCH .. read converted data.
	 */

	ADMUX   = ( (adc->vref) << 6 );
	ADCSRA |= ( 1 << ADEN ) | (PRESCALER);
#ifdef INTERRUPT
	//Enable Interrupt.
	ADCSRA |= ( 1 << ADIE);
#endif

}

/*
 * return uint16 because ADC in AVR 10-bit resolution.
 */
#ifndef INTERRUPT
uint16 ADC_readChannel(ADC_Channel channel)
{

	/*
	 * ADCSRA.
	 	 * ADSC ADC Start Conversion.
	 * ADCL - ADCH .. read converted data.
	 * ADMUX
	 	 * MUX4:0 Choose channel.
	 */
	CLEAR_BIT(ADC_DDR, channel);
	ADMUX |= channel;
	SET_BIT(ADCSRA, ADSC);
	//Polling.
	while(BIT_IS_CLEAR(ADCSRA, ADIF));
	SET_BIT(ADCSRA, ADIF);//Clear Flag.
	return ADC;
}
#endif

#ifdef INTERRUPT
void ADC_readChannel(ADC_Channel channel)
{

	/*
	 * ADCSRA.
	 	 * ADSC ADC Start Conversion.
	 * ADCL - ADCH .. read converted data.
	 * ADMUX
	 	 * MUX4:0 Choose channel.
	 */
	CLEAR_BIT(ADC_DDR, channel);
	ADMUX |= channel;
	SET_BIT(ADCSRA, ADSC);
}
#endif

#ifdef INTERRUPT
ISR(ADC_vect)
{
	ADC_Value = ADC;
}
#endif
