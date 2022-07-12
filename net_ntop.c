#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <arpa/inet.h>


#define UINT32 unsigned int

void  main()
{
    char ip_string[32] = "1.2.3.4";
    //char *ip_string = (char *)calloc(32, sizeof(char));
    UINT32 ip = 0;

    strcpy(ip_string, "1.2.3.4");



    if (inet_pton(AF_INET, ip_string, (void*)&ip) != 1)
    {
        printf ("ip=0x%x\n", ip);

        //free(ip_string);
        return;
    }

///    printf ("ip=0x%x\n", ip_string);
///    printf ("ip=0x%llx\n", ip_string);
///    printf ("ip=%p\n", ip_string);

    //free(ip_string);
    //ip_string = NULL;

    UINT32 t_ip = ntohl(ip);    
    printf ("ip=0x%x, t_ip=0x%x\n", ip, t_ip);

    struct in_addr ipv4 = {0};
    ipv4.s_addr = ip;
    char *src = NULL;
    src = inet_ntoa(ipv4);

    printf ("string ip=%s\n", src);

    uint32_t clientIp = 0;
    clientIp = ntohl(inet_addr(src));

    printf ("ipv4=0x%x, ipv4.s_addr=0x%x\n", ipv4, ipv4.s_addr);
    printf ("clientIp=0x%x\n", clientIp);

    return;

}
