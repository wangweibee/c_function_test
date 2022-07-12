#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

static void get_pname_from_pid(int pid)
{
    char cmd_line[64] = {0};
    snprintf( cmd_line, 64, "ls -l /proc/%d", pid );

    FILE *pp = NULL;
    
    if( (pp = popen(cmd_line, "r")) == NULL )
    {
        printf("get_pname_from_pid: popen() error!\n");
        return;
    }
    
    char buf[256] = {0};
    while (fgets(buf, 255, pp) != NULL )
    {
        if ( strstr(buf, "exe ->") )
        {
            printf("%s\n", buf);
            break;
        }
    }

    pclose(pp);
}


static void get_proceed_info_from_pid(int pid)
{
    char cmd_line[64] = {0};
    snprintf( cmd_line, 64, "ps -ef | grep -w %d | grep -v grep", pid );

    FILE *pp = NULL;
    
    if( (pp = popen(cmd_line, "r")) == NULL )
    {
        printf("get_proceed_info_from_pid: popen() error!\n");
        return;
    }
    
    char buf[512] = {0};
    while (fgets(buf, 511, pp) != NULL )
    {
        printf("%s\n", buf);
    }

    pclose(pp);
}


#define TCP_CONNECT(a, b) a##b

int cha(int a, int b, int c)
{
   int res = &c - &a;
printf ("address: %d, %lu, %lu\n", res, &c, &a);

unsigned long int aa = &a;
unsigned long int cc = &c;

int ret = cc - aa;
printf ("cc - aa: %d, %lu, %lu\n", ret, aa, cc);
printf ("aa add %lu, cc add %lu\n", &aa, &cc);

return res;
}

void  main()
{
#if 0
  char str1[6] = "ab";

  int i = 0;
  int aa0 = 3;
  int aa1 = 5;

  for (i = 0; i < 2; i++)
  {
    printf ("%d\n", TCP_CONNECT(aa, 1));
  }
#endif
 ///extern int *parr;
get_pname_from_pid(12554);
get_proceed_info_from_pid(12554);

return;

 int a = 0;
 int b = 0;
 int c = 0;

cha(a, b, c);

///  printf ("finish: %d \n", parr);

 /***
 char a1 = 119;
 char a2 = 122;
 unsigned char a3 = 3;
 if (a1 + a2 > a1)
{
  printf ("finish: \n");
}
else
{
 printf ("no: \n");
}
***/
}

