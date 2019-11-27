#include "common.h"
#include "include.h"



void main()
{
    char ch;
    uart_init(VCAN_PORT,115200);

    printf("测试串口");

    uart_putstr    (VCAN_PORT , "\n\n\n砥砺前行队 18721001etc:");         //发送字符串

}


