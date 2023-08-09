#include "lcd.h"
//#include "touch.h"

#include "stdio.h"
#include "stdbool.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char **argv)
{  
    LCD_Clear(WHITE);
    while(1)
    {
        /* LCD_Clear(RED);
        sleep(2);
        LCD_Clear(GREEN);
        sleep(2);
        LCD_Clear(BLUE);
        sleep(2); */
        LCD_ShowString(0, 0, 240, 24, 24, "Hello World!!",RED);
        LCD_ShowString(0, 20, 240, 24, 24, "I love China",RED);
        LCD_ShowString(0, 60, 800, 32, 32, "I love China",RED);

        LCD_ShowNum(10, 240, 12345, 6, 32,GREEN);
        LCD_ShowNum(10, 270, 123456, 6, 16,GREEN);
        LCD_ShowNum(10, 286, 123456, 6, 12,GREEN);

        LCD_Fill(400, 100, 500, 200, BLUE);
    }
}