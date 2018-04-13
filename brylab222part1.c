/*--------------------------------------------------------
* Name: Bryan Fernandez                    
* Lab: 2, Part 1                
* Section:     7                     
* Date: Aug, 29 2017
* Instructor:                         
* Description: This program has printf functions that print   
* sizes and ranges of char, short int, int, long int,    
* unsigned int, unsinged long int, float and double.
*--------------------------------------------------------*/

#include "msp430.h"
#include "stdio.h"
#include "limits.h"   //Shows and defines limits for variables or data types that cannot be exceeded
#include "float.h"    //Provides the limits for float and double types that cannot be exceeded

int main(void)
{   
  /*Sizes ( 1 )
  character: char
  (add additional sizes here)
  
  Ranges: (min, max)
  character: (0, 255)
  (add additional ranges here)*/
  
  
  
  
   printf("Datatype--Size(in bytes)---Ranges (min, max)\n\n");
	//Prints Header 
   printf("char :        %d            (%d, %d) \n", sizeof(char), CHAR_MIN, CHAR_MAX); 
	//%d is a specifier for type integer
	//Prints size and range for interger type. Sizeof() gives size of type
	//Macro CHAR_MIN defines minimum value for type char
	
   printf("\nshort int :   %d            (%hd, %hd)\n", sizeof(short int), SHRT_MIN, SHRT_MAX);    
	//We are going to have length l and specifier d for short int
	//MIN and MAX provide the minimum values for data type short int
	
   printf("\nint:          %d            (%d, %d)\n", sizeof(int), INT_MIN, INT_MAX);
    //Simply print size and range of int type
   
   printf("\nlong int:     %d            (%ld, %ld)\n", sizeof(long int), LONG_MIN, LONG_MAX);
    //We use length l for long integer type
    //Macro LONG_MIN defines miminum value for type long int
   
   printf("\nunsigned int: %d            (0, %u)\n", sizeof(unsigned int),UINT_MAX);
    //We use specifier u for unsigned integer type
    //Macro for unsigned integer max value
   
   printf("\nunsigned lont int:%d        (0, %lu)\n", sizeof(unsigned long int), ULONG_MAX);
    //We use length l and specifier u for usinged long integer type
    //Macro for unsigned long integer max
   
   printf("\nfloat:        %d            (%4.3e, %4.3e)\n", sizeof(float), FLT_MIN, FLT_MAX);
    //We use specifier e for scientific notation for floating point type
    //We use 4.3 to specify width of 4 and a precision of 3 past the decimal point
   
   printf("\ndouble:       %d            (%4.3e, %4.3e)\n", sizeof(double), DBL_MIN, DBL_MAX);
	//We also use specifier f for double float types
	
	return 0;
}
