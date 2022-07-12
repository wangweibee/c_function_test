#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

void foo(int x, int y, int z)

{

int a = x + y;
int b = y + z;
}


int main(int argc, char *argv[])

{
printf("fun name 1: %s\n", foo);
printk("fun name 2: %pf\n", foo);

void (*pf)(int x, int y, int z);
pf = foo;

printf("fun name 11: %s\n", pf);
printk("fun name 12: %pf\n", pf);

foo(100, 200, 300);

return 0;

}
