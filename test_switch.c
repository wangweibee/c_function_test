#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


void  main()
{
    unsigned int a = 6;
    int b = -20;
    int dd = (a+b> 6) ? 0 : 1;




    int ar[2][2]={{1},{2,3}};

    printf ("ar[0][0]=%d, ar[0][1]=%d, ar[1][0]=%d\n", ar[0][0], ar[0][1], ar[1][0]);

    char aa = 'a';

    int res = 0;
    
    switch (aa)
    {
        case'b':
            res = 1;
            break;
            
        case'a':
            res = 2;
            break;
    } 


    printf ("finish, res=%d\n", res);
}
