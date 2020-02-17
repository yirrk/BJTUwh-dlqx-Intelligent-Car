#include "common.h"
#include "include.h"
int f=10;
int flag=0;
void led0()
{
    led(LED0, LED_ON);                  //LED0 亮
    DELAY_MS(500/f); 
    if(key_check(KEY_STOP) == KEY_DOWN)
    {
        flag=0;
        led(LED0, LED_OFF); 
     }
     else if(key_check(KEY_U)== KEY_DOWN)
     {
        f+=1;
     }
     else if(key_check(KEY_L)== KEY_DOWN)
     {
        f-=1;
     }
    led(LED0, LED_OFF);                 //LED0 灭
    DELAY_MS(500/f); 
}

void main()
{
    key_init(KEY_U);
    key_init(KEY_D);
    key_init(KEY_L);
    key_init(KEY_R);
    key_init(KEY_START);
    key_init(KEY_STOP);
    led_init(LED0);                         //初始化LED0

    printf("\n按键按下");

    while(1)
    { 
      
      /*if(key_check(KEY_START) == KEY_DOWN) //检测key状态
        {
            printf("\n按键按下");       //通过串口助手查看，提示按键按下
            delay=500;
            while(1)
            {
              led0();
              if(key_check(KEY_STOP) == KEY_DOWN) //检测key状态
              {       
                  printf("\n按键按下");       //通过串口助手查看，提示按键按下
            
                  led(LED0, LED_OFF);   
                  break;   
               } 
              if(key_check(KEY_U) == KEY_DOWN) //检测key状态
              {
                  delay-=100;
                
                }
              if(key_check(KEY_D) == KEY_DOWN) //检测key状态
              {
            
                  delay+=100;
                  
              }
            }
        }*/
      if(key_check(KEY_START) == KEY_DOWN)
      {
        flag=1; 
        f=10;
      }
      if(flag==1)
      {
        if(key_check(KEY_STOP) == KEY_UP&&key_check(KEY_U)== KEY_UP&&key_check(KEY_D) == KEY_UP)
        {
          led0();
        }
        else if(key_check(KEY_STOP) == KEY_DOWN)
        {
          flag=0;
          led(LED0, LED_OFF); 
        }
        else if(key_check(KEY_U)== KEY_DOWN)
        {
          f+=1;
        }
        else if(key_check(KEY_L)== KEY_DOWN)
        {
          f-=1;
        }
      }
      
      
    }
}

