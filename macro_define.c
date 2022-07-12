#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdint.h>

void test_fun()
{
int aa = PARAM_MAX_LEN + 1;
printf("aa=%d\n", aa);
}

void  main()
{
#define PARAM_MAX_LEN    (64)

    char *arr_t[3] = {"select", "insert", "update", "delete"};

    int len = sizeof("select");
printf("len=%d\n", len);

   int i = 0;
   for (i=0; i < 3; i++)
{
    int res = strncasecmp(arr_t[i], "INSert ", 6);
    printf("res=%d\n", res);
}
return;


}
