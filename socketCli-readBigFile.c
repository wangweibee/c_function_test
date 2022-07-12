/// ./socketcli "2.2.2.97" 11988

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


#define  I_R_OK        0  //作为函数的返回值
#define  I_R_ERROR    -1  //作为函数的返回值
#define  I_R_SOCKET_ERROR -2
#define  I_R_ERROR_EAGAIN -3


//#define DRPS_LISTEN_PORT 32345   /* drps 系统监听端口 */

#define MAX_HEADER_LEN 8
#define MAX_TX_PKTDATA_LEN 1024 * 8
#define RESPONSE_PKTDATA_LEN 128


//#define FILE_NAME "emerging-sql.rules"
#define FILE_NAME "testtt"


static int recv_specific_length_pkts(int sockfd, char *ptr, int len)
{
    int num = len;
    int ret = 0;
    
	while (num > 0)
	{
	    ret = read(sockfd, ptr, num);
     	if (ret == -1) 
		{
		    // 非阻塞下没有这个信号
      		if (errno == EINTR)
      		{
      			printf("$.");
       			ret = 0;
      		}
      		// 在这里就当作是该次事件已处理完.
            else if(errno == EAGAIN)
            {
      			printf("*.");
       			ret = 0;
            }
      		else // if (errno == ECONNRESET) 
      		{
                printf("%s:read payload return error(%d-%s).\n", __func__, errno, strerror(errno));
                
                if (-1 == close(sockfd))
                {
                    printf("%s:close return error(%s).\n", __func__, strerror(errno));
                }
                
				return I_R_SOCKET_ERROR;
      		}
     	}
     	else if (ret == 0)
     	{
            printf("%s:read return 0, the socket be closed.\n", __func__);
            
            if (-1 == close(sockfd))
            {
                printf("%s:close return error(%s).\n", __func__, strerror(errno));
            }
            
            return I_R_SOCKET_ERROR;
     	}
     	
     	ptr += ret;
     	num -= ret;
	}

    return I_R_OK;
}

static int proc_rx_pkts(int sockfd)
{
	char buf[MAX_HEADER_LEN + 1] = {0};
	char pkts_info[RESPONSE_PKTDATA_LEN] = {0};
	int len = 0;
	int pkt_len = 0;
	int temp_len = 0;
	int num = 0;
	int msg_type = 0;
	int ret = 0;

	if (sockfd <= 0)
	{
        printf("%s:Parameter(s) error.\n", __func__);
		return I_R_ERROR;
	}
	
	/* 读取头部内容 */
    ret = recv_specific_length_pkts(sockfd, buf, MAX_HEADER_LEN);
	if (ret != I_R_OK)
	{
        printf("%s: call recv_specific_length_pkts fail.\n", __func__);

		return ret;
	}
	
	/* 解析内容*/
    //sscanf(buf,"%4d%4d",&msg_type,&len);
    msg_type = *(int *)buf;
    len = *(int *)(buf + 4);

    msg_type = ntohl(msg_type);
    len = ntohl(len);

    printf("%s:read head: msg_type=%d, len=%d.\n", __func__, msg_type, len);

    
    ret = recv_specific_length_pkts(sockfd, pkts_info, len);
	if (ret != I_R_OK)
    {
        printf("%s: call recv_specific_length_pkts fail.\n", __func__);

		return ret;
    }

    printf("%s:response result: %s.\n", __func__, pkts_info);


    return ret;
}


int main(int argc, char *argv[])
{
    struct addrinfo hint, *result;
    int res, sfd;
    //char buf[MAX_TX_PKTDATA_LEN + MAX_HEADER_LEN] = {0};

    memset(&hint, 0, sizeof(hint));
    hint.ai_family   = AF_INET;
    hint.ai_socktype = SOCK_STREAM;
    
    if (argc != 3) {
        perror("error:  ip, port not usage \n");
        exit(1);
    }
        
    printf("ip: %s, port: %s\n", argv[1], argv[2]);

    //res = getaddrinfo("127.0.0.1", argv[1], &hint, &result);
    res = getaddrinfo(argv[1], argv[2], &hint, &result);
    if (res == -1) {
        perror("error : cannot get socket address!\n");
        exit(1);
    }

    sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sfd == -1) {
        perror("error : cannot get socket file descriptor!\n");
        exit(1);
    }

    res = connect(sfd, result->ai_addr, result->ai_addrlen);
    if (res == -1) {
        printf("error: connect the server fail: %s\n", strerror(errno));
        exit(1);
    }

	struct stat st_buf = {0};

	if (0 != access(FILE_NAME, F_OK))
	{
		printf("access return error.\n");
		return 0;
	}
	if (0 != stat(FILE_NAME, &st_buf))
	{
		printf("stat return error.\n");
        return 0;
	}
    
    int data_len = 0;
    //data_len = st_buf.st_size + 1;
    data_len = st_buf.st_size;
    
    printf("data_len=%d\n", data_len);

     
    char head_buf[MAX_HEADER_LEN] = {0};

    *(int *)head_buf = htonl(0x0076);
    *(int *)(head_buf + 4) = htonl(data_len);
  //  *(int *)(head_buf + 4) = data_len;

   
   int left = 0;
   int write_cnt = 0;

   	/* 发送报文头 */
	left = MAX_HEADER_LEN;
	char *ptr = head_buf;
	while (left > 0)
	{
		write_cnt = write(sfd, ptr, left);
		if (write_cnt <= 0)
		{
			if (write_cnt < 0 && errno == EINTR)
			{
				write_cnt = 0;
			}
			else
			{
                close(sfd);
                return -1;
			}
		}
        
		left -= write_cnt;
		ptr += write_cnt;
	}


    
	char *data_buf = NULL;

	if (NULL == (data_buf = calloc(st_buf.st_size + 1, 1)))
	{
		printf("calloc return error.\n");
        return 0;
	}
    
    FILE *fp = NULL;
	if(NULL == (fp = fopen(FILE_NAME, "rb")))
    {
        printf("fail to open rule.ibm.\n");
        return 0;
    }
	
	int read_cnt = 0;
    left = st_buf.st_size;
    
	ptr = data_buf;

	while (left > 0)
    {
        read_cnt = fread(ptr, 1, left, fp);
        left -= read_cnt;
        ptr += read_cnt;
    }

    fclose(fp);

    
   	/* 发送 报文 */
	left = data_len;
	ptr = data_buf;

	int total_cnt = 0;
	int max_segment_times = 0;
	int tail_segment_times = 0;
	
	while (left > 0)
	{
        //ret = write(sfd, ptr, left);
        
        if (left < MAX_TX_PKTDATA_LEN)
        {
            write_cnt = write(sfd, ptr, left);
            printf("send packet len=%d\n",  write_cnt);
                
            max_segment_times++;
        }
        else
        {
            write_cnt = write(sfd, ptr, MAX_TX_PKTDATA_LEN);
            printf("send packet len=%d\n",  write_cnt);
                
            tail_segment_times++;
        }

        total_cnt += write_cnt;
        
		if (write_cnt <= 0)
		{
			if (write_cnt < 0 && errno == EINTR)
			{
                printf("write errno == EINTR, ret=%d\n", write_cnt);
				write_cnt = 0;
			}
			else
			{
                printf("write, to close(sfd), ret=%d\n", write_cnt);
                close(sfd);
                return -1;
			}
		}
        
		left -= write_cnt;
		ptr += write_cnt;

		usleep(10000);
	}
	
    // printf("2 write:\n%s\n", head_buf + 8);
    printf("client, max_segment_times=%d, tail_segment_times=%d, total_cnt=%d\n", 
        max_segment_times, tail_segment_times, total_cnt);
    
    // 发送完成
    free(data_buf);

    
    
    // 开始接收响应
    printf("begin to recv response\n");
    proc_rx_pkts(sfd);

    /*
	char rebuf[MAX_HEADER_LEN + 1] = {0};

    int cnt = read(sfd, rebuf, MAX_HEADER_LEN);

        if (cnt == -1) {
            if (errno == EAGAIN) {
    return 0;
            }
            
            perror("error : read error!\n");
    return -1;

        } else if (cnt == 0) {
            close(sfd);
    return 0;
        } 
        printf("receive client data : %s\n, cnt=%d\n", rebuf, cnt);    
*/
        /*
        int msg_type = *(int *)rebuf;
        int len = *(int *)(rebuf + 4);
        
        msg_type = ntohl(msg_type);
        len = ntohl(len);
        printf("pkt head: msg_type=%d, len=%d\n", msg_type, len);
        
        char buf[MAX_TX_PKTDATA_LEN] = {0};

        
        if (len < 1024)
        {
            cnt = read(sfd,  buf, len);
        }
        else
        {
            cnt = read(sfd,  buf, 328);
        }
        printf("receive client data : %s\n, cnt=%d\n", buf, cnt);    
        */
    
        printf("\n");
        while(1)
        {
            printf(".");
            sleep(3);
        }
        
        close(sfd);

   

    return 0;
}


