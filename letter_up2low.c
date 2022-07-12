#include <ctype.h>
#include <stdio.h>
#include <string.h>


void main ()
{
char proto_type[] = "aBC d";


    int i = 0;
    char proto_sc[32 + 1] = {0};
    for (i = 0; i < strlen(proto_type); i++)
    {
        proto_sc[i] = tolower(proto_type[i]);
    }

printf("the result: %s", proto_sc);
}
