#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


# define TCP_CONNECT(a, b) a##b

int cha(int a, int b, int c)
{
   int res = &c - &a;
printf ("address: %d, %p, %p\n", res, &c, &a);

unsigned long int aa = &a;
unsigned long int cc = &c;

int ret = cc - aa;
printf ("cc - aa: %d, cc=0x%lx, aa=0x%lx\n", ret, cc, aa);
printf ("cc=address 0x%lx, aa=address 0x%lx\n", &cc, &aa);

return res;
}

struct ss
{};

void  main()
{
    char bb[] = {"22"};
    char cc[] = "33";
    char dd[] = {};
    printf("sizeof(bb)=%d,sizeof(cc)=%d,sizeof(dd)=%d\n", sizeof(bb), sizeof(cc), sizeof(dd));

struct ss s1;
printf("sizeof(ss)=%d, sizeof(s1)=%d\n",  sizeof(struct ss),sizeof(s1));
    return;



int a = 0;
int b = 0; 
int c=0;

int rr =  cha(a, b, c);
printf ("rr:%d\n", rr);
return;


int arrr[] = {11,22,33,};
int num = sizeof(arrr) / sizeof(int);

printf ("the num:%d\n", num);


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
#if 0
 int a = 1;
 inr arr[8] = {1,2,3,4,5,6,,7,8};
 int b[2][2][2];
 int c = 2;

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
#endif

}

