#include "PictureShow.h"

int showPicture_bmp(char* (pictureFilePath))
{
	int i, x, y;
	
	int bmpfd = open(pictureFilePath, O_RDWR);  //1.打开bmp图片
	if(-1 == bmpfd)
	{
		printf("open bmp err!\n");
		return -1;
	}	
	//1.打开显示屏设备文件
	int lcdfd = open("/dev/fb0", O_RDWR);
	if(-1 == lcdfd)
	{
		printf("open fb0 err!\n");
		return -1;
	}	
	//2、读取图片文件中前54字节文件信息头
	char buf[54];
	read(bmpfd, buf, 54);
	//3、读取图片中剩余的1152000字节的颜色数据
	char BGR[800*480*3];
	read(bmpfd, BGR, 800*480*3);
	//4、需要将读取的BGR数据转换为开发板屏幕要求的ARGB格式
	int ARGB[800*480];
	for(i=0; i<800*480; i++)
		ARGB[i] = BGR[3*i] | BGR[3*i+1]<<8 | BGR[3*i+2]<<16;
	//5、进行按行翻转
	int data[800*480];
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)
			data[x+(479-y)*800]  =  ARGB[x+y*800];
    //创建映射
    int *p=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,
                    MAP_SHARED,lcdfd,0);
    //将数据写入到映射的内存中
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)	
			*(p+x+y*800) = data[x+y*800];
	
	munmap(p, 800*480*4);
    
	//7.关闭显示屏设备文件和图片文件
	close(bmpfd);
	close(lcdfd);
	
	return 0;	

}

int showBMP_any(int rx,int ry,char *filepath,int w,int h)
{
    if(w*3%4!=0)
	{
		printf("bmp err!\n");
		return -1;
	}
	f(rx+w>800 || ry+h>480)
	{
		printf("show bmp picture err:bmp very big!\n");
		return -1;
	}
    int i, x, y;
	//1.打开bmp图片
	int bmpfd = open(filepath, O_RDWR);
	if(-1 == bmpfd)
	{
		printf("open bmp err!\n");
		return -1;
	}
    //1.打开显示屏设备文件
	int lcdfd = open("/dev/fb0", O_RDWR);
	if(-1 == lcdfd)
	{
		printf("open fb0 err!\n");
		return -1;
	}
    //2、读取图片文件中前54字节文件信息头
	char buf[54];
	read(bmpfd, buf, 54);
    //3、读取图片中剩余的1152000字节的颜色数据
	char BGR[w*h*3];
	read(bmpfd, BGR, w*h*3);
    //4、需要将读取的BGR数据转换为开发板屏幕要求的ARGB格式
	int ARGB[w*h];
	for(i=0; i<w*h; i++)
		ARGB[i] = BGR[3*i] | BGR[3*i+1]<<8 | BGR[3*i+2]<<16;
    //5、进行按行翻转
	int data[w*h];
	for(y=0; y<h; y++)
		for(x=0; x<w; x++)
			data[x+(h-1-y)*w]  =  ARGB[x+y*w];
    //创建映射
	int *p = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE,
					MAP_SHARED, lcdfd, 0);
    //将数据写入到映射的内存中
	for(y=0; y<h; y++)
		for(x=0; x<w; x++)	
			*(p+x+rx+(ry+y)*800) = data[x+y*w];

    munmap(p, 800*480*4);

    //7.关闭显示屏设备文件和图片文件
	close(bmpfd);
	close(lcdfd);

}