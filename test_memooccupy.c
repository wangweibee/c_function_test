#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#if 0
struct sysinfo
{
    long uptime;             /* Seconds since boot */
    unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
    unsigned long totalram;  /* Total usable main memory size */
    unsigned long freeram;   /* Available memory size */
    unsigned long sharedram; /* Amount of shared memory */
    unsigned long bufferram; /* Memory used by buffers */
    unsigned long totalswap; /* Total swap space size */
    unsigned long freeswap;  /* swap space still available */
    unsigned short procs;    /* Number of current processes */
    unsigned long totalhigh; /* Total high memory size */
    unsigned long freehigh;  /* Available high memory size */
    unsigned int mem_unit;   /* Memory unit size in bytes */
    char _f[20-2*sizeof(long)-sizeof(int)]; /* Padding for libc5 */
};
#endif


typedef struct sys_mem_info         //定义一个mem occupy的结构体
{
    unsigned long MemFree;
    unsigned long MemTotal;
}SysMemInfo;


SysMemInfo *GetHostMemInfo(SysMemInfo *memInfo)
{
    if (NULL == memInfo)
      printf("GetMemInfo: malloc SysMemInfo Struct error");

    struct sysinfo tmp;
    int ret = 0;
    ret = sysinfo(&tmp);
    
    if (ret == 0) 
    {		
        memInfo->MemFree  = (unsigned long)tmp.freeram/(1024*1024);
        memInfo->MemTotal = (unsigned long)tmp.totalram/(1024*1024);
    } 
    else 
    {
        printf("GetMemInfo: sysinfo() error");
    }

    return memInfo;
}



void  main()
{
    SysMemInfo *memInfo = (SysMemInfo *)malloc(sizeof(SysMemInfo));

    GetHostMemInfo(memInfo);
    printf ("MemFree:%u, MemTotal:%u\n", memInfo->MemFree, memInfo->MemTotal);

    free(memInfo);

}