#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

typedef struct CPU_PACKED //定义一个cpu occupy的结构体

{
    char name[20];      //定义一个char类型的数组名name有20个元素
    unsigned int user;  //定义一个无符号的int类型的user
    unsigned int nice;  //定义一个无符号的int类型的nice
    unsigned int system;//定义一个无符号的int类型的system
    unsigned int idle;  //定义一个无符号的int类型的idle
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
}CPU_OCCUPY;

double cal_cpuoccupy(CPU_OCCUPY *o,CPU_OCCUPY *n)
{
    double od, nd;
    double id, sd;
    double cpu_use;

    //第一次(用户+优先级+系统+空闲)的时间再赋给od
    od = (double)(o->user + o->nice + o->system + o->idle + o->softirq + o->iowait + o->irq);
    //第二次(用户+优先级+系统+空闲)的时间再赋给od
    nd = (double)(n->user + n->nice + n->system + n->idle + n->softirq + n->iowait + n->irq);

    id = (double)(n->idle); //用户第一次和第二次的时间之差再赋给id
    sd = (double)(o->idle); //系统第一次和第二次的时间之差再赋给sd
    if((nd-od) != 0)
    {
        //((用户+系统)乖100)除(第一次和第二次的时间差)再赋给g_cpu_used
        cpu_use = 100.0 - ((id-sd)) / (nd-od) * 100.00;
    }
    else
    {
        cpu_use = 0;
    }

    return cpu_use;
}

void get_cpuoccupy(CPU_OCCUPY *cpust)
{
    FILE *fd;
    int n;
    char buff[256];
    CPU_OCCUPY *cpu_occupy;
    cpu_occupy = cpust;

    fd = fopen("/proc/stat", "r");
    fgets(buff, sizeof(buff), fd);
    sscanf(buff, "%s %u %u %u %u %u %u %u", cpu_occupy->name, &cpu_occupy->user, 
        &cpu_occupy->nice, &cpu_occupy->system, &cpu_occupy->idle, 
        &cpu_occupy->iowait, &cpu_occupy->irq, &cpu_occupy->softirq);

    fclose(fd);
}

double getCpuRate()
{
    CPU_OCCUPY cpu_stat1;
    CPU_OCCUPY cpu_stat2;
    double cpu;
    get_cpuoccupy((CPU_OCCUPY*)&cpu_stat1);
    sleep(1);

    //第二次获取cpu使用情况
    get_cpuoccupy((CPU_OCCUPY *)&cpu_stat2);

    //计算cpu使用率
    cpu = cal_cpuoccupy((CPU_OCCUPY*)&cpu_stat1, (CPU_OCCUPY*)&cpu_stat2);

    return cpu;
}

void  main()
{
    double cpu_rate = getCpuRate()
    printf ("cpu rate:%f\n", cpu_rate);

}
