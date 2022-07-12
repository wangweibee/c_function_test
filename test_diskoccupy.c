#include <sys/time.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include <stdlib.h>
#include <sys/vfs.h>
#include <stdio.h>
#include <mntent.h>
#include <sys/errno.h>


typedef struct sys_disk_info         //定义一个mem occupy的结构体
{
    unsigned long Disk_used;
    unsigned long Disk_Total;
}SysDiskInfo;


SysDiskInfo *GetHostDiskInfo(SysDiskInfo *sys_disk_info)
{
    struct statfs	fs_info;
    struct mntent	*mnt_info;
    FILE			*fh;
    unsigned long	sum_Total = 0, sum_used = 0, all_sum_Total = 0, sum_availiable = 0, sum_free = 0;

    if ((fh = setmntent("/etc/mtab", "r")) == NULL)
    {
        printf("Cannot open /etc/mtab file!:%s\n",strerror(errno));
        return NULL;
    }

    while ((mnt_info = getmntent(fh)) != NULL)
    {
        if (statfs(mnt_info->mnt_dir, &fs_info) < 0)
        {
            continue;
        }

        unsigned long cur_dir_blocks = fs_info.f_blocks * fs_info.f_bsize / 1024 / 1024;
 
        printf ("mnt_dir:%s, cur dir_blocks:%u\n", mnt_info->mnt_dir, cur_dir_blocks);
        all_sum_Total +=  cur_dir_blocks;

        if (strcmp(mnt_info->mnt_type, "proc") &&
        strcmp(mnt_info->mnt_type, "devfs") &&
        strcmp(mnt_info->mnt_type, "usbfs") &&
        strcmp(mnt_info->mnt_type, "sysfs") &&
        strcmp(mnt_info->mnt_type, "tmpfs") &&
        strcmp(mnt_info->mnt_type, "devpts") &&
        strcmp(mnt_info->mnt_type, "fusectl") &&
        strcmp(mnt_info->mnt_type, "debugfs") &&
        strcmp(mnt_info->mnt_type, "binfmt_misc") &&
        strcmp(mnt_info->mnt_type, "fuse.gvfs_fuse_daemon")&&
        strcmp(mnt_info->mnt_type, "securityfs"))
        {
        }
        else
        {
            continue;
        }

        unsigned long block_size = fs_info.f_bsize/1024;
 
        //printf ("block_size:%u, f_bsize:%u\n", block_size, fs_info.f_bsize);

        sum_Total +=  fs_info.f_blocks * block_size / 1024;
        sum_availiable += fs_info.f_bavail * block_size / 1024;
        sum_free += fs_info.f_bfree * block_size / 1024;

        /* clean auxiliary memory */
    }
    printf ("sum_Total:%u, all_sum_Total:%u, sum_free:%u, sum_availiable:%u\n", sum_Total, all_sum_Total, sum_free, sum_availiable);

    sys_disk_info->Disk_Total = sum_Total/1024;
    sys_disk_info->Disk_used = (sum_Total - sum_free)/1024;
    return sys_disk_info;
}



void  main()
{
    SysDiskInfo *sys_disk_info = (SysDiskInfo *)malloc(sizeof(SysDiskInfo));

    GetHostDiskInfo(sys_disk_info);
    printf ("Disk_used:%u, Disk_Total:%u\n", sys_disk_info->Disk_used, sys_disk_info->Disk_Total);

    free(sys_disk_info);

}