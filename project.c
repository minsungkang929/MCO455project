/*
	Title: MCO Final Project - Burglar Alarm System
	Author: Kang, Minsing (147175160) 
                Kim, Kun Eui (144719168)
	Date: July ??, 2018
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

#include <hidef.h> /* for EnableInterrupts macro */
#include "derivative.h" /* include peripheral declarations */
#include "f:\library_de1.h"

void main(void)
{
	volatile unsigned char input, count, mask;
	
	SOPT_COPE = 0; /* disable COP */
	LCD_ROWS=4;
	LCD_COLS=16;
	devices_init();
	
	scr_title();
	lcd_to_activate();
  
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
	scr_print("DeACTIVATED");  // should be changed
  
	scr_setcursor(15, 17);
	scr_print("Local Alarm");
	scr_setcursor(16, 22);
	scr_print("OFF");  // should be changed
  
	scr_setcursor(12, 40);
	scr_print("ZONE Sensor STATUS");
	scr_setcursor(14, 42);
	scr_print("ZONE 1");
	scr_setcursor(16, 42);
	scr_print("ZONE 2");
	scr_setcursor(17, 42);
	scr_print("ZONE 3");
	scr_setcursor(18, 42);
	scr_print("ZONE 4");
	scr_setcursor(19, 42);
	scr_print("ZONE 5");
	scr_setcursor(20, 42);
	scr_print("ZONE 6");
	scr_setcursor(21, 42);
	scr_print("ZONE 7");
	scr_setcursor(22, 42);
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
