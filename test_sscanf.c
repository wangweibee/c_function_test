#include<stdio.h>
#include <sys/time.h>


int get_port_flow(char *port_name, unsigned long long int *rx_byte, unsigned long long int *tx_byte)
{
    FILE *fd;
    int n;
    char buff[256] = {0};
    char cmd_line[256] = {0};

    snprintf(cmd_line, 256, "/sys/class/net/%s/statistics/rx_bytes", port_name);

    fd = fopen(cmd_line, "r");
    if (NULL == fd)
    {
        printf("get_port_flow fopen %s fail.", cmd_line);
        return -1;
    }
    
    fgets(buff, sizeof(buff), fd);
    //sscanf(buff, "%llu", rx_byte);
    *rx_byte = atoll(buff);
    fclose(fd);
    return 0;
}


void  main()
{
#if 0
    int ret = 0;
unsigned long long int rx_bt = 0;
unsigned long long int tx_bt = 0;

get_port_flow("enp15s0", &rx_bt , &tx_bt);
    printf("rx=%llu, tx=%llu.", rx_bt , tx_bt);


return;
#endif


#if 0
    char* rules_update_buf = "action=1:content=2,3,6,8";
   
    int rules_action = 0;
    char rules_classes[1024] = {0};

    ret = sscanf(rules_update_buf, "action=%d:content=%s", &rules_action, rules_classes);

    printf ("ret=%d, rules_action=%d, rules_classes=%s\n", ret, rules_action,rules_classes);

    int index = 0;
    int rules_sets[256] = {0};

    char *saveptr = NULL; 
    char *option = NULL;
    
    /* process remain options */
    while ((option = strtok_r(rules_classes, ",", &saveptr)) != NULL)
    {
        rules_sets[index] = atoi(option);
        printf("index=%d, rule_val=%d\n", index, rules_sets[index]);
        index++;
    }
#endif


#if 0
    char *string = "ios<android>wp7";
    char buf[36] = {0};
    sscanf(string, "%*[^<]<%[^>]", buf);  
    printf("6.string=%s\n", string);  
    printf("6.buf=%s\n\n", buf);  
#endif


    char *string2 = "Mstar;OWB,Origyn Web Browser,1";
    char buf1[36] = {0};
    char buf2[36] = {0};
    char buf3[36] = {0};
    //sscanf(string2, "%[^,]%*[,]%[^,]%*[,]%d", buf1, buf2, buf3);
    //sscanf(string2, "%[^,],%[^,]", buf1, buf2);

    sscanf(string2, "%*[^,]%s", buf2);

    int aa1 = 0;
    sscanf(string2, "%*[^,]%*[,]%*[^,],%d", &aa1);
    printf("6.string2=%s\n", string2);
    printf("6.aa1=%u\n\n", aa1);
    printf("6.buf2=%s\n\n", buf2);
    

#if 0

    char *str_1 = "31:85:91:11:22:33";
    unsigned char str_arr[6] = {0};
    int ret = 0;

    ret = sscanf(str_1, "%d:%d:%d:%d:%d:%d", &str_arr[0],&str_arr[1],&str_arr[2],&str_arr[3],&str_arr[4],&str_arr[5]);
   // ret = sscanf(str_1, "%2s:%2s:%2s:%2s:%2s:%2s", str_arr[0],str_arr[1],str_arr[2],str_arr[3],str_arr[4],str_arr[5]);
 
    printf("start to print result, ret=%d\n", ret);
    printf("mac array-1-6: %x-%x-%x-%x-%x-%x\n", str_arr[0],str_arr[1],str_arr[2],str_arr[3],str_arr[4],str_arr[5]);

   // printf("mac array-1-6: %s-%s-%s-%s-%s-%s\n", str_arr[0],str_arr[1],str_arr[2],str_arr[3],str_arr[4],str_arr[5]); 

  
    // 调用更新规则接口
   // printf("start to call rule_update_interface: total rule num=%d\n", index);
#endif

}
