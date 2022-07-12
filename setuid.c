#include<fcntl.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
void err_exit(char *fmt,...);
int main(int argc,char *argv[])
{
    uid_t ruid,euid,suid;
 
    printf("Before:\n");
    if(-1 == getresuid(&ruid,&euid,&suid))
      return 0;

    printf("real:%d\teffective:%d\tset-user:%d\n",ruid,euid,suid);
// /***
    setuid(1003);
    printf("After:\n");
    if(-1 == getresuid(&ruid,&euid,&suid))
      return 0;

    printf("real:%d\teffective:%d\tset-user:%d\n",ruid,euid,suid);
//***/ 
    umask(0);   /// for chmod,mkdir,open
    int  file_fd = open("/home/ww/test/database/newfile", O_CREAT | O_TRUNC | O_NOFOLLOW | O_WRONLY,
               0766 );  ///0644

    if (file_fd == -1) 
    {
    printf("open failed\n");
return -1;
    }
    printf("open success");

    return 0;
}

