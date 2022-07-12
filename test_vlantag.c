#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>


void  main()
{
/*
    char str[] = "[{\"taskId\":207,\"taskType\":\"custom_idf\",\"extendInfo\":{\"idf_xml_url\":\"http://192.168.10.220:8080/Resources/file/fileManage.spr?method\\u003dgetFile\\u0026fileName\\u003dprotocolUpdate/iec104.xml.ss\",\"action\":\"add\"}}]";


    int res = process_task(str);
*/


    typedef struct _vlan_tag_hdr {
        unsigned short vlan_type;/**< Ethernet type of encapsulated frame. */
        unsigned short vlan_tci; /**< Priority (3) + CFI (1) + Identifier Code (12) */
    }VLAN_TAG_HDR;

    VLAN_TAG_HDR vlan_tag = {0};
    vlan_tag.vlan_type = 0x8100;
    
    unsigned short id = 11;
    vlan_tag.vlan_tci = id & 4095; //12位


    unsigned char * tmp_chr = (unsigned char *)&vlan_tag;

    printf ("tmp_chr1234:%x,%x,%x,%x\n", tmp_chr[0], tmp_chr[1], tmp_chr[2], tmp_chr[3]);


    unsigned short * tmp_sht = (unsigned short *)&vlan_tag;
    printf ("tmp_sht:1234:%x,%x\n", tmp_sht[0], tmp_sht[1]);

    char *p_start = "o001235";
    
    int i = 0;
    int len = strlen(p_start);

    
    for (i = 0; i < len; i++)
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
