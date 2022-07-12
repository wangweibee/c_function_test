#include <sys/time.h>
#include<stdio.h>
#include <math.h>
#include<string.h>
#include <stdint.h>

#define IPV6_32BIT_SEG_NUM 4


typedef struct
{  
uint32_t x[IPV6_32BIT_SEG_NUM];
} ip6_t;


static int mk_mask6(int prefixlen)
{
ip6_t mask;
uint32_t ones = ~((uint32_t) 0);
///int32_t tmpt = (ones >> 0) << 0;
///printf("tmpt=%u", tmpt);

int pivot = prefixlen / 32;
int shift = 32 - (prefixlen % 32);

int i = 0;
for ( i=0; i<pivot && i<IPV6_32BIT_SEG_NUM; i++)
{
mask.x[i] = ones;
}

if (pivot<IPV6_32BIT_SEG_NUM)
{
///mask.x[pivot] = (ones >> shift) << shift;
shift = (prefixlen % 32);
///mask.x[pivot] = pow(2,32) - pow(2, 32 - shift);
mask.x[pivot] = pow(2,32) - pow(2, 32 - shift);;
}

for (i = pivot+1; i<IPV6_32BIT_SEG_NUM; i++)
{
mask.x[i] = 0;
}


for (i=0; i<IPV6_32BIT_SEG_NUM; i++)
{
printf("idx:%d: mask:%u\n", i, mask.x[i]);
}

return 0;
}


void  main()
{
int prefixlen = 0;

mk_mask6(prefixlen);
}

