#include "common.h"
#include "include.h"



void main()
{
    char ch;
    uart_init(VCAN_PORT,115200);

    printf("���Դ���");

    uart_putstr    (VCAN_PORT , "\n\n\n����ǰ�ж� 18721001etc:");         //�����ַ���

}


