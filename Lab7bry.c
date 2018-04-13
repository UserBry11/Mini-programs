//      1 0001   6 0110     11 1011
//      2 0010   7 0111     12 1100
//      3 0011   8 1000     13 1101
//      4 0100   9 1001     14 1110   
//      5 0101  10 1010     15 1111
//Write a C program that uses Timer B to play note G (783.99 Hz)
//at the piezo-buzzer. All LEDs are off. 
//When SW1 is pressed, LED4 blinks @ 1 Hz frequency. Use WDT ISR.
//you need to configure WDT interval inside Port1 ISR and only when SW1
//is pressed.
//When SW1 is released, everything goes back to normal.
//When SW2 is pressed, the buzzer plays D (587 Hz).
//Bonus: Timer A ISR to alternately blink LED2 and LED1 at 1 Hz
//Throughout execution of the program.
//When  SW1  is  pressed,  LED4 
//When SW1 == 0, LED4 should  blink  at  1Hz  frequency.  Use  WDT  ISR  for  this  operation  (You  would 
//need  to  configure  WDT  interval  inside  Port1  ISR  and  only  when  SW1  is 
//pressed).  
//                 MSP430xG461x                     SSEL1 SSEL0    u             MC1     MC0
//             -----------------                    0     0     TACLK           0       0   Stop mode
//        /|\ |              XIN|-                  0     1     ACLK            0       1   Up mode
//         |  |                 | 32kHz             1     0     MCLK            1       0   Continuous mode
//         ---|RST          XOUT|-                                              1       1   Up/down mode
//            |                 |
//            |                 |
//            |         P3.5/TB0|--> 32768/ACLK     LED4 = P5.1
//            |                 |

#include <msp430xG46x.h>
#define SW1 BIT0&P1IN
#define SW2 BIT1&P1IN
void main(void)
{
  WDTCTL = WDTPW + WDTHOLD;             //Stop WDT 
  _EINT();              //Enable interrupts
  P1IE |= BIT0;         //P1.0 interrupt enabled
  P1IES |= BIT0;        //P1.0 hi/low edge
  P1IFG &= ~BIT0;       //P1.0 IFG cleared
  P1IE |= BIT1;
  P1IES |= BIT1;
  P1IFG |= ~BIT1;
  P5DIR |= 0x02;        //P5.1 as output 
  P5OUT = 0x00;         //clear LED4     (0000_0010)
  P3DIR |= BIT5;        //P3.5 set as output
  P3SEL |= BIT5;        //Use special mode, lucky since they are multiplexed together
  TB0CCTL4 = OUTMOD_4;  //We use 4 because we want to toggle
  TB0CCR0 = 638;        //CCR0 = SMCLK / (2 * 784)   This is for G5 (783.99 Hz)
  TB0CTL = TBSSEL_2 + MC_1;     //Use SMCLK and UP mode
  _BIS_SR(LPM0_bits + GIE);     //Low Power Mode 0 w/ interrupts  
}
//Port 1 interrupt service routine
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void)
{
  P1IFG &= ~BIT0;             //Clear both flag
  P1IFG &= ~BIT1;       
  if((SW1)==0)                  //For LED4
  {
    WDTCTL = WDT_ADLY_1000;       //1s interval timer
    IE1 |= WDTIE;                 //Enable WDT interrupt
  }
  while((SW2)==0)                   //For D5 (587 Hz)
  {
    TB0CCTL4 = OUTMOD_4;
    TB0CCR0 = 852;                     //CCR0 = MCLK / (2 * 587)
    TB0CTL = TBSSEL_2 + MC_1;
    _BIS_SR(LPM0_bits + GIE);
  }
  TB0CCR0 = 638;                //When SW2 is released
}  
#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer(void)
{
  P5OUT ^= 0x02;        //Toggle LED4 
  if((SW1)==1)
  {
    P5OUT &= ~0x02;
  }
}