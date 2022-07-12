#include<stdio.h>
#include <stdlib.h>

void function(int a, int b, int c)
{
    char buffer1[5];
    char buffer2[10];
    int *ret;
    ret = buffer1 + 12;
    (*ret) += 8;
}

int  main(int argc, char *argv[])
{
    int x;
    x = 0;
    function(1,2,3);
    printf("1: %d\n",x);

    x = 1;
    printf("2: %d\n",x);

    return 0;
}

