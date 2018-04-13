/*Name: Bryan Fernandez   ======================================================
//Instructor: Sharshembiev
//Lab #: 07
//Date: 10/17/2017
//When P1.5 is high, toggle LED3. When it is low, stop toggling.
==============================================================================*/
#include <msp430x20x3.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           //Stop Watchdog timer, why not
    P1DIR |= 0x01;                      //P1.1 is on (0000_0001)  LED 3
    P1OUT = 0x01;                       //(0000_0001)
    
    for(;;)
    {
        while(BIT5&P1IN)               //P1.5 triggers high
        {
            P1OUT ^= 0x01;                  //Toggle LED3
            unsigned int i = 50000;         //Introduce noticeable delay
            do
            { i--;
              asm("NOP")
              asm("NOP")           
              asm("NOP")
              asm("NOP")
              asm("NOP")
              asm("NOP")
              asm("NOP")
            } while (i != 0);            
        }
    }
}







