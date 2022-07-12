#include<stdio.h>
#include <stdlib.h>


void  main()
{
    int ret = 0;
    

    char ch2[] = {1, 2};
    short *sh1 = (short *)ch2;

    printf("char one=%d, two=%d\n", ch2[0], ch2[1]);
    printf("char to short=%d\n", *sh1);

    
    short sh_1 = 0x102;
    char *ch_2 = (char *)&sh_1;

    printf("char one=%d, two=%d\n", ch_2[0], ch_2[1]);
    printf("char to short=%d\n", sh_1);

}

