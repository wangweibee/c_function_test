#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include <sys/vfs.h>
#include <stdio.h>
#include <mntent.h>
#include <sys/errno.h>


typedef struct DEV_MEM         //定义一个mem occupy的结构体
{
    unsigned long total;
    unsigned long used_rate;
}DEV_MEM;

DEV_MEM *get_devmem(DEV_MEM  *dev)        // get hard disk meeeage
{
    FILE * fp;
    int h=0;
    char a[80],d[80],e[80],f[80],buf[256]; 
    unsigned long c,b;
    fp=popen("df -m","r");
    fgets(buf,256,fp);

    unsigned long dev_total=0,dev_used=0;

    while(6==fscanf(fp,"%s %lu %lu %s %s %s",a,&b,&c,d,e,f))
    {
        dev_total+=b;
        dev_used+=c;
    }
    dev->total=dev_total;
    //dev->used_rate=dev_used/dev_total*100;
    dev->used_rate=dev_used; // /1024/1024

    pclose(fp);
    return dev;
}


void  main()
{
    DEV_MEM  *dev=(DEV_MEM *)malloc(sizeof(DEV_MEM));

    get_devmem(dev);
    printf ("Disk_used:%lu, Disk_Total:%lu\n", dev->used_rate, dev->total);

    free(dev);

}