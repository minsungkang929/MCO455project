/*
	Title:		MCO Final Project - Burglar Alarm System
	Author: 	Kang, Minsing (147175160) 
                Kim, Kun Eui (144719168)
	Date: 		July ??, 2018
	Description:	The program will emulate a BLODGERS HOME 
					monitoring Burglar Alarm System. 
					The PC SCREEN and PC KEYBOARD will represent
					the REMOTE BLODGERS Home monitoring Station. 
					The KEYPAD, LCD, SWITCHES, LEDS and 7 Segment
					Displays will represent the LOCAL ALARM SYSTEM.
 */

// Function prototypes
void scr_title(void);
void lcd_to_activate(void);
void scr_alarm_status(unsigned char act);
void scr_zone_sensor_status(void);
void lcd_alarm_off(void);
void lcd_staring(void);
void lcd_pls_close(void);
void lcd_still_open(void);

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "f:\library_de1.h"

void main(void)
{
	volatile unsigned char choice;
	
	SOPT_COPE = 0; /* disable COP */
	LCD_ROWS=4;
	LCD_COLS=16;
	devices_init();
	
	scr_title();
	lcd_to_activate();
	
	do
	{
		scr_setcursor(10, 35);
		choice = kb_getchar();
		switch(choice)
		{
			case '1':
				scr_alarm_status('1');		// 1 <= ACTIVATE
				scr_zone_sensor_status();	// sensing SWL
				lcd_alarm_off();			// alarm off
				while(KEY_1 != 1);
				lcd_staring();
				if(SWL != 0)
				{
					lcd_pls_close();
					lcd_still_open();
				}
				
				break;
			
			case '2':
				break;
				
			case '3':
				break;
					
			case '4':
				break;
		}
	} while (choice == '1' || choice == '2' || choice == '3' || choice == '4');
  
}

// function definitions
void scr_title(void)
{
	scr_clear();		// clear screen
	
	scr_setcursor(1, 10);
	scr_print("BLODGERS HOME MONITORING SYSTEM");
	scr_setcursor(3, 35);
	scr_print("MAIN MENU");
	scr_setcursor(5, 20);
	scr_print("1. ENABLE BURGLAR ALARM");
	scr_setcursor(6, 20);
	scr_print("2. RESET PASSWORD");
	scr_setcursor(7, 20);
	scr_print("3. RESET ALARM");
	scr_setcursor(8, 20);
	scr_print("4. DeACTIVATE ALARM");
  
	scr_setcursor(10, 20);
	scr_print("Your Choice - ");
  
	scr_setcursor(12, 17);
	scr_print("ALARM STATUS");
	scr_setcursor(13, 17);
	scr_print("DeACTIVATED");
  
	scr_setcursor(15, 17);
	scr_print("Local Alarm");
	scr_setcursor(16, 22);
	scr_print("OFF");
  
	scr_setcursor(12, 40);
	scr_print("ZONE Sensor STATUS");
	scr_setcursor(14, 42);
	scr_print("ZONE 1");
	scr_setcursor(15, 42);
	scr_print("ZONE 2");
	scr_setcursor(16, 42);
	scr_print("ZONE 3");
	scr_setcursor(17, 42);
	scr_print("ZONE 4");
	scr_setcursor(18, 42);
	scr_print("ZONE 5");
	scr_setcursor(19, 42);
	scr_print("ZONE 6");
	scr_setcursor(20, 42);
	scr_print("ZONE 7");
	scr_setcursor(21, 42);
	scr_print("ZONE 8");
	
	scr_setcursor(10, 35);
}

void lcd_to_activate(void)
{
	lcd_setcursor(0, 0);
	lcd_print("To activate your");
	lcd_setcursor(1, 2);
	lcd_print("Alarm System");
	lcd_setcursor(3, 2);
	lcd_print("Call BLODGERS");
}

void scr_alarm_status(unsigned char act)
{
	if(act == '1')
	{
		scr_setcursor(13, 17);
		scr_print("ACTIVATED  ");
	}
	else
	{
		scr_setcursor(13, 17);
		scr_print("DeACTIVATED");
	}
	scr_setcursor(10, 35);
}

void scr_zone_sensor_status(void)
{
	if(SWL_0 == 0)		// ZONE 1
	{
		scr_setcursor(14, 52);
		scr_print("CLOSED");
	}
	else
	{
		scr_setcursor(14, 52);
		scr_print("OPEN  ");
	}
	
	if(SWL_1 == 0)		// ZONE 2
		{
			scr_setcursor(15, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(15, 52);
			scr_print("OPEN  ");
		}
	
	if(SWL_2 == 0)		// ZONE 3
		{
			scr_setcursor(16, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(16, 52);
			scr_print("OPEN  ");
		}
	
	if(SWL_3 == 0)		// ZONE 4
		{
			scr_setcursor(17, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(17, 52);
			scr_print("OPEN  ");
		}
	
	if(SWL_4 == 0)		// ZONE 5
		{
			scr_setcursor(18, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(18, 52);
			scr_print("OPEN  ");
		}
	
	if(SWL_5 == 0)		// ZONE 6
		{
			scr_setcursor(19, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(19, 52);
			scr_print("OPEN  ");
		}
	
	if(SWL_6 == 0)		// ZONE 7
		{
			scr_setcursor(20, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(20, 52);
			scr_print("OPEN  ");
		}
	
	if(SWL_7 == 0)		// ZONE 8
		{
			scr_setcursor(21, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(21, 52);
			scr_print("OPEN  ");
		}
}

void lcd_alarm_off(void)
{
	lcd_setcursor(0, 0);
	lcd_print("Burglr Alarm OFF");
	lcd_setcursor(1, 0);
	lcd_print("To turn ON ALARM");
	lcd_setcursor(3, 3);
	lcd_print("Push KEY1");
}

void lcd_staring(void)
{
	lcd_setcursor(0, 2);
	lcd_print("Burglr Alarm");
	lcd_setcursor(1, 4);
	lcd_print("Start Up");
	lcd_setcursor(3, 1);
	lcd_print("Checking STATUS");
	lcd_setcursor(4, 3);
	lcd_print("Please Wait");
	delay_milli(2500);
}

void lcd_pls_close(void)
{
	lcd_setcursor(0, 0);
	lcd_print("Please Close All");
	lcd_setcursor(1, 3);
	lcd_print("Windows and");
	lcd_setcursor(3, 6);
	lcd_print("doors");
	delay_milli(1000);
}

void lcd_still_open(void)
{
	volatile unsigned char mask, count, ccount;
	
	lcd_setcursor(0, 2);
	lcd_print("Door/Windows");
	lcd_setcursor(1, 3);
	lcd_print("Still Open");
	lcd_setcursor(3, 1);
	lcd_print("8 7 6 5 4 3 2 1");
	
	while(SWL != 0)
	{
		mask = 0x80;
		ccount = 7;
		for(count = 1; i <= 8; ++count)
		{
			if(((SWL & mask) >> ccount) == 1)				// check SWL
			{
				lcd_setcursor(3, count*2-1);	// set cursor
				lcd_print("O");					// print 'O'
				LEDRL = LEDRL & (!mask);		// flash LED (off)
				LEDRL = LEDRL | mask;			// flash LED (on)
			}
			else
			{
				lcd_setcursor(3, count*2-1);	// set cursor
				lcd_print(" ");					// remove 'O'
				LEDRL = LEDRL & (!mask);		// turn off LED
			}
			mask = mask >> 1;
			--ccount;
		}
	}
}
