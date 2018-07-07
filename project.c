#include<hidef.h>
#include "derivative.h"
void lcd_print(unsigned char input[40]);         //This function will allow you to send text to the LCD sreen.
                                                    example:
                                                    lcd_print("Hello World!");

void lcd_write(volatile unsigned char data);    //This function will take a two digit hex value,
                                                  and display it on the LCD screen. It does this
                                                  by converting each of the hex digits to its
                                                  ASCII equivalent value 

int main(void)
{
  SOPT_COPE = 0;
  SCI28DH = 0x00;
  SCI28DL = 0x82;
  SCI2C2 = 0x0c;
  for(;;)
  {
    while((SCI251 & 0x20)! = 0x20);
    while((SCI251 & 0x80)! = 0x80);
    SCI2D = SCI2D;
    LEDG = SCI2D;
  }

void lcd_print(unsigned char input[40])
{
  lcd_print("");
}
                                                    
void lcd_write(volatile unsigned char data)
{
  
}
