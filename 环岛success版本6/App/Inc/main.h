
#ifndef __MAIN_H
#define __MAIN_H	



typedef struct
{
    uint8 camera;//ʹ������ͷ
    uint8 lcd;   //ʹ��LCD
    uint8 print;//ʹ�ô������
    uint8 wireless;//ʹ������ģ��
} sys_con;



void show_pic_on_oled(void);//��OLED����ʾͼ��

extern int TimeUsed;
extern int imgCount;//֡���ۼƱ�־
extern int Speed;//�����ٶȵı���
extern int Speed2;//�����ٶȵı���
#endif  