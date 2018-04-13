/*-------------------------------------------------------------------
* Program:      Calculate the factorial for first 15 integers
* Input:        None
* Output:       Factorials of integer numbers from 1 to MAXF
* Written by :  Aleksander Milenkovic
* Description:  This C code will calculate the factorial for several integers
				and print out the result in both int (16-bit) and
				long int types (32-bit), decimally and hexadecimally.
*---------------------------------------------------------------------*/
#include <msp430.h>
#include <stdio.h>

#define MAXF 16

int ifact(int);
long int lifact(int);

int main(void)
{
	// Stop watchdog timer to prevent time out reset
	WDTCTL = WDTPW + WDTHOLD;
	int i;
	int a;
	long int b;
	printf("( i)!   :  int-dec,  int-hex :   long int-dec,   long int-hex;\n");
	for (i = 1; i < MAXF; i++) {
		a = ifact(i);   // Call subroutins to do the caluclation
		b = lifact(i);

		printf("(%2d)!   : %8d, %8x : %14ld, %14lx;\n", i, a, a, b, b);
	}
	return 0;
}
