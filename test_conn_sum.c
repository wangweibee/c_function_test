#include <stdio.h>
#include <string.h>


int cmd_exec_func(char *cmd_buf, char *cmd_res)
{
    FILE *pp;
    if(cmd_buf == NULL)
    {
        return -1;
    }

    if( (pp = popen(cmd_buf, "r")) == NULL )
    {
        printf("CMD Failed : %s.", cmd_buf);
        return -1;
    }
    if(cmd_res)
    {
        fgets(cmd_res, sizeof(cmd_res), pp);
    }
    
    pclose(pp);
    printf(" %s.", cmd_buf);
    return 0;
}

static int get_conn_sum(int *conn_sum)
{
    char cmd_buf[128] = "cat /proc/net/nf_conntrack | wc -l";
    int ret = 0;

    char rst_buf[128] = {0};
    ret = cmd_exec_func(cmd_buf, rst_buf);

    if (0 == ret)
    {
        *conn_sum = atoi(rst_buf);
    }

    return 0;
}

void main ()
{
int conn_sum = 0;
int res = get_conn_sum(&conn_sum);

printf("the conn num:  %d.", conn_sum);

}
