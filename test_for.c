#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

int  func(x)
{
   int countx = 0; 
  
    while(x)
    { 
        countx ++; 
        x = x&(x-1); 
    } 
     
    return  countx; 
}

void  main()
{
    int aa = 255;

    int res = func(aa);

    printf ("finish, res=%d\n", res);
}
