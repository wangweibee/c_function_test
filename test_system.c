#include<stdio.h>
#include <stdlib.h>


int  main(int argc, char *argv[])
{
    int ret = 0;
    

    char ch2[] = {1, 2};
    

//oprintf("char to short=%d\n", sh_1);

    //char *cmd_line = "grep 100% /home/isec_rule_up/res_tmp.txt";
        
    //char *cmd_line = "wget -P /home/ww/train.pdf http://www.winicssec.com112332/Uploads/File/filedownloads/2017training_lecture.pdf  2>/dev/null 1>&2";
    
   char cmd_line[512] = {0};
    
   //snprintf(cmd_line, 511, "%s 2>/dev/null 1>&2", argv[1]);
   
   snprintf(cmd_line, 511, "wget -P /home/ww/train.pdf %s 2>/dev/null 1>&2", argv[1]);

    printf("system call: %s\n",  argv[1]);

    int exec_status = system(cmd_line);

    if (exec_status < 0)
    {
        printf("system call fail: %s\n", cmd_line);
        return -1;
    }
    else if (!WIFEXITED(exec_status))
    {
        printf("system call failed, exception: %d|%s\n", exec_status, cmd_line);
        return -2;
    }
    else if (WEXITSTATUS(exec_status) != 0)
    {
        printf( "system call exit: %d|%d|%s\n", exec_status, WEXITSTATUS(exec_status), cmd_line);
        return -3;
    }

    printf("system call success!\n");

    return 0;
}

