#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


void f(void)
{
   int* x = (int*)malloc(10 * sizeof(int));
   x[10] = 0;  //问题1: 数组下标越界
}                  //问题2: 内存没有释放

int main(void)
{
   f();

while(1)
{
    sleep(2);
}

   return 0;
}
