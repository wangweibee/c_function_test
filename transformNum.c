#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


# define TCP_CONNECT(a, b) a##b

void  main()
{
unsigned char uc1 = 1;
unsigned char uc2 = 2;

unsigned int ui = 3;

int res0 = uc1 < ui;
int res1 = uc1 - uc2 < uc1;
int res2 = uc1 - uc2 > ui;

printf ("(uc1 < ui)=%d\n, (uc1 - uc2 < uc1)=%d\n, (uc1 - uc2 > ui)=%d\n", res0, res1, res2);


unsigned char uc3 = 139;
unsigned char uc4 = 149;
int res3 = uc3 + uc4 > uc4;
int res4 = uc4 * 2 > uc4;

printf ("(uc3 + uc4 > uc4)=%d\n, (uc4 * 2 > uc4)=%d\n", res3, res4);
}


