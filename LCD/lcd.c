
/**********************/
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//GEC6818开发板
//创建日期:2023/7/8
//版本：V3.2
//*********************
//
/**********************/
#include "lcd.h"
#include "font.h"


void delay_ms(int xms)
{
	int ms=1000*xms;
	sleep(ms);
}

//画点函数
int LCD_DrawPoint(int x,int y,int32_t data_color)
{
	//1.打开显示屏设备文件
	int lcdfd = open("/dev/fb0", O_RDWR);
	if(-1 == lcdfd)
	{
		printf("open fb0 err!\n");
		return -1;
	}

	//创建映射
	int *p = mmap(NULL, 800*480*4, PROT_READ|PROT_WRITE,
					MAP_SHARED, lcdfd, 0);
    //将数据写入到映射的内存中
	*(p+x+y*800) = data_color;

    munmap(p, 800*480*4);

    //7.关闭显示屏设备文件
	close(lcdfd);
}

//清屏
int LCD_Clear(u32 color)
{
    int x,y;
	//1.打开显示屏设备文件
	int lcdfd = open("/dev/fb0", O_RDWR);
	if(-1 == lcdfd)
	{
		perror("clear open fb0 err");
		return -1;
	}

	//2.创建映射
    int *p=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,
                    MAP_SHARED,lcdfd,0);
    if( p == NULL )
    {
        perror("clear mmap failed");
        return -1;
    }
    //3.将数据写入到映射的内存中
	for(y=0; y<480; y++)
		for(x=0; x<800; x++)	
			*(p+x+y*800) = color;
	//解除映射
	munmap(p, 800*480*4);

	//6.关闭显示屏设备文件
	close(lcdfd);
	return 0;	
}

//在指定区域内填充指定颜色
//区域大小:(xend-xsta+1)*(yend-ysta+1)
//xsta
//color:要填充的颜色
void LCD_Fill(int sx, int sy, int ex, int ey, int32_t data_color)
{
	unsigned int x,y;
	unsigned int width,height;
	width = ex-sx+1;            //得到填充的宽度
    height = ey-sy+1;           //高度
	/* for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            LCD_DrawPoint(sx+j,sy+i,data_color);  //写入数据
        }
    } */
    //1.打开显示屏设备文件
	int lcdfd = open("/dev/fb0", O_RDWR);
	if(-1 == lcdfd)
	{
		perror("clear open fb0 err");
		return -1;
	}

    //2.创建映射
    int *p=mmap(NULL,800*480*4,PROT_READ|PROT_WRITE,
                    MAP_SHARED,lcdfd,0);
    if( p == NULL )
    {
        perror("full mmap failed");
        return -1;
    }

     //3.将数据写入到映射的内存中
	for(y=0; y<height; y++)
		for(x=0; x<width; x++)	
			*(p+x+sx+(y+sy)*800) = data_color;
	//解除映射
	munmap(p, 800*480*4);

	//6.关闭显示屏设备文件
	close(lcdfd);
	return 0;	
}

//画线
//x1,y1:起点坐标
//x2,y2:终点坐标
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,int32_t data_color)
{
	u16 t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1;              //计算坐标增量
    delta_y = y2 - y1;
    uRow = x1;
    uCol = y1;

	if (delta_x > 0)incx = 1;       //设置单步方向
    else if (delta_x == 0)incx = 0; //垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }

    if (delta_y > 0)incy = 1;
    else if (delta_y == 0)incy = 0; //水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }

    if ( delta_x > delta_y)distance = delta_x; //选取基本增量坐标轴
    else distance = delta_y;

	for (t = 0; t <= distance + 1; t++ )    //画线输出
    {
        LCD_DrawPoint(uRow, uCol,data_color); //画点
        xerr += delta_x ;
        yerr += delta_y ;

        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }

        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

//画矩形
//(x1,y1),(x2,y2):矩形的对角坐标
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,int32_t data_color)
{
    LCD_DrawLine(x1, y1, x2, y1,data_color);
    LCD_DrawLine(x1, y1, x1, y2,data_color);
    LCD_DrawLine(x1, y2, x2, y2,data_color);
    LCD_DrawLine(x2, y1, x2, y2,data_color);
}

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void LCD_Draw_Circle(u16 x0, u16 y0, u16 r,int32_t data_color)
{
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);       //判断下个点位置的标志

    while (a <= b)
    {
        LCD_DrawPoint(x0 + a, y0 - b,data_color);        //5
        LCD_DrawPoint(x0 + b, y0 - a,data_color);        //0
        LCD_DrawPoint(x0 + b, y0 + a,data_color);        //4
        LCD_DrawPoint(x0 + a, y0 + b,data_color);        //6
        LCD_DrawPoint(x0 - a, y0 + b,data_color);        //1
        LCD_DrawPoint(x0 - b, y0 + a,data_color);
        LCD_DrawPoint(x0 - a, y0 - b,data_color);        //2
        LCD_DrawPoint(x0 - b, y0 - a,data_color);        //7
        a++;

        //使用Bresenham算法画圆
        if (di < 0)di += 4 * a + 6;
        else
        {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}


//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size,int32_t data_color, u8 mode)
{
    u8 temp, t1, t;
    u16 y0 = y;
    u8 csize = (size / 8 + ((size % 8) ? 1 : 0)) * (size / 2);  //得到字体一个字符对应点阵集所占的字节数
    num = num - ' ';    //得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）

    for (t = 0; t < csize; t++)
    {
        if (size == 12)temp = asc2_1206[num][t];        //调用1206字体
        else if (size == 16)temp = asc2_1608[num][t];   //调用1608字体
        else if (size == 24)temp = asc2_2412[num][t];   //调用2412字体
		else if (size == 32)temp = asc2_3216[num][t];   //调用3216字体
		else if (size == 64)temp = asc2_6432[num][t];   //调用2412字体
        else return;                                    //没有的字库

        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp & 0x80)
				LCD_DrawPoint(x, y, data_color);
            else if (mode == 0)
				LCD_DrawPoint(x, y, data_color);

            temp <<= 1;
            y++;

            if (y >= 480)
				return;      //超区域了

            if ((y - y0) == size)
            {
                y = y0;
                x++;

                if (x >= 800)
					return;   //超区域了

                break;
            }
        }
    }
}

//显示字符串
//x,y:起点坐标
//width,height:区域大小
//size:字体大小
//*p:字符串起始地址
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p,int32_t data_color)
{
    u8 x0 = x;
    width += x;
    height += y;

    while ((*p <= '~') && (*p >= ' '))   //判断是不是非法字符!
    {
        if (x >= width)
        {
            x = x0;
            y += size;
        }

        if (y >= height)break; //退出

        LCD_ShowChar(x, y, *p, size, data_color ,1);
        x += size / 2;
        p++;
    }
}

//m^n函数
//返回值:m^n次方.
u32 LCD_Pow(u8 m, u8 n)
{
    u32 result = 1;

    while (n--)
		result *= m;

    return result;
}

//显示数字,高位为0,则不显示
//x,y :起点坐标
//len :数字的位数
//size:字体大小
//color:颜色
//num:数值(0~4294967295);
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size,int32_t data_color)
{
    u8 t, temp;
    u8 enshow = 0;

    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;

        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                LCD_ShowChar(x + (size / 2)*t, y, ' ', size, data_color,0);
                continue;
            }
            else enshow = 1;

        }

        LCD_ShowChar(x + (size / 2)*t, y, temp + '0', size, data_color,1);
    }
}

//显示数字,高位为0,还是显示
//x,y:起点坐标
//num:数值(0~999999999);
//len:长度(即要显示的位数)
//size:字体大小
//mode:
//[7]:0,不填充;1,填充0.
//[6:1]:保留
//[0]:0,非叠加显示;1,叠加显示.
void LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, int32_t data_color, u8 mode)
{
    u8 t, temp;
    u8 enshow = 0;

    for (t = 0; t < len; t++)
    {
        temp = (num / LCD_Pow(10, len - t - 1)) % 10;

        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                if (mode & 0X80)
					LCD_ShowChar(x + (size / 2)*t, y, '0', size, data_color, mode & 0X01);
                else 
					LCD_ShowChar(x + (size / 2)*t, y, ' ', size, data_color, mode & 0X01);

                continue;
            }
            else enshow = 1;

        }

        LCD_ShowChar(x + (size / 2)*t, y, temp + '0', size, data_color, mode & 0X01);
    }
}

//全屏显示图片
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


int showBMP_any(int rx,int ry,char* (filepath),int w,int h)
{
	int i, x, y;
    if(w*3%4!=0)
	{
		printf("bmp w err!\n");
		return -1;
	}
	if(rx+w>800 || ry+h>480)
	{
		printf("show bmp picture err:bmp very big!\n");
		return -1;
	}
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

void showBMP_GIF(int n,int xms)
{
	int i;
	char path[128];
	for(i=n;i<n+1;i++)
	{
		sprintf(path,"./%d.bmp",i);
		showBMP_any(0,0,path,800 ,480);
		delay_ms(xms);

	}
	/*for(i=1;i<begin;i++)
	{
		sprintf(path,"./%d.bmp",i);
		showBMP_any(0,0,&path,800 ,480);
		delay_ms(xms);

	}*/

}
