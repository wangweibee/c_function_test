#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


void  main()
{
char app_flow_stat[256] = "12abd";
///int type = 123;
///sprintf(app_flow_stat, "%d", type );


printf("%s\n", app_flow_stat);

int i = 0;
for (i = 0; i < 16; i++)
{
printf(" %02x", app_flow_stat[i]);
}

printf(" %02x", 1);

return;


}
