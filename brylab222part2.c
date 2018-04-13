/*--------------------------------------------------------
* Name: Bryan Fernandez
* Lab assignment: 2 part 2
* Lab Section: 7
* Date: Aug 28, 2017                                          
* Instructor:                              
* Description: This program will initialize 2 integer 
* arrays. The program will then calculate the dot product
* of the two arrays and output input and output arrays.
*--------------------------------------------------------*/

#include "msp430.h"
#include "stdio.h"

int main (void)
{
	int bry1[5] = {1, 2, 3, 4, 5};      //Array of 5 elements
	int bry2[5] = {0, 1, 2, 3, 4};      //Array of 5 elements
        int i;                              //Counting variable		
	int answer = 0;                     //Contains answer
        
        //----------------------------------------------------------------------
        //This section we use for loops to print out each array element
        printf("Array #1: "); 
        
        for(i=0; i < 5; i++)
        {
                printf("%d ", bry1[i]);     //Print out each element
        }
        
        printf("\nArray #2: ");             //Beginning of next line
        
        for(i=0; i < 5; i++)
        {
                printf("%d ", bry2[i]);     //Print out each element
        }
        
        //Calculate and print out dot product
        //----------------------------------------------------------------------
	for(i=0; i < 5; i++)
	{      
		answer += bry1[i]*bry2[i];  //Calculates dot product
        }        
                
        printf("\nDot Product: %d", answer);//Prints out answer
        
	return 0;
}
