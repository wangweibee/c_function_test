#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>

#include <gperftools/tcmalloc.h>
#include "gperftools/malloc_extension_c.h"


void  main()
{
printf("start\n");
sleep(5);

 printf("will allocate\n");
 char *ptr[256] = {NULL};
 int i = 0;
 for (i = 0; i < 100; i++)
 {
  ptr[i] = malloc(1024 * 1024 * 100 * sizeof(char));
  memset(ptr[i], 3, 1024 * 1024 * 100 );
 }  

printf("allocate finish\n");
 sleep(3);

printf("will free\n");
 for (i = 0; i < 100; i++)
 {   
     free(ptr[i]);
 }
 MallocExtension_ReleaseFreeMemory();

printf("free finish\n");
 
 while(1)
 {
  sleep(1);
 }




}
