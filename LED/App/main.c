
#include "common.h"
#include "include.h"


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

