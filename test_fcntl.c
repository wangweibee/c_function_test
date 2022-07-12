#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <fcntl.h>
#include<errno.h>


#define TCP_CONNECT(a, b) a##b

#define ICARE_PID_FILE  "/var/run/icare111.pid"
#define IGW_LOCK_MODE  (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

static int icare_run_to_success(void)
{
    int fd;
    char buf[16];

    fd = open(ICARE_PID_FILE, O_RDWR | O_CREAT, IGW_LOCK_MODE);
    if (fd == -1)
    {
        printf("Can't open %s: %s", ICARE_PID_FILE, strerror(errno));
        return 0;
    }

    struct flock fl;
    fl.l_type = F_WRLCK;  /* write lock */
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0; /* lock the whole file */

    if (fcntl(fd, F_SETLK, &fl) == -1)
    {
        if (errno == EACCES || errno == EAGAIN)
        {
            printf( "%s already locked", ICARE_PID_FILE);
            close(fd);
            return 1;
        }
    }

    /* write pid */
    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);

///    close(fd);

    return 0;
}




void  main()
{
int ress = icare_run_to_success();

if (1 == ress)
{
printf ("is running successly!\n");
}
else
{
printf ("is running fail, ress=%d!\n", ress);
}

while(1)
{
sleep(5);
}

return;
}

