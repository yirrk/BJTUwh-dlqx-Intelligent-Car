#include "common.h"
#include "include.h"


#define BM_SWITCH1  PTD5
#define BM_SWITCH2  PTD4
#define BM_SWITCH3  PTD3
#define BM_SWITCH4  PTD2
#define MENU_PAGE_MAX 3	//��ʾҳ����
uint8 menu_page=0;//OLED��ʾҳ��

uint8 dis_buff1[20]={0};  //OLED��ʾ����
KEY_MSG_t keymsg;

/************************��ʾ��������**************************/
void display_logo(void)
{		    
	Draw_BMP();	//��̬ˢ����ʾͼƬ 
    OLED_Clear();
 //   OLED_Fill(0,0,127,63,1);
  //  while(1);
}

void update_display0(void)//��ʾ����0
{
	//OLED_Clear();
	//sprintf(dis_buff1," Analog voltage   \r\n  ");//
	//OLED_ShowString(0,0,dis_buff1);	
	sprintf(dis_buff1,"ch1:%3d ch2:%3d",sen_var[0],sen_var[1]);//
	OLED_ShowString(0,0,dis_buff1);	
	sprintf(dis_buff1,"ch3:%3d ch4:%3d",sen_var[2],sen_var[3]);//
	OLED_ShowString(0,16,dis_buff1);
    sprintf(dis_buff1,"BAT VOL:%dmV",BAT_VOL_mV);//
	OLED_ShowString(0,32,dis_buff1);
	sprintf(dis_buff1,"P0");//
	OLED_ShowString(0,48,dis_buff1);
	OLED_Refresh_Gram();	
   // printf("CH1:%d,CH2:%d,CH3:%d,CH4:%d\r\n",sen_var[0],sen_var[1],sen_var[2],sen_var[3]);
}

void update_display1(void)//��ʾ����1
{
	sprintf(dis_buff1,"Time used:%ds",TimeUsed);//
	OLED_ShowString(0,0,dis_buff1);	
	sprintf(dis_buff1,"image cnt:%d",imgCount);//
	OLED_ShowString(0,16,dis_buff1);
	sprintf(dis_buff1,"average fps:%d",imgCount/TimeUsed);//
	OLED_ShowString(0,32,dis_buff1);
	sprintf(dis_buff1,"P1");//
	OLED_ShowString(0,48,dis_buff1);
	OLED_Refresh_Gram();	
}

void update_display2(void)//��ʾ����2
{
  
	 sprintf(dis_buff1,"Speed1:%3d  ",Speed);//
	OLED_ShowString(0,0,dis_buff1);	
	sprintf(dis_buff1,"Speed2:%3d  ",Speed2);//
	OLED_ShowString(0,16,dis_buff1);
 
	sprintf(dis_buff1,"P2--MOTOR SPEED");//
	OLED_ShowString(0,48,dis_buff1);
	OLED_Refresh_Gram();	
}

void update_display3(void)//��ʾ����3
{
//    sprintf(dis_buff1,"imgCount");//
//	OLED_ShowString(100,0,dis_buff1);	
//	sprintf(dis_buff1,"%d ",imgCount);//
//	OLED_ShowString(100,16,dis_buff1);
// 
//	sprintf(dis_buff1,"P4--IMG");//
//	OLED_ShowString(100,48,dis_buff1);
//	OLED_Refresh_Gram();	
}

/***********************��������*******************************/
void key_msg_process(void)
{
	if(get_key_msg(&keymsg) == 1)
	{
	  if(keymsg.key == KEY_U && keymsg.status ==1)
	  {
		if(menu_page<MENU_PAGE_MAX)
			menu_page++;
		else
		  menu_page=0;
	  }
	  else if(keymsg.key == KEY_D && keymsg.status ==1)
	  {
		if(menu_page>0)
			menu_page--;
		else
		  menu_page=MENU_PAGE_MAX;
	  }
            
      printf("\n���°���KEY%d,����Ϊ%d��0Ϊ���£�1Ϊ����2Ϊ������",keymsg.key,keymsg.status);
	}
}

/***********************���뿪�ش���*******************************/
void switch_msg_process(void)
{
	
}


/***********************OLED��ʾ����*******************************/
void OLED_process(void)
{
  	static uint8 menu_page_last;
  	if(menu_page_last!=menu_page)//�л���ʾҳ��ʱ����
	  OLED_Clear();
	switch(menu_page)
	{
		case 0://��ʾ��1ҳ��
	 	 	update_display0();
	 	break;
		case 1://��ʾ��2ҳ��
	 	 	update_display1();
	 	break;
		case 2://��ʾ��3ҳ��
	 	 	update_display2();
	 	break;
		case 3://��ʾ��4ҳ��
          show_pic_on_oled();
       //   update_display3();
	 	break;
	}
	
	menu_page_last=menu_page;
}


/***********************LCD��ʾ����*******************************/
void LCD_process(void)
{
	
}

/**********************��ʼ�����뿪��*******************************/
void bm_switch_init(void)
{
  gpio_init  (BM_SWITCH1, GPI, 0);
  gpio_init  (BM_SWITCH2, GPI, 0);
  gpio_init  (BM_SWITCH3, GPI, 0);
  gpio_init  (BM_SWITCH4, GPI, 0);
}

/***********************���ز��뿪��״̬ 0-3λ�ֱ����BM1-BM4*******************************/
uint8 get_sw_status(void)
{
  uint8 sw_status=0;
  if(gpio_get(BM_SWITCH1) == 0)
     sw_status|=0x08;
  if(gpio_get(BM_SWITCH2) == 0)
     sw_status|=0x04;
  if(gpio_get(BM_SWITCH3) == 0)
     sw_status|=0x02;
  if(gpio_get(BM_SWITCH4) == 0)
     sw_status|=0x01;
  return sw_status;
}








