//Name: Bryan Fernandez
//Instructor: Sharshembiev
//Lab #: 07
//Date: 10/17/2017
//                MSP430xG4618                     SSEL1 SSEL0                 MC1     MC0
//             -----------------                    0     0     TACLK           0       0   Stop mode
//        /|\ |              XIN|-                  0     1     ACLK            0       1   Up mode
//         |  |                 | 32kHz             1     0     MCLK/SMCLK      1       0   Continuous mode
//         ---|RST          XOUT|-                                              1       1   Up/down mode
//
//FG4618 Board Demo - Real-time clock in Hyperterminal
//
//Decription: This program maintains real-time clock and sends time (10 times a second)
// to the workstation through a serial asychronous link (uart).
//This program displays the system clock in "sssss:tsec" format to Hyper Terminal.
//Instuctions: Set the following paramters in ht
//Port: COM1
//Baud rate: 19200
//Data bits: 8
//Parity: None
//Stop bits: 1
//Flow Control: None
//
//Port on 2013 Port on 4618
//P1.5         P3.3

//MSP430FG4618, print this message:  "Press SW1"
//When SW1 is pressed, display
//      " mm:ss:hh time elapsed since SW1 was pressed "
//    sprintf(Time, %05d:%01d", sec, tsec); 


#include <msp430xG46x.h>
#define SW1 BIT0&P1IN
#define SW2 BIT1&P1IN
#include <stdio.h>

//Declare variables
unsigned char hh = 0;                // 1 / 100 sec:   10^ -2
unsigned char ss = 0;                // seconds
unsigned char mm = 0;                // minutes
char Time[8];                              //" mm:ss:hh " time
char message[8];                        //beginning message
unsigned int a = 0;                     //P3.3 counter

//Declare Functions
void CountTime(void);
void UART_Initialize(void);
//Function Definitions
////////////////////////////////////////////////////////////////////////////////
void UART_Initialize(void) // USART in UART Mode 
{   
	P2SEL |= BIT4+BIT5; // Set UC0TXD and UC0RXD to transmit and receive data   
	UCA0CTL1 |= BIT0; // Software reset     control register
	UCA0CTL0 = 0; // USCI_A0 control register      //0 for asynchronous,  1 for synchronous mode
	UCA0CTL1 |= UCSSEL_2; // Clock source SMCLK   
	UCA0BR0=54; // 1048576 Hz / 19200       Baud rate control register
	UCA0BR1=0; //   
	UCA0MCTL=0x0A; // Modulation control register
	UCA0CTL1 &= ~BIT0; // Undo software reset 
}  

void CountTime(void)  //mm:ss:hh
{
    hh++;
    if(hh > 99)
    {
        hh = 0;
        ss++;   
    }
    if(ss > 59)
    {
        ss = 0;
        mm++;
    }
}

// Sends the time to the HyperTerminal 
void SendTime(void) 
{   
	sprintf(message, "Press SW1"); // prints time to a string   
	for(int i=0;i<8;i++) // Send character by character   
	{     
		while (!(IFG2 & UCA0TXIFG));     
		UCA0TXBUF = message[i];   
	}   
	while (!(IFG2 & UCA0TXIFG));   
	UCA0TXBUF = 0x0D; // Carriage Return 
} 
/*==============================================================================
//Main Program /////////////////////////////////////////////////////////////////
==============================================================================*/
void main(void)
{
      WDTCTL = WDTPW + WDTHOLD;
      
      UART_Initialize();             //DONE
      
      _EINT();
      P1IE |= BIT0;
      P1IES |= BIT0;
      P1IFG &= ~BIT0;
      P1IFG |= BIT1;
      P1IES |= BIT1;
      P1IFG &= ~BIT1;
                            //P3.3 on msp4618
      P3DIR |= BIT3;        //Port for communication
      P3OUT &= ~BIT3;       //Turn it off
      
                            //Configuring Timer B
      //P3DIR |= BIT4;
      P3SEL |= BIT4;       //Using TimerB3
      TB0CCTL3 = OUTMOD_4;
      TB0CCR0 = 5000;       //100 Hz or 0.01 seconds, using f = SMCLK / (2*CCR0)
      TB0CTL = TBSSEL_2 + MC_1 + ID_3;
      _BIS_SR(LPM0_bits + GIE);
      
      SendTime();    
}
////////////////////////////////////////////////////////////////////////////////
//SW1 Interrupt Service Routine
#pragma vector = PORT1_VECTOR   //Display time
__interrupt void PORT1_ISR(void)
{
    P1IFG &= ~BIT0;             //Clear flag
    P1IFG &= ~BIT1;
    if((SW1) == 0)
    {
        sprintf(Time, "%02d:%02d:%02d time elapsed since SW1 was pressed", mm, ss, hh);  //Prints time to string
      for(int i = 0; i < 8; i++)
        {
            while(!(IFG2 & UCA0TXIFG));
            UCA0TXBUF = Time[i];          
        }   
        while(!(IFG2 & UCA0TXIFG));
        UCA0TXBUF = 0x0D;               //Carriage Return
        
        hh = 0;                 //Reset counter back to 0
        ss = 0;
        mm = 0;
    }
    
    if((SW2) == 0)
    {
        a++;            //increment each time it is pressed
        
        if(a%2 == 0)     //If even, toggle on. If odd, toggle off
        {
            P3OUT &= BIT3;          //Toggle P3.3  (0000_1000)
        }
        else
        {
            P3OUT &= ~BIT3;             //Toggle off if it's odd time
        }
        //while(!(IFG2&UCA0TXIFG));               //Wait until can transmit     
      
    }
}
//Timer B Interrupt Service Routine
#pragma vector = TIMERB0_VECTOR
__interrupt void TIMERB_ISA(void)
{
    CountTime();           //Start counting time
    _BIC_SR_IRQ(LPM0_bits);     //Clear LMP0 bits from 0(SR)  
}









