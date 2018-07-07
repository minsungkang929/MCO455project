#include<hidef.h>
#include "derivative.h"

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
}
