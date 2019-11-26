/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"
#include "include.h"

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       测试 LED 功能是否正常
                看到的效果是LED0和LED1同时亮灭闪烁
 */

void led0()
{
          led(LED0, LED_ON);                  //LED0 亮
          DELAY_MS(50);                      //延时500ms
          led(LED0, LED_OFF);                 //LED0 灭
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
  
  led(LED0, LED_ON);                  //LED0 亮
  DELAY_MS(50);                      //延时500ms
  led(LED0, LED_OFF);                 //LED0 灭
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
    led_init(LED0);                         //初始化LED0
    led_init(LED1);                         //初始化LED1
    led_init(LED2);                         //初始化LED2
    led_init(LED3);                         //初始化LED3
 
    while(1)
    { 
       led3();
    }
}

