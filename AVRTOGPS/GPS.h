/*
 * GPS.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#ifndef GPS_H_
#define GPS_H_



#include"uart.h"

unit8 GPS_SERVICE_NAME(const unit8* postion,unit8* SERVICE_NAME);
void GPS_SERVICE_UTC(const unit8* postion,unit8* UTC);
void UART_receiveString_Postion(unit8 *Str);
void UTC_SPLIT_HMS(unit8* UTC,unit8* HOUR,unit8* Min,unit8* Sec);



#endif /* GPS_H_ */
