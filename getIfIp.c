
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>



int get_ip_from_if_name(char *if_name, char ip_addr[])
{
    if(if_name== NULL || ip_addr == NULL)
    {
        return 1;
    }
    int sockfd;
    struct ifreq req;
    struct sockaddr_in *host;

    if(-1 == (sockfd = socket(PF_INET, SOCK_STREAM, 0)))
    {
         perror( "socket" );
         return 1;
    }

    bzero(&req, sizeof(struct ifreq));
    strcpy(req.ifr_name, if_name);
    ioctl(sockfd, SIOCGIFADDR, &req);
    host = (struct sockaddr_in*)&req.ifr_addr;
    strcpy(ip_addr, inet_ntoa(host->sin_addr));
    close(sockfd);
    return 0;
}


void main ()
{
  char ip_addr[32] = {0};
  char *if_name = "enp15s0";
  
  get_ip_from_if_name(if_name, ip_addr);

  printf("ip is %s", ip_addr);
}
