#include "common.h"
#include "include.h"


#define BM_SWITCH1  PTD5
#define BM_SWITCH2  PTD4
#define BM_SWITCH3  PTD3
#define BM_SWITCH4  PTD2
#define MENU_PAGE_MAX 3	//显示页面数
uint8 menu_page=0;//OLED显示页面

uint8 dis_buff1[20]={0};  //OLED显示缓存
KEY_MSG_t keymsg;

/************************显示开机画面**************************/
void display_logo(void)
{		    
	Draw_BMP();	//动态刷新显示图片 
    OLED_Clear();
 //   OLED_Fill(0,0,127,63,1);
  //  while(1);
}

void update_display0(void)//显示数据0
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

void update_display1(void)//显示数据1
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

void update_display2(void)//显示数据2
{
  
	 sprintf(dis_buff1,"Speed1:%3d  ",Speed);//
	OLED_ShowString(0,0,dis_buff1);	
	sprintf(dis_buff1,"Speed2:%3d  ",Speed2);//
	OLED_ShowString(0,16,dis_buff1);
 
	sprintf(dis_buff1,"P2--MOTOR SPEED");//
	OLED_ShowString(0,48,dis_buff1);
	OLED_Refresh_Gram();	
}

void update_display3(void)//显示数据3
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

/***********************按键处理*******************************/
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
            
      printf("\n按下按键KEY%d,类型为%d（0为按下，1为弹起，2为长按）",keymsg.key,keymsg.status);
	}
}

/***********************拨码开关处理*******************************/
void switch_msg_process(void)
{
	
}


/***********************OLED显示处理*******************************/
void OLED_process(void)
{
  	static uint8 menu_page_last;
  	if(menu_page_last!=menu_page)//切换显示页面时清屏
	  OLED_Clear();
	switch(menu_page)
	{
		case 0://显示第1页面
	 	 	update_display0();
	 	break;
		case 1://显示第2页面
	 	 	update_display1();
	 	break;
		case 2://显示第3页面
	 	 	update_display2();
	 	break;
		case 3://显示第4页面
          show_pic_on_oled();
       //   update_display3();
	 	break;
	}
	
	menu_page_last=menu_page;
}


/***********************LCD显示处理*******************************/
void LCD_process(void)
{
	
}

/**********************初始化拨码开关*******************************/
void bm_switch_init(void)
{
  gpio_init  (BM_SWITCH1, GPI, 0);
  gpio_init  (BM_SWITCH2, GPI, 0);
  gpio_init  (BM_SWITCH3, GPI, 0);
  gpio_init  (BM_SWITCH4, GPI, 0);
}

/***********************返回拨码开关状态 0-3位分别代表BM1-BM4*******************************/
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








