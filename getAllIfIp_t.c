
#include <fcntl.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/prctl.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <limits.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if_arp.h>
#include <linux/sockios.h>
#include <linux/netlink.h>

///#include <sys/ioctl.h>
///#include <net/if.h>

struct rtnl_handle
{
    int fd;
    struct sockaddr_nl local;
    struct sockaddr_nl peer;
    unsigned int  seq;
    unsigned int  dump;
};

const char *rt_addr_n2a(int af, int len, const void *addr)
{
    static char buf[256];

    switch (af)
    {
    case AF_INET:
    case AF_INET6:
        return inet_ntop(af, addr, buf, 256);
    case AF_PACKET:
        return ll_addr_n2a(addr, len, ARPHRD_VOID, buf, 256);
    case AF_BRIDGE:
    {
        const union {
        struct sockaddr sa;
        struct sockaddr_in sin;
        struct sockaddr_in6 sin6;
        } *sa = addr;

        switch (sa->sa.sa_family)
        {
        case AF_INET:
            return inet_ntop(AF_INET, &sa->sin.sin_addr, buf, 256);
        case AF_INET6:
            return inet_ntop(AF_INET6, &sa->sin6.sin6_addr, buf, 256);
        }
    }
    default:
        return "???";
    }
}

#define	TAILQ_INIT(head) do {						\
	(head)->tqh_first = NULL;					\
	(head)->tqh_last = &(head)->tqh_first;				\
} while (0)

#define TAILQ_FOREACH(var, head, field)					\
	for((var) = TAILQ_FIRST(head);					\
	    (var) != TAILQ_END(head);					\
	    (var) = TAILQ_NEXT(var, field))


void if_addr_list_destroy(if_addr_list_t *addr_list)
{
    if_addr_t *ifaddr, *tmp;

    TAILQ_FOREACH_SAFE(ifaddr, addr_list, next, tmp)
    {
        TAILQ_REMOVE(addr_list, ifaddr, next);
        free(ifaddr);
    }
}


int rtnl_open(struct rtnl_handle *rth)
{
    int namelen, ret;
    int sndbuf_len = 32768;
    int rcvbuf_len = NL_RCV_BUF_SIZE;

    rth->fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE);
    if (rth->fd < 0)
    {
        printf("Can't open netlink socket: %s", safe_strerror(errno));
        return -1;
    }

    if (setsockopt(rth->fd, SOL_SOCKET, SO_SNDBUF, &sndbuf_len, sizeof(sndbuf_len)) < 0)
    {
        printf("set SO_SNDBUF failed");
        return -1;
    }
    if (setsockopt(rth->fd, SOL_SOCKET, SO_RCVBUF, &rcvbuf_len, sizeof(rcvbuf_len)) < 0)
    {
        printf("set SO_RCVBUF failed");
        return -1;
    }

    rth->local.nl_family = AF_NETLINK;
    rth->local.nl_groups = 0;

    /* Bind the socket to the netlink structure for anything. */
    ret = bind(rth->fd, (struct sockaddr *)&rth->local, sizeof(rth->local));
    if (ret < 0)
    {
        printf("Can't bind netlink socket: %s\n", safe_strerror(errno));
        close (rth->fd);
        return -1;
    }

    /* multiple netlink sockets will have different nl_pid */
    namelen = sizeof(rth->local);
    ret = getsockname(rth->fd, (struct sockaddr *)&rth->local, (socklen_t *)&namelen);
    if (ret < 0 || namelen != sizeof(rth->local))
    {
        printf("Can't get netlink socket name: %s\n", safe_strerror(errno));
        close (rth->fd);
        return -1;
    }

    rth->seq = 0;

    return 0;
}


int if_addr_list_get(if_addr_list_t *addr_list)
{
    struct rtnl_handle rth;

    if (!addr_list)
    {
        return -1;
    }

    memset(&rth, 0, sizeof(rth));
    if (rtnl_open(&rth) < 0)
    {
        printf("[NET] open netlink failed");
        return -1;
    }

	struct nlmsg_chain linfo = { NULL, NULL};
	struct nlmsg_chain ainfo = { NULL, NULL};
	struct nlmsg_list *l;
    if_addr_t *ifaddr;

    if (ip_link_list(&rth, &linfo) != 0)
    {
        goto out;
    }

    if (ip_addr_list(&rth, &ainfo) != 0)
    {
        goto out;
    }

    for (l = linfo.head; l; l = l->next)
    {
        struct nlmsghdr *nlh = &l->h;
        struct ifinfomsg *ifi = NLMSG_DATA(nlh);
        struct nlmsg_list *entry = ainfo.head;
        uint32_t ip;

        for ( ; entry; entry = entry->next)
        {
            struct nlmsghdr *n = &entry->h;
            struct ifaddrmsg *ifa = NLMSG_DATA(n);

            if (n->nlmsg_type != RTM_NEWADDR)
                continue;

            if (n->nlmsg_len < NLMSG_LENGTH(sizeof(*ifa)))
                return -1;

            if (ifa->ifa_index != ifi->ifi_index)
                continue;

            ip = parse_addr_info(n);
            if (ip == 0)
                continue;

            ifaddr = calloc(1, sizeof(*ifaddr));
            if (ifaddr)
            {
                ifaddr->ip = ip;
                TAILQ_INSERT_TAIL(addr_list, ifaddr, next);
            }
        }
    }

out:
	free_nlmsg_chain(&ainfo);
	free_nlmsg_chain(&linfo);
    rtnl_close(&rth);

    return 0;
}



int main(void)
{
    if_addr_list_t al;
    const char *ipaddr;

    memset(&al, 0, sizeof(if_addr_list_t));
    TAILQ_INIT(&al);

    if (if_addr_list_get(&al) == 0)
    {
        if_addr_t *ifaddr;

        TAILQ_FOREACH(ifaddr, &al, next)
        {
            if (ifaddr->ip == ALERT_IPADDR_IGNORE)
                continue;

            ipaddr = rt_addr_n2a(AF_INET, 4, &ifaddr->ip);
            printf("local interface ip %s\n", ipaddr);            
        }
    }

    if_addr_list_destroy(&al);

    return 0;
}



