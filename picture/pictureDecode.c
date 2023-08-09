#include "pictureDecode.h"


BITMAPFILEHEADER fileHeader;
BITMAPINFOHEADER infoHeader;

//定义显示信息的函数，传入文件头结构体
void showBmpHead(BITMAPFILEHEADER pBmpHead)
{  
    printf("BMP文件大小：%dkb\n", fileHeader.bfSize/1024);
    printf("保留字必须为0：%d\n",  fileHeader.bfReserved1);
    printf("保留字必须为0：%d\n",  fileHeader.bfReserved2);
    printf("实际位图数据的偏移字节数: %d\n",  fileHeader.bfOffBits);
}

//定义显示信息的函数，传入的是信息头结构体
void showBmpInfoHead(BITMAPINFOHEADER pBmpinfoHead)
{
   printf("位图信息头:\n" );
   printf("信息头的大小:%d\n" ,infoHeader.biSize);
   printf("位图宽度:%d\n" ,infoHeader.biWidth);
   printf("位图高度:%d\n" ,infoHeader.biHeight);
   printf("图像的位面数(位面数是调色板的数量,默认为1个调色板):%d\n" ,infoHeader.biPlanes);
   printf("每个像素的位数:%d\n" ,infoHeader.biBitCount);
   printf("压缩方式:%d\n" ,infoHeader.biCompression);
   printf("图像的大小:%d\n" ,infoHeader.biSizeImage);
   printf("水平方向分辨率:%d\n" ,infoHeader.biXPelsPerMeter);
   printf("垂直方向分辨率:%d\n" ,infoHeader.biYPelsPerMeter);
   printf("使用的颜色数:%d\n" ,infoHeader.biClrUsed);
   printf("重要颜色数:%d\n" ,infoHeader.biClrImportant);
}
