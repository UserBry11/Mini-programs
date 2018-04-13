/*------------------------------------------------------------------------------
* Name: Bryan Fernandez
* Lab assignment: 2 part 2
* Lab Section: 7
* Date: Aug 28, 2017                                          
* Instructor:                              
* Description: This program initializes an integer array, and two scalar
* values a and b.
*-----------------------------------------------------------------------------*/

#include "msp430.h"
#include "stdio.h"

int main (void)
{
    int bry1[5] = {1,2,3,4,5};
    int Answer[5] = {1,1,1,1,1};
    int scalarA = 2;
    int scalarB = 3;
    int partanswer;
    int i;
     
    printf("Array #1:     {"); 
        
        for(i=0; i < 5; i++)
        {
                printf("%d ", bry1[i]);     //Print out each element
        }

        printf("}\nOutput Array: {");
        //----------------------------------------------------------------------
	for(i=0; i < 5; i++)
	{      
		partanswer = bry1[i]*scalarA;  
                Answer[i] = partanswer + scalarB;
                printf("%d ", Answer[i]);//Prints out answer
        }        
        printf("}");        
        
        return 0;
}
