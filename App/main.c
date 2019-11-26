/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ���� LED �����Ƿ�����
                ������Ч����LED0��LED1ͬʱ������˸
 */
void main()
{
    led_init(LED0);                         //��ʼ��LED0
    led_init(LED1);                         //��ʼ��LED1

    while(1)
    {        
        led(LED0, LED_ON);                  //LED0 ��
        led_turn(LED1);                     //LED1��ת

        DELAY_MS(500);                      //��ʱ500ms

        led(LED0, LED_OFF);                 //LED0 ��
        led_turn(LED1);                     //LED1��ת

        DELAY_MS(500);                      //��ʱ500ms
    }
}

