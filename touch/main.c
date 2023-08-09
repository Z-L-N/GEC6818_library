#include <stdio.h>
#include "touch.h"

int main()
{
    int x, y;
    while(1)
    {
        touch_GetValue(&x, &y);
        printf("main:[%d, %d]\n", x, y);
        printf("\n");
    }
    

    return 0;
}