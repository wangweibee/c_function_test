#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <jansson.h>


static int process_task(char *content)
{
    /* validate content length */
    if (strlen(content) == 0) {
        printf( "task has no content!");
        return -1;
    }

    /* parse it as a json object */
    json_error_t jerror;
    json_t *json_tasks = json_loads(content, 0, &jerror); 
    if (!json_tasks) {
        printf( "load json string from task content failed: %s %s (line %d, col %d)",
                jerror.text, jerror.source, jerror.line, jerror.column);
        return -1;
    }
    if (!json_is_array(json_tasks)) {
        printf( "load json string from task content failed: not an array!");
        json_decref(json_tasks);
        return -1;
    }

    size_t index;
    json_t *json_task;

    json_array_foreach(json_tasks, index, json_task) {
         printf( "hahah1!");

    }

    json_decref(json_tasks);

    return 0;
}


void  main()
{
/*
    char str[] = "[{\"taskId\":207,\"taskType\":\"custom_idf\",\"extendInfo\":{\"idf_xml_url\":\"http://192.168.10.220:8080/Resources/file/fileManage.spr?method\\u003dgetFile\\u0026fileName\\u003dprotocolUpdate/iec104.xml.ss\",\"action\":\"add\"}}]";


    int res = process_task(str);
*/
    char *p_start = "o001235";
    
    int i = 0;
    int len = strlen(p_start);

    
    for (i = 1; i < len; i++)
    {
        if (p_start[i] < 48 || p_start[i] > 57)
        {
            if(p_start[i] != 'o')
            {
                int a = 1;
            }

        }
    }
  


    printf ("finish\n");
}
