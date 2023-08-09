#ifndef _PICTURESHOW_H_
#define _PICTURESHOW_H_

#include <stdio.h>
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//write  close  read
#include <unistd.h>
//mmap
#include <sys/mman.h>

int showPicture_bmp(char* (pictureFilePath));
int showBMP_any(int rx,int ry,char *filepath,int w,int h);

#endif