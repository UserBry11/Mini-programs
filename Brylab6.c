/* 
Name: Bryan Fernandez

   A C program that initializes clock speed at 4 MHz.
   &= Bitwise AND asignment operator.   C &= 2 is same C = C & 2
   ^= Bitwise exclusive OR operator C ^= 2 is same C = C ^ 2
   |= Bitwise inclusive OR operator C |= 2 is same C = C | 2
   & is AND                            1 0001    
   | is OR                             2 0010
   ^ is XOR                            3 0011
   ~ is inverse                        4 0100
   << is shift LEFT                    5 0101
   >> is shift RIGHT                   6 0110
                                       7 0111
Initially, LED1 is blinking @ 2 Hz (0.25 secs on, 0.25 secs off)) LED2 is off.
While SW1 == 0, double blinking frequency of LED1. LED2 should be on.
While SW2 == 0, LED2 should blink at half the frequency. LED1 should be on.
While SW1 & SW2 == 0, both LEDs should blink alternately @ double the blinking freq.
When released, the clock speed is reset to 4 MHz, both LEDs on. Use interrupt for switches */

#include <msp430xG46x.h>
#define SW1 BIT0&P1IN
#define SW2 BIT1&P1IN
int b=0;                              //Global, setting my own flag
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD;           //stop watchdog
    FLL_CTL0 |= XCAP18PF;               //set capacitance to 8pF
    SCFI0 |= FN_4;                      //set DCO range to 2.8 - 26.6 MHz
    SCFQCTL = 121;                      // ( [0111_1001) +1] x 32768 = 4 MHz
    //P1DIR |= 0x32;                      //P1.1,P1.4,P1.5 to outputs
    //P1SEL |= 0x32;                      //output to MCLK, SMCLK, & ACLK
    
    P2DIR |= 0x06;                      // P2.1,P2.2 to output ports
    P2OUT = 0x04;                       //(0000_0100) turn on
    
    _EINT();                             //Enable interrupts    
    P1IE |= BIT0;                       //P1.0 interrupt enabled
    P1IES |= BIT0;                      //P1.0 hi/low edge
    P1IFG &= ~BIT0;                     //P1.0 IFG cleared
    
    P1IE |= BIT1;                       //P1.0 interrupt enabled
    P1IES |= BIT1;                      //P1.0 hi/low edge
    P1IFG &= ~BIT1;                     //P1.0 IFG cleared
    for(;;) //Infinite loop for blinking
    {
       P2OUT ^= 0x04;                     //LED1 is blinking 
       unsigned int i;
       i = 50000;       					// Delay 
       do 
       {
          i--;
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
       } while (i != 0);
       
  //------ If switch(es) are/is presssed -----------------------------------------
      if(b == 1)           //Only = 1 when it comes out of an interrupt
       {          //Enter another infinite loop
            for(;;)
            { 
              FLL_CTL0 |= XCAP18PF;               //set capacitance to 8pF
              SCFI0 |= FN_4;                     //Reset the range
              SCFQCTL = 121;                     //Reset the clocks to 4 MHz
           
              P2OUT = 0x06;                 //Turn on both LEDs
            }
       }  
    } 
}

//Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR (void)
{   
    P1IFG &= ~BIT0;                     //P1.0 IFG cleared
    P1IFG &= ~BIT1;                     //P1.1 IFG cleared
    P2OUT = 0x06;                       //Turn on both LEDs

//==============================================================================
      while((SW1) == 0)
      {                   //Want to double frequency to 8 MHz
          FLL_CTL0 |= DCOPLUS + XCAP18PF;      //Enable modulation and 8pF
          SCFI0 |= FN_4;                      //set DCO range to 2.8 - 26.6 MHz
          SCFQCTL = 121;                      // (121+1] x 32768 x 2 = 8 MHz
          P2OUT ^= 0x04;                  //Blink only LED1  (0000_0100)        (0000_ 0 LED1 LED2 0)

          unsigned int i = 50000;       					// Delay ^^^^^^  xor     00
          
           do 
           {
              (i--);
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
              asm("NOP");
           } while (i != 0);
           b = 1;                       //Turn on my flag
           if((SW2) == 0)
           {
             goto SWBoth;
           }
      }         
//=============================================================================     
      while((SW2) == 0)
      {           //Want half the frequency to 2 MHz
          FLL_CTL0 |= XCAP18PF;
          SCFI0 |= FN_2;
          SCFQCTL = 60;                    //(60 + 1) x 32768 = 2 MHz
          P2OUT ^= 0x02;                   //(0000_0010)  LED2 blink only. LED1 on
          unsigned int i = 50000;               // Delay 
       do 
       {
          (i--);
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
          asm("NOP");
       } while (i != 0);
       b = 1;                   //Turn on my flag
       if((SW1) == 0)
       {
         goto SWBoth;
       }
      } 

SWBoth:
  while((SW1)== 0 && (SW2)== 0)
  {
        
        FLL_CTL0 |= DCOPLUS + XCAP18PF;      //Enable modulation and 8pF
        SCFI0 |= FN_4;                      //set DCO range to 2.8 - 26.6 MHz
        SCFQCTL = 121;                      // (121+1] x 32768 x 2 = 8 MHz
        P2OUT ^= 0x06;                    //Blink both LEDs
        unsigned int i = 50000;       					// Delay 
     do 
     {
        (i--);
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
        asm("NOP");
     } while (i != 0);
  }  
    P2OUT &= ~0x06;                     //Turn off LEDs 
}
