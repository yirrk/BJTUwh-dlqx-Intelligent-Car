/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       VCAN_LCD_ILI9325.h
 * @brief      LCD ILI9325������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-09-03
 */
#ifndef _VCAN_LCD_ILI9325_H_
#define _VCAN_LCD_ILI9325_H_

#include "VCAN_LCD.h"
#include "MK60_flexbus.h"


//�û�����
#define ILI9325_DIR_DEFAULT     1      //����Ĭ�Ϸ��� (0~3)


#if (USE_LCD == LCD_ILI9325)

/*********************** API�ӿ� ******************************/
//�ṩAPI�ӿڸ�LCD����

#define LCD_H                   ILI9325_get_h()                 //��
#define LCD_W                   ILI9325_get_w()                 //��

#define LCD_INIT()              LCD_ILI9325_init()              //��ʼ��
#define LCD_PTLON(site,size)    LCD_ILI9325_ptlon(site,size)    //����
#define LCD_RAMWR()             LCD_ILI9325_WR_CMD(0x22)        //дģʽ
#define LCD_WR_DATA(data)       LCD_ILI9325_WR_DATA(data)       //д����
#define LCD_WR_CMD(cmd)         LCD_ILI9325_WR_CMD(cmd)         //����
#define LCD_SET_DIR(opt)        LCD_ILI9325_dir(opt)            //����

#define LCD_DIR                 ILI9325_get_dir()               //��ȡ����

#endif //(USE_LCD == LCD_ILI9325)

/********************* ILI9325�ڲ�ʵ�� ***********************/

#define LCD_ILI9325_CMD_ADDR                    FB_8080_CMD
#define LCD_ILI9325_DATA_ADDR                   FB_8080_DATA

#define LCD_ILI9325_WR_CMD(cmd)         do{LCD_ILI9325_CMD_ADDR  = cmd ;}while(0)
#define LCD_ILI9325_WR_DATA(data)       do{LCD_ILI9325_DATA_ADDR = data;}while(0)


extern void     LCD_ILI9325_init();
extern void     LCD_ILI9325_dir(uint8 option);
extern void     LCD_ILI9325_ptlon(Site_t site, Size_t size);
extern uint16   ILI9325_get_h();
extern uint16   ILI9325_get_w();
extern uint8    ILI9325_get_dir();




#endif //   _VCAN_LCD_ILI9325_H_