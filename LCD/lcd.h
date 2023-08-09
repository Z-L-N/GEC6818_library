#ifndef __LCD_H
#define __LCD_H

#include <stdio.h>
#include <stdbool.h>
#include "stdlib.h"
//open
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//write  close  read
#include <unistd.h>
//mmap
#include <sys/mman.h>

#define u16 u_int16_t 
#define u8 u_int8_t 
#define u32 u_int32_t 
//颜色

#define WHITE           0xFFFFFF
#define BLACK           0x000000

#define RED             0xFF0000
#define GREEN           0x00FF00
#define BLUE            0x0000FF

#define YELLOW          0x00FFE0
//GUI颜色
#define DARKBLUE        0X01CF  //深蓝色
#define LIGHTBLUE       0X7D7C  //浅蓝色  
#define GRAYBLUE        0X5458  //灰蓝色

void delay_ms(int xms);

int LCD_DrawPoint(int x,int y,int32_t data_color);    //画点
int LCD_Clear(u32 color);                            //清屏                                            
void LCD_Fill(int sx, int sy, int ex, int ey, int32_t data_color);          //填充单色
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2,int32_t data_color);       //画线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,int32_t data_color);  //画矩形
void LCD_Draw_Circle(u16 x0, u16 y0, u16 r,int32_t data_color);             //画圆
void LCD_ShowChar(u16 x, u16 y, u8 num, u8 size,int32_t data_color, u8 mode);  //显示一个字符
void LCD_ShowString(u16 x, u16 y, u16 width, u16 height, u8 size, u8 *p,int32_t data_color); //显示一个字符串,12/16字体
u32 LCD_Pow(u8 m, u8 n);                                                    
void LCD_ShowNum(u16 x, u16 y, u32 num, u8 len, u8 size,int32_t data_color); //显示一个数字
void LCD_ShowxNum(u16 x, u16 y, u32 num, u8 len, u8 size, int32_t data_color, u8 mode);  //显示 数字


int showPicture_bmp(char* (pictureFilePath));       //显示bmp图片
int LCD_Show_BMP(u16 x, u16 y, char* bmpName);

int showBMP_any(int rx,int ry,char* (filepath),int w,int h);  //
void showBMP_GIF(int n,int xms);

void display_intNum(unsigned int x,unsigned y,int num,int numBit);
void keyboard_3x4_display(int x,int y);
#endif