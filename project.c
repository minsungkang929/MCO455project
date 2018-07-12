/*
	Title:		MCO455 Final Project - Burglar Alarm System
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
void lcd_starting(void);
void lcd_pls_close(void);
void lcd_still_open(void);
void lcd_closed(void);
void lcd_arming(void);
void scr_local_alarm(unsigned char act);
void lcd_password(void);
void lcd_new_password(void);
void scr_zone_sensor_status_clr(void);
void scr_choice(unsigned char choice);

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "f:\library_de1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global variable
unsigned char password[] = "1234#";

void main(void)
{
	volatile unsigned char choice;
		
	SOPT_COPE = 0; /* disable COP */
	LCD_ROWS=4;
	LCD_COLS=16;
	devices_init();			// initialize diveices
	
	scr_title();			// display main menu on screen
	scr_alarm_status('2');	// alarm status: 1- ACTIVATE / 2-DeACTIVATE
	scr_local_alarm('2');	// local alarm: 1-ON / 2-OFF
		
	do
	{
		lcd_to_activate();		// display instruction to activate on LCD
		scr_setcursor(10, 35);
		while((choice=kb_getchar())== '\0');
		switch(choice)
		{
			case '1':
				do
				{
					scr_choice('1');			// display choice on screen
					scr_alarm_status('1');		// alarm status: 1- ACTIVATE / 2-DeACTIVATE
					lcd_alarm_off();			// alarm off
					while(SW_KEY1 != 0) 		// wait for KEY1 to be pressed
					{
						scr_zone_sensor_status();	// display zone status
						if(kb_getchar() == '4')			// if keyboard 4 is pressed
						{
							scr_choice('4');			// display choice on screen
							scr_alarm_status('2');		// alarm status: 1- ACTIVATE / 2-DeACTIVATE
							scr_zone_sensor_status_clr();	// clear zone status
							scr_local_alarm('2');		// local alarm: 1-ON / 2-OFF
							choice = '4';				// now menu choice is 4
							break;						// break while loop
						}
					}
					if(choice != '4')				// if not 4, proceed
					{
						lcd_starting();				// display starting on LCD
						do
						{
							if(SWL != 0)				// check SWL up
							{
								lcd_pls_close();		// display massage on LCD
								lcd_still_open();		// display SWL status on LCD
								lcd_closed();			// display ARM or Cncl menu on LCD
							}
							else						// NO SWL up
								lcd_closed();			// display ARM or Cncl menu on LCD
				
							for(;;)
							{
								if(SW_KEY2 == 0)		// if KEY2 is pressed
								{
									choice = '8';		// prepare to go back to Alarm off
									break;
								}
								if(SW_KEY3 == 0)		// if KEY3 is pressed
								{
									choice = '9';		// prepare to arm
									break;
								}
								if(SWL != 0)			// if SWL up, go back to check SWL
								{
									scr_zone_sensor_status();	// display zone status on screen
									break;
								}
							}
						} while(SWL != 0);				// do-while loop for checking SWL down
						
						if(choice == '9')			// prepare to arm
							break;					// exit from do-while loop
					}
				} while (choice == '8');		// proceed do-while loop to go back to Alarm off
				
				if(choice != '4')				// if not 4, proceed
				{
					choice = '1';				// case choice is 1
					lcd_arming();				// arm windows and doors
					
					while(SWL == 0);			// check for SWL up
					
					scr_local_alarm('1');		// local alarm: 1-ON / 2-OFF				
					lcd_password();				// get password 1st try
				
					if(strcmp(key_buff, password) == 0)	// if wrong password for the 1st try
					lcd_password();						// get password 2nd try
				
					if(strcmp(key_buff, password) == 0)		// if wrong password again
					{
						for(;;)
						{
							// system("COLOR 70");		// 7-white bg, 0-black font
							//system("COLOR 47");			// 4-red bg, 0-white font
							//scr_title();
							//scr_alarm_status('1');		// alarm status: 1- ACTIVATE / 2-DeACTIVATE
							scr_zone_sensor_status();	// display zone status
							//scr_local_alarm('1');		// local alarm: 1-ON / 2-OFF
						
							LEDRL = 0xff;				// LED flash
							delay_milli(500);			// with 0.5s delay
							LEDRL = 0x00;				//
							delay_milli(500);			//
							
								if(kb_getchar() == '3') // wait for 3 to reset
								{
									//system("COLOR 70");			// 7-white bg, 0-black font
									scr_title();
									scr_alarm_status('1');		// alarm status: 1- ACTIVATE / 2-DeACTIVATE
									scr_zone_sensor_status();	// display zone status
									scr_local_alarm('2');		// local alarm: 1-ON / 2-OFF
									break;						// break for-loop
								}
							}
						}
					else							// if correct password
					{
						scr_local_alarm('2');		// local alarm: 1-ON / 2-OFF
						scr_setcursor(18, 14);
						scr_print("Password Accepted");
						delay_milli(1000);
						scr_setcursor(18, 14);
						scr_print("                 ");
					}
				}
				break;
			
			case '2':
				scr_choice('2');			// display choice on screen
				lcd_new_password();
				break;
				
			//case '3':
			//	break;
					
			case '4':
				scr_choice('4');			// display choice on screen
				scr_alarm_status('2');		// alarm status: 1- ACTIVATE / 2-DeACTIVATE
				scr_zone_sensor_status_clr();	// clr zone status
				scr_local_alarm('2');		// local alarm: 1-ON / 2-OFF
				break;
				
			default:
				scr_choice(choice);			// display choice on screen
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
	//scr_setcursor(13, 17);
	//scr_print("DeACTIVATED");
  
	scr_setcursor(15, 17);
	scr_print("Local Alarm");
	//scr_setcursor(16, 22);
	//scr_print("OFF");
  
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
	lcd_clear();
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
	volatile unsigned char mask, count, ccount;
	for(count = 1; count <= 8; ++count)
	{
		mask = 0x01;
		if((SWL & mask) == 0)
		{
			scr_setcursor(13+count, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(13+count, 52);
			scr_print("OPEN  ");
		}
		mask = mask << 1;
	}
	
	/*
	if(SW_SW0 == 0)		// ZONE 1
	{
		scr_setcursor(14, 52);
		scr_print("CLOSED");
	}
	else
	{
		scr_setcursor(14, 52);
		scr_print("OPEN  ");
	}
	
	if(SW_SW1 == 0)		// ZONE 2
		{
			scr_setcursor(15, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(15, 52);
			scr_print("OPEN  ");
		}
	
	if(SW_SW2 == 0)		// ZONE 3
		{
			scr_setcursor(16, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(16, 52);
			scr_print("OPEN  ");
		}
	
	if(SW_SW3 == 0)		// ZONE 4
		{
			scr_setcursor(17, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(17, 52);
			scr_print("OPEN  ");
		}
	
	if(SW_SW4 == 0)		// ZONE 5
		{
			scr_setcursor(18, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(18, 52);
			scr_print("OPEN  ");
		}
	
	if(SW_SW5 == 0)		// ZONE 6
		{
			scr_setcursor(19, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(19, 52);
			scr_print("OPEN  ");
		}
	
	if(SW_SW6 == 0)		// ZONE 7
		{
			scr_setcursor(20, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(20, 52);
			scr_print("OPEN  ");
		}
	
	if(SW_SW7 == 0)		// ZONE 8
		{
			scr_setcursor(21, 52);
			scr_print("CLOSED");
		}
		else
		{
			scr_setcursor(21, 52);
			scr_print("OPEN  ");
		}
		*/
}

void lcd_alarm_off(void)
{
	lcd_clear();
	lcd_setcursor(0, 0);
	lcd_print("Burglr Alarm OFF");
	lcd_setcursor(1, 0);
	lcd_print("To turn ON ALARM");
	lcd_setcursor(3, 3);
	lcd_print("Push KEY1");
}

void lcd_starting(void)
{
	lcd_clear();
	lcd_setcursor(0, 2);
	lcd_print("Burglr Alarm");
	lcd_setcursor(1, 4);
	lcd_print("Start Up");
	lcd_setcursor(2, 1);
	lcd_print("Checking STATUS");
	lcd_setcursor(3, 3);
	lcd_print("Please Wait");
	delay_milli(2500);
}

void lcd_pls_close(void)
{
	lcd_clear();
	lcd_setcursor(0, 0);
	lcd_print("Please Close All");
	lcd_setcursor(1, 3);
	lcd_print("Windows and");
	lcd_setcursor(2, 6);
	lcd_print("doors");
	delay_milli(1000);
}

void lcd_still_open(void)
{
	volatile unsigned char mask, count, ccount;
	
	lcd_clear();
	lcd_setcursor(0, 2);
	lcd_print("Door/Windows");
	lcd_setcursor(1, 3);
	lcd_print("Still Open");
	lcd_setcursor(2, 1);
	lcd_print("8 7 6 5 4 3 2 1");
	
	while(SWL != 0)
	{
		scr_zone_sensor_status();	// display zone status on screen
		mask = 0x80;
		ccount = 7;
		for(count = 1; count <= 8; ++count)
		{
			if(((SWL & mask) >> ccount) == 1)	// check SWL
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

void lcd_closed(void)
{
	lcd_clear();
	lcd_setcursor(0, 2);
	lcd_print("All Doors and");
	lcd_setcursor(1, 3);
	lcd_print("Windows are");
	lcd_setcursor(2, 4);
	lcd_print("closed");
	lcd_setcursor(3, 0);
	lcd_print("KY3=ARM,KY2=Cncl");
}

void lcd_arming(void)
{
	volatile unsigned char count;
	
	lcd_clear();
	lcd_setcursor(0, 2);
	lcd_print("System ARMING");
	lcd_setcursor(1, 1);
	lcd_print("You must leave");
	lcd_setcursor(2, 0);
	lcd_print("Before the count");
	lcd_setcursor(3, 0);
	lcd_print("down is complete");
	
	for(count = 1; count <= 4 ; ++count)		// countdown 3 to 0
	{
		HEX3=0b01111110;
		delay_milli(100);
	
		HEX3=0b11111110;
		HEX2=0b01111110;
		delay_milli(100);
	
		HEX2=0b11111110;
		HEX1=0b01111110;
		delay_milli(100);
		
		HEX1=0b11111110;
		HEX3=0b11111100;
		delay_milli(100);
		
		HEX3=0b11111110;
		HEX2=0b11111100;
		delay_milli(100);
		
		HEX2=0b11111110;
		HEX1=0b11111100;
		delay_milli(100);
	
		HEX1=0b11111110;
		HEX3=0b11101110;
		delay_milli(100);
	
		HEX3=0b11111110;
		HEX2=0b11101110;
		delay_milli(100);
		
		HEX2=0b11111110;
		HEX1=0b11101110;
		delay_milli(100);
	
		HEX1=0b11111110;
		
		if(count == 1)
			HEX0 = 0b00001100;
		else if(count == 2)
			HEX0 = 0b00100100;
		else if(count == 3)
			HEX0 = 0b10011110;
		else
			HEX0 = 0b00000010;		
	}
	
	lcd_clear();
	lcd_setcursor(0, 2);
	lcd_print("Burglar Alarm");
	lcd_setcursor(1, 1);
	lcd_print("now ACTTIVATED");
	lcd_setcursor(2, 0);
	lcd_print("Checking Windows");
	lcd_setcursor(3, 4);
	lcd_print("and doors");
	HEX0 = 0b11111111;
}

void scr_local_alarm(unsigned char act)
{
	if(act == '1')
	{
		scr_setcursor(16, 22);
		scr_print("ON ");
	}
	else
	{
		scr_setcursor(16, 22);
		scr_print("OFF");
	}
		
}

void lcd_password(void)
{
	lcd_clear();
	lcd_setcursor(0, 1);
	lcd_print("Enter Password");
	lcd_setcursor(1, 0);
	lcd_print("within Two Tries");
	lcd_setcursor(2, 2);
	lcd_print("to deactivate");
	
	scr_setcursor(18, 14);
	scr_print("Password Pending");
	
	key_input(5, 3, 6, 0);			// 4 digits, row 3, col 6, show *
}

void lcd_new_password(void)
{
	//volatile unsigned char choice;
	unsigned char choice[2];
	unsigned char temppass[5];
	do
	{
		lcd_clear();
		lcd_setcursor(0, 2);
		lcd_print("New Password");
	
		key_input(5, 1, 6, 1);		// 4 digits, row 1, col 6, show number
		temppass[0] = key_buff[0];
		temppass[1] = key_buff[1];
		temppass[2] = key_buff[2];
		temppass[3] = key_buff[3];
		temppass[4] = key_buff[4];
				
		lcd_setcursor(2, 2);
		lcd_print("OK=1, No=2");
		
		//choice = get_key();		// get key from keypad
		//choice = keypad();		// convert keypad value to ascii
		key_input(2, 3, 6, 1);		// 4 digits, row 1, col 6, show number
		choice[0] = key_buff[0];
		choice[1] = key_buff[1];
		
		if(choice[0] == '1')
		{
			//strcpy(password, temppass);
			password[0] = temppass[0];
			password[1] = temppass[1];
			password[2] = temppass[2];
			password[3] = temppass[3];
			password[4] = temppass[4];
		}
	} while(choice[0] != '1');
}

void scr_zone_sensor_status_clr(void)
{
	scr_setcursor(14, 52);
	scr_print("      ");
	scr_setcursor(15, 52);
	scr_print("      ");
	scr_setcursor(16, 52);
	scr_print("      ");
	scr_setcursor(17, 52);
	scr_print("      ");
	scr_setcursor(18, 52);
	scr_print("      ");
	scr_setcursor(19, 52);
	scr_print("      ");
	scr_setcursor(20, 52);
	scr_print("      ");
	scr_setcursor(21, 52);
	scr_print("      ");
}

void scr_choice(unsigned char choice)
{
	scr_setcursor(10, 35);
	scr_print(&choice);
}
