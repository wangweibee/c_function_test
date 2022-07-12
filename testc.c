///#include <stdio.h>
///#include <stdlib.h>
///#include <string.h>
//#include <stdint.h>
#include <inttypes.h>

void main()
{
///int arr[2][2] = {{1},2,3};
printf("long's size:%d\n",sizeof(long) );
///printf("(00)=%"PRId32",((01)=%d,(10)=%d,(11)=%d\n", arr[0][0], arr[0][1], arr[1][0], arr[1][1]);
///return;

struct A{};
printf("%d\n", sizeof(struct A));
///return;

    char bb[4] = {"22"};
    char cc[3] = "33";
    char dd[2] = {};
    printf("sizeof(bb)=%d,sizeof(cc)=%d,sizeof(dd)=%d\n", sizeof(bb), sizeof(cc), sizeof(dd));
    printf("(bb)=%s,(cc)=%s,(dd)=%s\n", (bb), (cc), (dd));
    printf("(bb)=%p,(cc)=%p,(dd)=%p\n", (bb), (cc), (dd));
    dd[0] = '4';
    printf("sizeof(bb)=%d,sizeof(cc)=%d,sizeof(dd)=%d\n", sizeof(bb), sizeof(cc), sizeof(dd));
    printf("(bb)=%s,(cc)=%s,(dd)=%s\n", (bb), (cc), (dd));
    printf("(bb)=%p,(cc)=%p,(dd)=%p\n", (bb), (cc), (dd));
}
