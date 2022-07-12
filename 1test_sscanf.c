#include<stdio.h>
#include <string.h>


void  main()
{
    int ret = 0;
    char* rules_update_buf = "action=1:content=2,3,6,8";
   
    int rules_action = 0;
    char rules_classes[1024] = {0};

    ret = sscanf(rules_update_buf, "action=%d:content=%s", &rules_action, rules_classes);

    printf ("ret=%d, rules_action=%d, rules_classes=%s\n", ret, rules_action,rules_classes);

    int index = 0;
    int rules_sets[256] = {0};

    char *saveptr = NULL; 
    char *p_data = NULL;

    char *data  = rules_classes;

    
    printf ("start deal string=%s\n", data);

    /* process remain options */
    while ((p_data = strtok_r(data, ",",&saveptr)) != NULL)
    {
        rules_sets[index] = atoi(p_data);
        printf("index=%d, rule_val=%d\n", index, rules_sets[index]);
        index++;
        
        data = NULL;
    }
    
    // 调用更新规则接口
    printf("start to call rule_update_interface: total rule num=%d\n", index);

}
