/*
 * master.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */





#include"GPS.h"
#include"LCD.h"


int main(void){


	unit8 postion[68],GPGGA[5],True=0,UTC[10],HOUR[2],Min[2],Sec[2];



	LCD_init();

	UART_init();



	// unit8* ch="$GPGGA,054355.000,0029.8450,N,00031.3275,W,1,6,1.25,84.0,M,-2.2,M,,*74";
     unit8 ch;

    DDRD|=0x80;
    PORTD=(1<<6);





	while(1){
		/*ch=UART_recieveByte();
		LCD_displayChar(ch);*/

		UART_receiveString_Postion(postion);


        True=GPS_SERVICE_NAME(postion,GPGGA);

       if(True){
        LCD_displayStrRowCol(0,0,GPGGA);
        GPS_SERVICE_UTC(postion,UTC);
        LCD_displayStrRowCol(1,0,UTC);
      //  UTC_SPLIT_HMS(UTC,HOUR,Min,Sec);
           }



        /*LCD_displayStrRowCol(1,0,HOUR);
        LCD_displayStrRowCol(1,2,":");
        LCD_displayStrRowCol(1,3,Min);
        LCD_displayStrRowCol(1,5,":");
        LCD_displayStrRowCol(1,6,Sec);*/
















	}


	return 0;
}
