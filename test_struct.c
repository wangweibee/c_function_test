#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<string.h>

struct AA{
    int a;
    char b;
    short c; 
}aa;

void main ()
{
 uint8_t str[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
 struct AA *bb = (struct AA *)str;
 printf("AA: a=0x%x, b=0x%x, c=0x%x\n\n", bb->a, bb->b, bb->c);

 bb = (struct AA *)(str+1);
 printf("AA: a=0x%x, b=0x%x, c=0x%x\n\n", bb->a, bb->b, bb->c);

 bb = (struct AA *)(str+2);
 printf("AA: a=0x%x, b=0x%x, c=0x%x\n\n", bb->a, bb->b, bb->c);

 bb = (struct AA *)(str+3);
 printf("AA: a=0x%x, b=0x%x, c=0x%x\n\n", bb->a, bb->b, bb->c);
}



