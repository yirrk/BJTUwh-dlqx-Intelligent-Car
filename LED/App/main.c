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

void led0()
{
          led(LED0, LED_ON);                  //LED0 ��
          DELAY_MS(50);                      //��ʱ500ms
          led(LED0, LED_OFF);                 //LED0 ��
          DELAY_MS(50); 
}

void led2()
{
  led(LED1, LED_ON);  
  led(LED2, LED_ON); 
  led0();
  led(LED1, LED_OFF); 
  led0();
  led(LED1, LED_ON);
  
  led(LED0, LED_ON);                  //LED0 ��
  DELAY_MS(50);                      //��ʱ500ms
  led(LED0, LED_OFF);                 //LED0 ��
  led(LED2, LED_OFF); 
  DELAY_MS(50); 
  
  led(LED1, LED_OFF); 
  led0();
  led(LED1, LED_ON);
  led0();
  
}

void led3()
{
  led(LED3, LED_ON);
  led2();
  led(LED3, LED_OFF);
  led2();
}

void main()
{
    led_init(LED0);                         //��ʼ��LED0
    led_init(LED1);                         //��ʼ��LED1
    led_init(LED2);                         //��ʼ��LED2
    led_init(LED3);                         //��ʼ��LED3
 
    while(1)
    { 
       led3();
    }
}

