#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

void foo(int x, int y, int z)

{
printf("x = %d at [%p]\n", x, &x);

printf("y = %d at [%p]\n", y, &y);

printf("z = %d at [%p]\n", z, &z);

printf("&z - &x = %d\n", &z - &x);
}

int main(int argc, char *argv[])

{
foo(100, 200, 300);

return 0;

}
