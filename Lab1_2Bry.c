/*------------------------------------------------------------------------------
* Name:         Bryan Fernandez
* Section:      07
* Date:         Aug 22, 2017
* Instructor:   Kumar Sharshembiev
* Description:  Part 2: write a c program to count the number of digits, lower 
* case alphabetic characters, and upper case alphhabetic characters in a given string.
* If the string is "Hello CPE 325!"
* Output: Hello CPE325! Contains: 3 digits
*                                 4 upper case characters
*                                 4 lower case characters
------------------------------------------------------------------------------*/
#include "msp430.h"
#include "stdio.h"

int main()
{
  char string [50] = "Hello CPE 325!";
  
  int i = 0;                            //declarations
  int Upper = 0;
  int Lower = 0;
  int NumberCounter = 0;
  
  while(string[i] != '\0')              //While loop doesn't encounter null character
  {
    if(string[i] >= 'A' && string[i] <= 'Z')    //if value is between A and Z
    {
      Upper++;                                  //We have a capital letter
    }
    
    if(string[i] >= 'a' && string[i] <= 'z')    //if value is between a and z
    {
      Lower++;                                  //We have lowercase letter
    }
    
    if(string[i] >= '0' && string[i] <= '9')    //if value is between 0 and 9
    {
      NumberCounter++;
    }
    i++;                                        //Moves to the next letter
  }
  
  printf("Output: "); printf(string); printf(" Contains: %d digits", NumberCounter);
  printf("\n                                 %d upper case characters", Upper);
  printf("\n                                 %d lower case characters", Lower);
  
  return 0;
}
  
  
  
  