
#ifndef __MAIN_H
#define __MAIN_H	



typedef struct
{
    uint8 camera;//使用摄像头
    uint8 lcd;   //使用LCD
    uint8 print;//使用串口输出
    uint8 wireless;//使用无线模块
} sys_con;



void show_pic_on_oled(void);//在OLED上显示图像

extern int TimeUsed;
extern int imgCount;//帧数累计标志
extern int Speed;//保存速度的变量
extern int Speed2;//保存速度的变量
#endif  