#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include <stdint.h>


void  main()
{

int len1 = 0;
uint64_t flow[7] = {0};
char str1[] = "abcde";

flow[0] = str1;

printf("1, %llu\n\n", flow[0]);

///char *t_st = (char *)flow[0];
printf("2, %s\n\n", flow[0]);

int tt[]={1, 2, 3};
flow[0] = tt;
int *p_tt = (int *)flow[0];
printf("3, %d\n\n", p_tt[0]);

}
