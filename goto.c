#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdint.h>


void  main()
{
    char *arr_t[3] = {"select", "insert", "update"};

   int i = 0;
if (0 == i)
{
   for (i=0; i < 3; i++)
   {
    int res = strncasecmp(arr_t[i], "INSert ", 6);
    printf("res=%d\n", res);
    goto OBJECT;
   }
}
else
{
OBJECT:
  printf("cur idx=%d\n", i);

}
return;


}
