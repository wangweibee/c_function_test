#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdint.h>

struct dpdk_nic_port_statistics
{
	uint64_t rx_bytes;
	uint64_t tx_bytes;
};


void  main()
{
/*
    char str[] = "[{\"taskId\":207,\"taskType\":\"custom_idf\",\"extendInfo\":{\"idf_xml_url\":\"http://192.168.10.220:8080/Resources/file/fileManage.spr?method\\u003dgetFile\\u0026fileName\\u003dprotocolUpdate/iec104.xml.ss\",\"action\":\"add\"}}]";


    int res = process_task(str);
*/
char arr_t[3] = {0};


    struct dpdk_nic_port_statistics last_nic_port_stats_arr[16] = {{0}};
    struct dpdk_nic_port_statistics nic_port_stats_arr[16] = {{0}};
    
    char sub_flow_stat[512] = {0};

    int len = 0;
    int tmp_l = 0;
len = snprintf(arr_t, 33, "abc" \
			  "def");
printf("len=%d, arr_t=%s\n", len, arr_t);

return;

    
    len = snprintf(sub_flow_stat, 512, "\"flow\":[");
printf("len=%d, tmp_l=%d\n", len, tmp_l);

    int i = 0;

    for (i = 0; i < 2; i++)
    {
        nic_port_stats_arr[i].rx_bytes = 10 * i + 1;
        nic_port_stats_arr[i].tx_bytes = 100 * i + 2;

        if (i > 0)
        {
            tmp_l = snprintf(sub_flow_stat + len, 512 - len, ", ");
            len += tmp_l;
printf("len=%d, tmp_l=%d\n", len, tmp_l);
        }
        
       uint32_t id = i + 1;
        tmp_l = snprintf(sub_flow_stat + len, 512 - len, "{\"id\":%u, \"up\":%llu, \"down\":%llu, \"total\":%llu}", 
            id, nic_port_stats_arr[i].rx_bytes,
            nic_port_stats_arr[i].tx_bytes);
            
        len += tmp_l;
printf("len=%d, tmp_l=%d\n", len, tmp_l);

        last_nic_port_stats_arr[i] = nic_port_stats_arr[i];
        
    }


printf("%s\n", sub_flow_stat);
return;


}
