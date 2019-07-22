/*
 * watchdog.c
 *
 *  Created on: Jul 20, 2019
 *      Author: LENOVO
 */


#include "watchdog.h"
/*
 * watchDog Enable.
 */
void WATCHDOG_enable(WATCHDOG_Timer timer)
{
	/*
	 * MCUCSR.--DONE--.
	 	 * WDRF -> watch dog reset .. reset by POWER-ON reset or writing a logic zero to it.
	 * WDTCR.--DONE--.
	 	 * WDTOE -> watch dog turn-off Enable .. this bit sets only when WDE bit written to logic 0.
	 	 * WDE   -> watch dog enable .. enable watch dog timer.
	 	 	 * 0 => Disable.
	 	 	 * 1 => Enable.
	 */
	WDTCR = timer | ( 1 << WDE );
}


/*
 * watchDog disabled.
 */
void WATCHDOG_disable()
{
	/*
	 * To disable watch dog timer.--DONE--.
	 	 * First write logic 1 to WDTOE and WDE in the same operation.
	 	 * Then write in the next four cycles .. write a logic 0 to WDE.
	 */
	WDTCR = ( 1 << WDTOE ) | ( 1 << WDE );
	//_delay_us((4 * (1/F_CPU)));
	WDTCR = 0x00;
}
