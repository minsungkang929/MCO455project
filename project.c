/*
"I declare that the attached source code is wholly my own work in accordance with Seneca 
Academic Policy. No part of this codehas been copied manually or electronically from any other 
source (including web sites) or distributed to other students." 

Name: Minsung Kang         Student ID: 147175160          Date: July 30, 2018                       
Name: Kun Eui Kim		   Student ID: 144719168		  Date: July 30, 2018
*/


/*
	Title:		MCO455 Final Project - Burglar Alarm System
	Author: 	Kang, Minsing (147175160) 
                Kim, Kun Eui (144719168)
	Date: 		July 30, 2018
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
void lcd_start_up(void);
void lcd_pls_close(void);
volatile unsigned char lcd_still_open(void);
void lcd_closed(void);
void lcd_arming(void);
void scr_local_alarm(unsigned char act);
volatile unsigned char lcd_password(void);
volatile unsigned char lcd_new_password(void);
void scr_zone_sensor_status_clr(void);
void scr_choice(unsigned char choice);
volatile unsigned char get_key(void);

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "f:\library_de1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// global variable
unsigned char password[6];
volatile unsigned long SWL_temp;

void main(void)
{
	volatile unsigned char choice;
		
	SOPT_COPE = 0; /* disable COP */
	LCD_ROWS=4;
	LCD_COLS=16;
	
	// set initial password "1234#"
	password[0] = '1';
	password[1] = '2';
	password[2] = '3';
	password[3] = '4';
	password[4] = '#';
	password[5] = '\0';
	
	devices_init();			// initialize diveices
	
	// background color to GREY
	while((SCI2S1 & 0x80)!=0x80); 
	SCI2D=0x1b;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x5b;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x34;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x37;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x6d;
															
	// foreground color to BLACK
	while((SCI2S1 & 0x80)!=0x80); 
	SCI2D=0x1b;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x5b;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x33;
	while((SCI2S1 & 0x80)!=0x80);
	SCI2D=0x30;
	while((SCI2S1 & 0x80)!=0x80);
	
	scr_title();			// display main menu on screen
	for(;;)					// alarm system program have to always run using for-loop
	{
		scr_alarm_status('0');	// alarm status: 1- ACTIVATE / 0-DeACTIVATE
		scr_local_alarm('0');	// local alarm: 1-ON / 0-OFF
		lcd_to_activate();		// display instruction to activate on LCD
		scr_setcursor(10, 35);
		while((choice=kb_getchar())== '\0');	// wait for user input to select menu
		switch(choice)
		{
			case '1':	// 1.   ENABLE BURGLAR ALARM
				do
				{
					choice = '1';
					SWL_temp = (SWL + 1) << 1;	//change SWL_temp value in different value with SWL to update ALARM STATUS 
					scr_choice('1');			// display choice on screen
					scr_alarm_status('1');		// alarm status: 1- ACTIVATE / 0-DeACTIVATE
					lcd_alarm_off();			// display "to turn on..." message on lcd
					
					while(SW_KEY1 != 0) 		// wait for KEY1 to be pressed
					{
						scr_zone_sensor_status();		// display zone status
						if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
						{ }								// do nothing
						else
						{
							choice=SCI2D;			// store received character in variable
							if(choice == '4')		// 4.   DeACTIVATE ALARM
							{
						        scr_choice(' ');				// display choice on screen
								scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
								scr_zone_sensor_status_clr();	// clear zone status
								scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
								break;							// break while loop
							}
							else if(choice == '2')	// 2.   RESET PASSWORD
							{
								scr_choice(' ');				// display choice on screen
								choice = lcd_new_password();	// function to change password
								scr_setcursor(10, 35);
								break;							// break while loop
							}
							else if(choice == '3')	// 3.   RESET ALARM
							{
								scr_choice(' ');							// display choice on screen
								scr_setcursor(11, 35);
								scr_print("Unavailable!! Alarm is OFF!!");	// display error message
								delay_milli(2000);
								scr_setcursor(11, 35);
								scr_print("                            ");	// remove error message
							}
							else if(choice == '1')	// 1.   ENABLE BURGLAR ALARM
							{
								scr_choice(' ');											// display choice on screen
								scr_setcursor(11, 35);
								scr_print("Unavailable!! System is already activated!!");	// display error message
								delay_milli(2000);
								scr_setcursor(11, 35);
								scr_print("                                           ");	// remove error message
														}
							else
							{}			// do nothing, go back to while loop
						}	// end of if-else
					}	// end of while(SW_KEY1 != 0)
					
					if(choice != '4' && choice != '2')	// if not 4,2, proceed to start up
					{
						lcd_start_up();				// display start up on LCD
						do
						{
							if(SWL != 0)				// check SWL up
							{
								lcd_pls_close();			// display massage on LCD
								choice = lcd_still_open();	// display SWL status on LCD
								if(choice == '4')			// if 4, break and go to deactivate
									break;
								lcd_closed();			// display ARM or Cncl menu on LCD
							}
							else						// NO SWL up
								lcd_closed();			// display ARM or Cncl menu on LCD
				
							for(;;)
							{
								scr_zone_sensor_status();	// display zone status on screen
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
									break;
								}
								if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
								{ }								// do nothing
								else
								{
									choice=SCI2D;					// store received character in variable
									if(choice == '4')				// if keyboard 4 is pressed, deactivate system
									{
										scr_choice(' ');				// display choice on screen
										scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
										scr_zone_sensor_status_clr();	// clear zone status
										scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
										choice = '4';					// now menu choice is 4
										break;							// break for loop
									}
								}
							}	// end of for-loop
						} while(SWL != 0 && choice != '4');				// do-while loop for checking SWL down
					} // end of if(choice != '4' && choice != '2')
					
					if(choice == '9')	// start arming
					{
						lcd_arming();				// arm windows and doors
						
						//while(SWL == 0);			// check for SWL up
						for(;;)	// sense SWL up of key 4 pressed
						{
							if(SWL != 0)			// if SWL up, break to check password
							{
								break;
							}
							if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
							{ }								// do nothing
							else
							{
								choice=SCI2D;					// store received character in variable
								if(choice == '4')				// if keyboard 4 is pressed, deactivate system
								{
									scr_choice(' ');				// display choice on screen
									scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
									scr_zone_sensor_status_clr();	// clear zone status
									scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
									choice = '4';					// now menu choice is 4
									break;							// break for loop
								}
							}
						}	// end of for-loop
						if (choice == '4')	// if key 4, break loop to deactivate
							break;
						
						// since SWL up, set alarm on and check password
						scr_local_alarm('1');		// local alarm: 1-ON / 0-OFF				
						choice = lcd_password();	// get password 1st try
						if (choice == '4')	// if key 4, break loop to deactivate
							break;
									
						if(strcmp(key_buff, password) != 0)	// if wrong password for the 1st try
							choice = lcd_password();		// get password 2nd try
						if (choice == '4')	// if key 4, break loop to deactivate
							break;
									
						if(strcmp(key_buff, password) != 0)		// if wrong password again
						{
							// change font color on screen to alert!!
							// background color to RED
							while((SCI2S1 & 0x80)!=0x80); 
							SCI2D=0x1b;	// <ESC>
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x5b;	// [
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x34;	// 4
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x31;	// 1
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x6d;	// m
							
							// foreground color to white
							while((SCI2S1 & 0x80)!=0x80); 
							SCI2D=0x1b;	// <ESC>
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x5b;	// [
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x33;	// 3
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x37;	// 7
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x6d;	// m
							
							scr_title();				// display main menu on screen with new color
							scr_local_alarm('1');		// local alarm: 1-ON / 0-OFF
							SWL_temp = (SWL + 1) << 1;	//change SWL_temp value in different value with SWL to update ALARM STATUS
							
							// LED flash because of an intruder
							for(;;)
							{
								scr_zone_sensor_status();	// display zone status
							
								LEDRL = 0xff;				// LED flash
								delay_milli(250);			// with 0.5s delay
								scr_zone_sensor_status();	// display zone status
								LEDRL = 0x00;				//
								delay_milli(250);			//
												
								if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
								{ }								// do nothing
								else
								{
									choice=SCI2D;		// store received character in variable
									if(choice == '4')	// 4.   DeACTIVATE ALARM
									{
										scr_choice(' ');				// display choice on screen
										scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
										scr_zone_sensor_status_clr();	// clear zone status
										scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
										scr_setcursor(18, 14);
										scr_print("                ");	// remove message "Password Pending"
										break;							// break for loop
									}
									else if(choice == '3')	// 3.   RESET ALARM
									{
										scr_alarm_status('1');		// alarm status: 1- ACTIVATE / 0-DeACTIVATE
										scr_zone_sensor_status();	// display zone status
										scr_local_alarm('0');		// local alarm: 1-ON / 0-OFF
										scr_setcursor(18, 14);
										scr_print("                 ");
										break;						// break for loop
									}
								}
							}	// end of for loop
							
							// change font color for normal status
							// background color to GREY
							while((SCI2S1 & 0x80)!=0x80); 
							SCI2D=0x1b;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x5b;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x34;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x37;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x6d;
														
							// foreground color to BLACK
							while((SCI2S1 & 0x80)!=0x80); 
							SCI2D=0x1b;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x5b;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x33;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x30;
							while((SCI2S1 & 0x80)!=0x80);
							SCI2D=0x6d;
							
							scr_title();			// display main menu on screen with new color
							scr_local_alarm('0');	// local alarm: 1-ON / 0-OFF							
						}	// end of if(strcmp(key_buff, password) != 0)
						else							// if correct password
						{
							scr_local_alarm('0');		// local alarm: 1-ON / 0-OFF
							scr_setcursor(18, 14);
							scr_print("Password Accepted");
							delay_milli(1000);
							scr_setcursor(18, 14);
							scr_print("                 ");
						}
					}	// end of if(choice != '4' && choice != '8' && choice != '2')					
				} while (choice == '8' || choice == '9'|| choice == '3' || choice == '2' );		// proceed do-while loop to go back to "to turn on..."				
				break;
			
			default:
				scr_setcursor(11, 35);
				scr_print("Unavailable!! Please activate system!!");
				delay_milli(1500);
				scr_setcursor(11, 35);
				scr_print("                                      ");
				break;
		}	// end of switch
	}		// end of for loop  
}			// end of main

// function definitions

/*
  to display title on screen
*/
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
  
	scr_setcursor(15, 17);
	scr_print("Local Alarm");
  
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

/*
 	 to show instruction on lcd for users to activate
*/ 
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

/*
 	 to write alarm status on screen
 	 1 = activate / 0 = deactivate
*/
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

/*	
 	 to read SWL value and display the value on screen 
*/
void scr_zone_sensor_status(void)
{
	volatile unsigned char mask, count;
	mask = 0x01;
	if(SWL != SWL_temp)
	{
		for(count = 1; count <= 8; ++count)
		{
			if((SWL & mask) == 0)
			{
				scr_setcursor(13+count, 52);
				scr_print("CLOSED");
			}
			else
			{
				
				// change font color to identify SWL status easily
				// background color to yellow
				while((SCI2S1 & 0x80)!=0x80); 
				SCI2D=0x1b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x5b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x34;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x33;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x6d;
															
				// foreground color to black
				while((SCI2S1 & 0x80)!=0x80); 
				SCI2D=0x1b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x5b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x33;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x30;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x6d;
											
				scr_setcursor(13+count, 52);
				scr_print("OPEN  ");
				
				// change font color for normal status
				// background color to white
				while((SCI2S1 & 0x80)!=0x80); 
				SCI2D=0x1b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x5b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x34;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x37;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x6d;
												
				// foreground color to black
				while((SCI2S1 & 0x80)!=0x80); 
				SCI2D=0x1b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x5b;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x33;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x30;
				while((SCI2S1 & 0x80)!=0x80);
				SCI2D=0x6d;
			}
			mask = mask << 1;
		}
		SWL_temp = SWL;
	}
	scr_setcursor(10, 35);	
}

/*
 	 to display instruction to turn on alarm on lcd
*/
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

/*
 	 to dispay checking status message and wait for 2.5sec
*/
void lcd_start_up(void)
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

/*
 	 to write instruction on lcd to close windows and doors
*/
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

/*
 	 to display windows and door status on lcd
 	 if all windows are closed, return 1 to proceed next step
 	 if keyboard 4 is pressed, return 4 to indicate deactivate
*/
volatile unsigned char lcd_still_open(void)
{
	volatile unsigned char choice, mask, count, ccount;
	
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
		if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
	    { }								// do nothing
	    else
	    {
	    	choice=SCI2D;						// store received character in variable
	    	if(choice == '4')				// if keyboard 4 is pressed, deactivate system
	    	{
	    		scr_choice(' ');				// display choice on screen
	    		scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
	    		scr_zone_sensor_status_clr();	// clear zone status
	    		scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
	    		scr_setcursor(18, 14);
	    		scr_print("                ");	// remove message "Password Pending"
	    		return '4';
	    	}
	    }
	}
	return '1';
}

/*
 	 to display instruction for next step on lcd
*/
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

/*
 	 to display arming message on lcd and count down 3 to 1
 	 after that, display armed message
*/
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
	lcd_setcursor(1, 2);
	lcd_print("now ARMED!!");
	lcd_setcursor(2, 0);
	lcd_print("Checking Windows");
	lcd_setcursor(3, 4);
	lcd_print("and doors");
	HEX0 = 0b11111111;
}

/*
 	 to write local alarm status on screen
 	 1 = ON / 0 = OFF
*/
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

/*
 	 to get password using keypad
 	 if get password from user, return 9 to proceed next step
 	 if keyboard 4 is pressed, return 4 to deactivate
*/
volatile unsigned char lcd_password(void)
{
	unsigned char count;
	
	lcd_clear();
	lcd_setcursor(0, 1);
	lcd_print("Enter Password");
	lcd_setcursor(1, 0);
	lcd_print("within Two Tries");
	lcd_setcursor(2, 2);
	lcd_print("to deactivate");
	
	scr_setcursor(18, 14);
	scr_print("Password Pending");
	
	
	lcd_setcursor(3, 6);
	for(count = 0 ; count < 5 ; ++count)
	{
		lcd_blink();
		key_buff[count] = get_key();
		if(key_buff[count] == 'x')
		{
			return '4';
		} else{}
		key_buff[count] = keypad();
		key_buff[count+1] = '\0';
		lcd_print("*");
		count+=6;
		lcd_setcursor(3, count+1);
		count-=6;
		
		if(password[count+1] == '\0')
		{
			return '9';
		}
	}
	return '9';
}

/*
 	 to change password using keypad
 	 password has max.4 digit + # in the end.
 	 if new password set is success, return 2 to proceed next step
 	 if keyboard 4 is pressed, return 4 to deactivate
*/
volatile unsigned char lcd_new_password(void)
{
	unsigned char choice[3];
	unsigned char temppass[6];
	unsigned char count;
	
	do
	{
		temppass[0] = '1';
		temppass[1] = '1';
		temppass[2] = '1';
		temppass[3] = '1';
		temppass[4] = '1';
		
		lcd_clear();
		lcd_setcursor(0, 2);
		lcd_print("New Password");
		
		lcd_setcursor(1, 6);
		for(count = 0 ; count < 5 ; ++count)
		{
			if(count == 4)
			{
				do
				{
					temppass[count] = get_key();
					if(temppass[count] == 'x')
					{
						choice[0] = '4';
						return '4';
					} else{}
					temppass[count] = keypad();
				} while(temppass[count] != '#');
				
			} else{}
			if(temppass[count] == '#')
			{
				temppass[count+1] = '\0';
				break;
			} else{}
			lcd_blink();
			temppass[count] = get_key();
			if(temppass[count] == 'x')
			{
				choice[0] = '4';
				return '4';
			} else{}
			temppass[count] = keypad();
			lcd_print("*");
			count+=6;
			lcd_setcursor(1, count+1);
			count-=6;
			
			if(temppass[count] == '#')
			{
				temppass[count+1] = '\0';
				break;
			} else{}
		}	// end of for loop
		
		if(choice[0] != '4')
		{
			choice[0] = '0';
			choice[1] = '0';
			
			lcd_setcursor(2, 2);
			lcd_print("OK=1, No=2");
		
			lcd_setcursor(3, 7);
			for(count = 0 ; count < 2 ; ++count)
			{
				if(count == 1)
				{
					do
					{
						choice[count] = get_key();
						if(choice[count] == 'x')
						{
							choice[0] = '4';
							return '4';
						} else{}
						choice[count] = keypad();
					} while(choice[count] != '#');
					
				} else{}
				if(choice[count] == '#')
				{
					break;
				} else{}
				
				lcd_blink();
				choice[count] = get_key();
				
				if(choice[count] == 'x')
				{
					choice[0] = '4';
					return '4';
				} else{}
				
				choice[count] = keypad();
				lcd_print("*");
				count+=7;
				lcd_setcursor(3, count+1);
				count-=7;
				
				if(choice[count] == '#')
				{
					break;
				} else{}
			}	// end of for loop
			
			if(choice[0] == '1')
			{
				password[0] = temppass[0];
				password[1] = temppass[1];
				password[2] = temppass[2];
				password[3] = temppass[3];
				password[4] = temppass[4];
				password[5] = temppass[5];
			}
		}
	} while(choice[0] != '1' && choice[0] != '4');
	return '2';
}

/*
 	 to remove alarm status on screen
*/
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

/*
 	 to write user choice on screen
*/
void scr_choice(unsigned char choice)
{
	scr_setcursor(10, 35);
	while(SCI2S1_TDRE == 0); //wait for TDRE=1
	SCI2D= choice;			// print choice on screen
}

/*
 	 to get key using keypad
 	 if keypad is pressed, return variable key_value
 	 if keyboard 4 is pressed, return x to indicate deactivate
*/
volatile unsigned char get_key(void) 
{
  volatile unsigned char dummy_key;
  volatile unsigned char choice;
   do 
  {      
     PTADD = 0xF0;                 
// set PortA  ROWS to output and Columns to input
     delay_micro(5);                  
// wait for PORTA to change Data Direction
     PTAD  = 0x00;                   
// put 0 on ROWS and check columns 
     dummy_key=PTAD;           
// put Column value into dummy_key()
     PTADD = 0x0F;                 
// set PortA  Columns to output and Rows to  input
     delay_micro(5);                  
// wait for PORTA to change Data Direction
     PTAD=0x00;                      
// put 00 on Columns and check Rows
     dummy_key=dummy_key + PTAD;  
// key_value gets combined PORTA value
     if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
     { }								// do nothing
     else
     {
     	choice=SCI2D;						// store received character in variable
     	if(choice == '4')				// if keyboard 4 is pressed, deactivate system
     	{
     		scr_choice(' ');				// display choice on screen
     		scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
     		scr_zone_sensor_status_clr();	// clear zone status
     		scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
     		scr_setcursor(18, 14);
     		scr_print("                ");	// remove message "Password Pending"
     		return 'x';
     	}
     }
     scr_zone_sensor_status();	// display zone status
  }
// keep doing till a keypress is detected, which happens if value in dummy_key is not FF
  while (((dummy_key >> 4) != 0x0F)&& ((dummy_key & 0x0f)!= 0x0f));
  delay_milli(20);               
// wait for key to be debounced
  do 
  {      
     PTADD = 0xF0;                 
// set PortA  ROWS to output and Columns to input
     delay_micro(5);                  
// wait for PORTA to change Data Direction
     PTAD  = 0x00;                   
//  put 0 on ROWS and check columns 
     key_value=PTAD;              
// key_value gets Column value
     PTADD = 0x0F;                 
// set PortA  Columns to output and Rows to  input
     delay_micro(5);                  
// wait for PORTA to change Data Direction
     PTAD=0x00;                      
// put 00 on Columns and check Rows
     key_value=key_value + PTAD;     
// key_value gets total PORTA value  
// keep going till result is not FX or XF
     if (( SCI2S1 & 0x20) != 0x20)	// check if receiver has no character
          { }								// do nothing
          else
          {
          	choice=SCI2D;						// store received character in variable
          	if(choice == '4')				// if keyboard 4 is pressed, deactivate system
          	{
          		scr_choice(' ');				// display choice on screen
          		scr_alarm_status('0');			// alarm status: 1- ACTIVATE / 0-DeACTIVATE
          		scr_zone_sensor_status_clr();	// clear zone status
          		scr_local_alarm('0');			// local alarm: 1-ON / 0-OFF
          		scr_setcursor(18, 14);
          		scr_print("                ");	// remove message "Password Pending"
          		return 'x';
          	}
          }
     scr_zone_sensor_status();	// display zone status
  } 
//(valid keypress doesn’t have F as either digit.)
  while (((key_value >> 4) == 0x0F) || ((key_value & 0x0f)== 0x0f)); 
  return(key_value);                
// return valid keypress
}

