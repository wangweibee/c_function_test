
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




void main ()
{
  char ip_addr[32] = "1.2.3.4";
  
  uint32_t ipn =  inet_addr(ip_addr);

  printf("ip is %s, ipn=0x%x", ip_addr, ipn);
}
