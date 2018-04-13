/*--------------------------------------------------------
*Name: Bryan Fernandez
*Date: Aug 11, 2017
*Instructor: Kumar
*Description: This program examins a sample string "Welcome to Assembly Programming @MSP430!". And 
*displays:

*# of total characters
*# of upper case vowels
*# of special characters (other than characters and digits)

*Set the port P1 to display the number of special characters,
*and port P2 to display the number of vowels.
*Store the total number of characters in R10.
*Total Characters: 40
*Total Uppercase Vowels: 1
*Total Special Characters: 6
*--------------------------------------------------------*/

#include "msp430.h"

                ORG 0FF00h                      //Starting address
                
Brystring       DB      "Welcome to Assembly Programming @MSP430!";
                //String placed on stack. Null character automatically added
                NAME    main                    //module name
                
                PUBLIC  main                    //make the main label visible
                
                ORG     0FFFEH
                DC16    main                    //set reset vector to 'main' label
                
                RSEG    CSTACK                  //predeclaration of segment
                RSEG    CODE                    //place program in 'CODE' SEGMENT
                
main:           MOV     #SFE(CSTACK),   SP      //set up stack
                MOV.W   #WDTPW+WDTHOLD, &WDTCTL;        //stop watchdog timer
                BIS.B   #0FFh,  &P1DIR                  //1111 or with P1, so it's on
                BIS.B   #0FFh,  &P2DIR                  //1111 or with P2, so it's on
                MOV.W   #Brystring,     R4              //load starting address
                                                  //of string into register R4
                                                  
                CLR.B   R8                      //Upper Case counter
                CLR.B   R9                      //Special character counter
                CLR.B   R10                     //Serves as the total counter
                
gnext:          MOV.B   @R4+,   R6              //Get new character
                CMP     #0,     R6              //Check for null character
                JEQ     endprog                 //go to end of program
                INC     R10                      //increment Total Char counter
////////////////////////////////////////////////////////////////////////////////                
                CMP     #'A',   R6              //Is it an uppercase A?
                JEQ     vowelcounter            //jump to vowel counter
                
                CMP     #'E',   R6              //Is it an uppercase E?
                JEQ     vowelcounter
                
                CMP     #'I',   R6
                JEQ     vowelcounter
                
                CMP     #'O',   R6
                JEQ     vowelcounter
                
                CMP     #'U',   R6
                JEQ     vowelcounter
                JMP     specialconfirm          //Jump to next section
                
vowelcounter:   INC     R8
                JMP     gnext                   //go to next character now
////////////////////////////////////////////////////////////////////////////////

specialconfirm: CMP     #41h,   R6              //41 is A in hex
                JGE     gnext                   //if greater or equal than A
                
                CMP     #40h,   R6              //40 is SPACE
                JEQ     increment                //if it's SPACE
                
                CMP     #30h,   R6              //30h and above are numbers
                JGE     gnext
                
increment:      INC     R9                      //IT'S A SPECIAL CHARACTER
                JMP     gnext                   //loop around
                
endprog:        MOV.B   R9,     &P1OUT          //special characters port
                MOV.B   R8,     &P2OUT          //vowerl characters port
                BIS.W   #LPM4,  SR              //LPM4
                NOP                             //required for debugger
                
                END
