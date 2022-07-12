#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

int cha1()
{
   static int stat = 0;
   stat++;
printf ("ch1, stat: %d\n", stat);

return stat;
}

int cha2()
{
   static int stat = 0;
   stat++;
printf ("ch2, stat: %d\n", stat);

return stat;
}


void  main()
{
int i= 0;
for (i = 0; i < 9; i++)
{
int rr =  cha1();
printf ("rr:%d\n", rr);

rr =  cha2();
printf ("rr:%d\n", rr);
}
return;

}
