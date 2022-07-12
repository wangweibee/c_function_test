#include<stdio.h>
#include<sys/time.h>
#include<time.h>
#include<string.h>


void  main()
{

    struct tm local_tm;
    char time_str[32] = {0};
    time_t now = time(NULL);
    localtime_r(&now, &local_tm);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S ", &local_tm);
    


    printf ("finish\n");
}
