#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdint.h>

typedef struct
{  
uint16_t x[8];
} ip6_t;


static int mk_mask6(int prefixlen)
{
ip6_t mask;
uint16_t ones = ~((uint16_t) 0);

int pivot = prefixlen / 16;
int shift = 16 - (prefixlen % 16);

int i = 0;
for ( i=0; i<pivot && i<8; i++)
{
mask.x[i] = ones;
}

if (pivot<8)
{
mask.x[pivot] = (ones >> shift) << shift;
}

for (i = pivot+1; i<8; i++)
{
mask.x[i] = 0;
}


for (i=0; i<8; i++)
{
printf("idx:%d: mask:%u\n", i, mask.x[i]);
}

return 0;
}


void  main()
{
int prefixlen = 31;

///printf ("the num:%d\n", num);
mk_mask6(prefixlen);
//
//
}
//
