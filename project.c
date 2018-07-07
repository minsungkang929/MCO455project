/*
	Title: MCO Final Project - Burglar Alarm System
	Author: Kang, Minsing (147175160) 
          Kim, Kun Eui (         )
	Date: July ??, 2018
	Description:	The program will emulate a BLODGERS HOME 
					monitoring Burglar Alarm System. 
					The PC SCREEN and PC KEYBOARD will represent
					the REMOTE BLODGERS Home monitoring Station. 
					The KEYPAD, LCD, SWITCHES, LEDS and 7 Segment
					Displays will represent the LOCAL ALARM SYSTEM.
 */

// Function prototypes
void screen_title(void);

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
  
}

// function definitions
void screen_title(void)
{
	void scr_setcursor(1, 10);
	void scr_print("BLODGERS HOME MONITORING SYSTEM");
  void scr_setcursor(3, 35);
  void scr_print("MAIN MENU");
  void scr_setcursor(5, 20);
  void scr_print("1. ENABLE BURGLAR ALARM");
  void scr_setcursor(6, 20);
  void scr_print("2. RESET PASSWORD");
  void scr_setcursor(7, 20);
  void scr_print("3. RESET ALARM");
  void scr_setcursor(8, 20);
  void scr_print("4. DeACTIVATE ALARM");
  
  void scr_setcursor(10, 20);
  void scr_print("Your Choice ");
  
  void scr_setcursor(12, 17);
  void scr_print("ALARM STATUS");
  void scr_setcursor(13, 17);
  void scr_print("DeACTIVATED");  // should be changed
  
  void scr_setcursor(15, 17);
  void scr_print("Local Alarm");
  void scr_setcursor(16, 22);
  void scr_print("OFF");  // should be changed
  
  void scr_setcursor(12, 40);
  void scr_print("ZONE Sensor STATUS");
  void scr_setcursor(14, 42);
  void scr_print("ZONE 1");
  void scr_setcursor(16, 42);
  void scr_print("ZONE 2");
  void scr_setcursor(17, 42);
  void scr_print("ZONE 3");
  void scr_setcursor(18, 42);
  void scr_print("ZONE 4");
  void scr_setcursor(19, 42);
  void scr_print("ZONE 5");
  void scr_setcursor(20, 42);
  void scr_print("ZONE 6");
  void scr_setcursor(21, 42);
  void scr_print("ZONE 7");
  void scr_setcursor(22, 42);
  void scr_print("ZONE 8");
}
