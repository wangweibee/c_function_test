#include <sys/time.h>
#include<stdio.h>
#include<stdint.h>
#include <stdlib.h>
#include<math.h>
#include<string.h>




void  main()
{


int i = 0;

int len = 1024 * 1024 * 1024 / 8 * 2;

char * srcbuf = (char *)calloc(1, len);
char * dstbuf = (char *)calloc(1, len);

srcbuf[99] = 2;

    struct timeval tv;
    gettimeofday(&tv, NULL);
///    return (0LL + ITIME_TICKS) * tv.tv_sec
///        + tv.tv_usec * (ITIME_TICKS / (1000 * 1000));

for (i = 0; i < 100; i++)
{
  srcbuf[99] = 100 + i;
  memcpy(dstbuf, srcbuf, len);
}

struct timeval tv2;
    gettimeofday(&tv2, NULL);

uint64_t span = tv2.tv_sec * 1000 * 1000 + tv2.tv_usec - tv.tv_sec * 1000 * 1000 - tv.tv_usec;

 printf ("copy memory 2G * 100, spend time: %llds, %lldus \n", span / 1000 / 1000, span % (1000 * 1000));

}

