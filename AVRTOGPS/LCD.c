/*
 * LCD.c
 *
 *  Created on: ??�/??�/????
 *      Author: Mohamed ELameer
 */

#include"LCD.h"



void LCD_init(void){
   /* set the control pins as output pins*/
	DIRECTION_CTRL_PINS |=(1<<RS)|(1<<RW)|(1<<E);

#if (BITS_MODES==8)
     /*out Pins for LCD 8 pins portc */
	DIRECTION_DATA_PINS=0xFF;
	/* eight bits mode*/
	LCD_sendCommand(BITS_8_MODES);
#endif

#if (BITS_MODES==4)
     #ifdef FIRST_PINS
	         DIRECTION_DATA_PINS|=0x0F;
	         LCD_sendCommand(BITS_4_MODES);
	         LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);
     #else
	         DIRECTION_DATA_PINS|=0xF0;
	         LCD_sendCommand(BITS_4_MODES);
	         LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE);

     #endif

#endif



	/*display on cursor off*/
	LCD_sendCommand(CURSOR_OFF);
	/* clear the screen first*/
	LCD_sendCommand(CLEAR_LCD);
}

void LCD_sendCommand(unit8 command){
	/*make RS=0 to send command*/
	Pin_clear(CTRL_OUTPUT_PINS  ,RS);
	/*make RW=0 to write command*/
	Pin_clear(CTRL_OUTPUT_PINS ,RW);
	/*wait tas before enabling 50ns */
	_delay_ms(1);
	/* Enable =1 */
	Pin_output(CTRL_OUTPUT_PINS  ,E);
	/* wait 190 ns before sending command tpw-tdsw*/
	_delay_ms(1);
#if (BITS_MODES==8)
	  /* write the command*/
	   DATA_OUTPUT_PINS =command;

	   /*wait tdpw to make enable =0*/
	   	_delay_ms(1);
	   	/* make enable =0*/
	   	Pin_clear(CTRL_OUTPUT_PINS,E);
	   	/*wait th 13ns */
	   	_delay_ms(1);
#endif

#if (BITS_MODES==4)
     #ifdef FIRST_PINS

	   /*	DATA_OUTPUT_PINS = (DATA_OUTPUT_PINS & 0xF0) | ((command & 0xF0) >> 4);*/
	   	    TAKE_FTCOMMAND(DATA_OUTPUT_PINS,command);
     #else
	   	/*DATA_OUTPUT_PINS=(DATA_OUTPUT_PINS & 0x0F) | (command & 0xF0);*/
	   	  TAKE_FTCOMMAND(DATA_OUTPUT_PINS,command);

     #endif

	/*wait tdpw to make enable =0 */
	_delay_ms(1);
	/* make enable =0*/
	Pin_clear(CTRL_OUTPUT_PINS,E);
	/*wait th 13ns */
	_delay_ms(1);

	/*start enabling again*/

		/* Enable =1 */
		Pin_output(CTRL_OUTPUT_PINS  ,E);
		/* wait 190 ns before sending command tpw-tdsw*/
		_delay_ms(1);

#if (BITS_MODES==4)
     #ifdef FIRST_PINS
		    /*DATA_OUTPUT_PINS = (DATA_OUTPUT_PINS& 0xF0) | (command & 0x0F);*/
		    TAKE_SCCOMMAND(DATA_OUTPUT_PINS,command);
     #else

	        /*DATA_OUTPUT_PINS=(DATA_OUTPUT_PINS&0x0F)|((command&0x0F)<<4);*/

	        TAKE_SCCOMMAND(DATA_OUTPUT_PINS,command);

     #endif

#endif
	        /*wait tdpw to make enable =0 */
	        	_delay_ms(1);
	        	/* make enable =0*/
	        	Pin_clear(CTRL_OUTPUT_PINS,E);
	        	/*wait th 13ns */
	        	_delay_ms(1);


}
#endif




  void LCD_displayChar(unit8 data){
	/*make RS=1 to send data*/
	Pin_output(CTRL_OUTPUT_PINS  ,RS);
	/*make RW=0 to write command*/
	Pin_clear(CTRL_OUTPUT_PINS  ,RW);
	/*wait tas before enabling 50ns */
	_delay_ms(1);
	/* Enable =1 */
	Pin_output(CTRL_OUTPUT_PINS  ,E);
	/* wait 190 ns before sending command tpw-tdsw*/
	_delay_ms(1);
	/* write the command*/
#if (BITS_MODES==8)
	  /* write the command*/
	   DATA_OUTPUT_PINS =data;

	   /*wait tdpw to make enable =0*/
	   	_delay_ms(1);
	   	/* make enable =0*/
	   	Pin_clear(CTRL_OUTPUT_PINS,E);
	   	/*wait th 13ns */
	   	_delay_ms(1);
#endif

#if (BITS_MODES==4)
     #ifdef FIRST_PINS
	   	/*DATA_OUTPUT_PINS = (DATA_OUTPUT_PINS & 0xF0) | ((data & 0xF0) >> 4);*/

	   	TAKE_FTCOMMAND(DATA_OUTPUT_PINS,data);

     #else
		/*DATA_OUTPUT_PINS=(DATA_OUTPUT_PINS & 0x0F) | (data & 0xF0);*/
		TAKE_FTCOMMAND(DATA_OUTPUT_PINS,data);

     #endif

	/*wait tdpw to make enable =0 */
	_delay_ms(1);
	/* make enable =0*/
	Pin_clear(CTRL_OUTPUT_PINS,E);
	/*wait th 13ns */
	_delay_ms(1);

	/*start enabling again*/

		/* Enable =1 */
		Pin_output(CTRL_OUTPUT_PINS  ,E);
		/* wait 190 ns before sending command tpw-tdsw*/
		_delay_ms(1);

#if (BITS_MODES==4)
     #ifdef FIRST_PINS
		/*DATA_OUTPUT_PINS = (DATA_OUTPUT_PINS& 0xF0) | (data & 0x0F);*/
		  TAKE_SCCOMMAND(DATA_OUTPUT_PINS,data);

     #else
	        /*DATA_OUTPUT_PINS=(DATA_OUTPUT_PINS&0x0F)|((data&0x0F)<<4);*/
		     TAKE_SCCOMMAND(DATA_OUTPUT_PINS,data);

     #endif

#endif
	        /*wait tdpw to make enable =0 */
	        	_delay_ms(1);
	        	/* make enable =0*/
	        	Pin_clear(CTRL_OUTPUT_PINS,E);
	        	/*wait th 13ns */
	        	_delay_ms(1);


}
#endif





   void LCD_displayString(const char *Str)
   {

   	while((*Str) != '\0')
   	{
   		LCD_displayChar(*Str);
   		Str++;
   	}
   }

   /*********************************************************************************************/

   void LCD_displayString_GPS(const char *Str)
      {

      	while((*Str) != '*')
      	{
      		LCD_displayChar(*Str);
      		Str++;
      	}
      }




   /***********************************************************************************************/


   void LCD_gotoRawCol(unit8 row, unit8 col){
	   unit8 address;
	   switch(row){
	       case 0:
		      address=col;
		       break;
	       case 1:
		      address=0x40+col;
	        }
	    LCD_sendCommand(address|CURSOR_MoveToFirstLoc);

	   }



void LCD_IntToStr(unit8 data){
	char buff[16];
	itoa(data,buff,10);
	LCD_displayString(buff);
}


void LCD_displayStrRowCol(unit8 row,unit8 col,const char *Str){
	unit8 address,i=0;
		   switch(row){
		       case 0:
			      address=col;
			       break;
		       case 1:
			      address=0x40+col;
		        }
    LCD_sendCommand(address|CURSOR_MoveToFirstLoc);

	while((*Str) != '\0')
   	{
   		LCD_displayChar(Str[i]);
   		Str++;
   	}
}


void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_LCD); //clear display
}


