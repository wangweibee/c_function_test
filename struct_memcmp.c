#include<stdio.h>
#include<string.h>

struct AAA
{
char type;
int cent;
};

int func(struct AAA *pGoods)
{
if (NULL == pGoods)
 return 0;

struct AAA tmp;
tmp.type = 1;
tmp.cent = 100;

if (0 == memcmp((char *)pGoods, (char *)&tmp, sizeof (struct AAA)))
{
printf("the result is 1\n");
return 1;
}
printf("the result is 0\n");
return 0;

}

int main(int argc, char *argv[])

{
struct AAA Goods;
 Goods.type = 1;
 Goods.cent = 100;

func(&Goods);
return 0;

}
