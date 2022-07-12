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


int get_localip(const char * eth_name, char *local_ip_addr)
{
	int ret = -1;
    register int fd, intrface;
    struct ifreq ifr[32];
    struct ifconf ifc;
 
    if (local_ip_addr == NULL || eth_name == NULL)
	{
        return ret;
	}
	if ((fd=socket(AF_INET, SOCK_DGRAM, 0)) > 0)
	{
		ifc.ifc_len = sizeof ifr;
		ifc.ifc_buf = (caddr_t)ifr;
		if (!ioctl(fd, SIOCGIFCONF, (char*)&ifc))
		{
			intrface = ifc.ifc_len / sizeof(struct ifreq);
			while (intrface-- > 0)
			{
				if (!(ioctl(fd, SIOCGIFADDR, (char*)&ifr[intrface])))
				{
					if(strcmp(eth_name, ifr[intrface].ifr_name) != 0)
					{
						ret = 0;
	sprintf(local_ip_addr, "%s", inet_ntoa(((struct sockaddr_in*)(&ifr[intrface].ifr_addr))->sin_addr));
                        printf("ip is %s\n", local_ip_addr);
						///break;

					}
				}
			}
		}
	}
	if (fd > 0)
	{
		close(fd);
	}
    return ret;
}
 

void main ()
{
  char ip_addr[32] = {0};
  char *if_name = "lo";
  
  ///get_ip_from_if_name(if_name, ip_addr);
get_localip(if_name, ip_addr);
  printf("ip is %s", ip_addr);
}
