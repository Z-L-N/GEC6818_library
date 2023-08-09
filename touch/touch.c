/**********************/
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//GEC6818开发板
//创建日期:2023/7/8
//版本：V2.0
//*********************
//
/**********************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <pwd.h>
#include<grp.h>

#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <linux/input.h>

#include "touch.h"

int touch_GetValue(int *x, int *y)
{
  
    //打开触摸屏设备文件
    int fd = open("/dev/input/event0", O_RDWR);
    if(-1 == fd)
    {
        perror("open");
        return -1;
    }

    struct input_event ts;
    while(1)
    {
        read(fd, &ts, sizeof(ts));      //由于设备文件中没有数据，阻塞等待

        if(ts.type == EV_ABS)   //触摸屏事件
        {
            if(ts.code == ABS_X)    //横坐标
            {
                *x = ts.value;
                //printf("x:%d\n", ts.value);
            }
            if(ts.code == ABS_Y)    //纵坐标
            {
                *y = ts.value;
                //printf("y:%d\n", ts.value);
            }

            //压力值  版本一
            if(ts.code == ABS_PRESSURE) 
            {
                 printf("PRESSURE-1:%d\n", ts.value);
                /*
                if(ts.value == 1)   //按下
                    break;
                */
                if(ts.value == 0)   //松开
                        break;
            }
               
        }

        //压力值  版本二
        if(ts.type == EV_KEY && ts.code == BTN_TOUCH)
        {
            printf("PRESSURE-2:%d\n", ts.value);
            /*
            if(ts.value == 1)   //按下
                break;
            */
           if(ts.value == 0)   //松开
                break;
        }
            
    }
   
    //printf("touch:[%d, %d]\n", *x, *y);

    close(fd);   
}

int touch_GetSlip(u_int8_t *slip_direction)
{

}