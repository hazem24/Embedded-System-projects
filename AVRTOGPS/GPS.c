/*
 * GPS.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Mohamed ELameer
 */

#include"uart.h"

void UART_receiveString_Postion(unit8 *Str)
{
	unit8 i = 0;

	Str[i] = UART_recieveByte();

	if(Str[i]=='$'){

	      while(Str[i]!= '*' )
	             {
	    	  i++;
	    	  Str[i] = UART_recieveByte();


	           }
	   }
Str[i]='\0';

}

unit8 GPS_SERVICE_NAME(const unit8* postion,unit8* SERVICE_NAME){

	unit8 i=0,flag=0;

	if ((postion[0]=='$') && (postion[1]=='G')  && (postion[2]=='P') && (postion[3]=='G') && (postion[4]=='G') && (postion[5]=='A')){

			for(i=0;i<6;i++){

				SERVICE_NAME[i]=postion[i];

			     }
			flag=1;


	    }

	SERVICE_NAME[i]='\0';

	if (flag==1)
		return 1;

return 0;
}



 void GPS_SERVICE_UTC(const unit8* postion,unit8* UTC){
	 unit8 i=0;
	 for(i=0;i<10;i++){
		 UTC[i]=postion[i+7];
	 }
	 UTC[i]='\0';

 }

 void UTC_SPLIT_HMS(unit8* UTC,unit8* HOUR,unit8* Min,unit8* Sec){
     	  unit8 i=0;
     	  for(i=0;i<2;i++){
     		  HOUR[i]=UTC[i];
 			  Min[i]=UTC[i+2];
 			  Sec[i]=UTC[i+4];
     	  }

 }



