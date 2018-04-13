#include <stdio.h>

int main()
{
    int i;
    int diceRoll;
    
    for( i = 0; i <20; i++)
    {
      printf("%d\n", rand() );
    }
    return 0;
}
  
  





























/*#include <msp430xG46x.h>

int main()
{
      int n;
      int max;
      int num;
      int c;
      
      printf("Enter the number of random numbers you want\n");
      scanf("%d", &n):
        
      printf("Enter the max value of random number\n");
      scanf("%d", &max);
      
      printf("%d random numbers from 0 to %d are :-\n", n, max);
      
      randomize();
      
      for(c = 1; c <= n; c++)
      {
          num = random(max);
          printf("%d\n", num);
      }
      
      getch();
      return 0;
}  



#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c;
    int n;
    
    printf("Ten random numbers in [1,100]\n");
    
    for (c = 1; c <= 10; c++)
    {
      n = rand() % 100 + 1;
      printf("%d\n", n);
    }
    
    return 0;
}  */