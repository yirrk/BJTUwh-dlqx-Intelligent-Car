#include "common.h"
#include "MK60_port.h"
#include "MK60_i2c.h"
#include "MK60_gpio.h"
#include "oled.h"
//#include "stdlib.h"
#include "oledfont.h"  	 
#include "main.h"

//////////////////////////////////////////////////////////////////////////////////	 
//imodule	
//////////////////////////////////////////////////////////////////////////////////	

//宏定义调用底层的I2C接口
#define OLED_PORT_INIT(baud)      i2c_init(OLED_DEVICE,baud)
#define OLED_WR(reg,value)        i2c_write_reg(OLED_DEVICE,OLED_ADRESS,reg,value)  //写寄存器


//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			   
uint8 OLED_GRAM[128][8];	 


void my_delay(uint32 time)
{
   // volatile uint32 i = time;
   // while(i--);
;
}

//更新显存到LCD		 
void OLED_Refresh_Gram(void)
{
	uint8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)
          OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}


//起始信号
void I2C_Start(void)
{
    OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

//结束信号
void I2C_Stop(void)
{
	OLED_SCLK_Set();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

//等待信号响应
void I2C_WaitAck(void) //测数据信号的电平
{
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}

//写入一个字节
void Send_Byte(uint8 dat)
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		OLED_SCLK_Clr();//将时钟信号设置为低电平
		if(dat&0x80)//将dat的8位从最高位依次写入
		{
			OLED_SDIN_Set();
    }
		else
		{
			OLED_SDIN_Clr();
    }
    OLED_SCLK_Set();//将时钟信号设置为高电平
    OLED_SCLK_Clr();//将时钟信号设置为低电平
    dat<<=1;
  }
}

/*
	@brief			对OLED写入一个字节
	@param			dat：数据
					mode：1，写诶数据；0，写入命令
	@retval			无
 */
void OLED_WR_Byte(unsigned char dat,unsigned char mode)
{	
  if(mode)
    {i2c_write_reg(OLED_DEVICE,0x78>>1,0x40,dat);}
  else
    {i2c_write_reg(OLED_DEVICE,0x78>>1,0x00,dat);}
   
} 

//void OLED_WR_Byte(unsigned char dat,unsigned char mode)
//{
//	I2C_Start();
//	Send_Byte(0x78);
//	I2C_WaitAck();
//	if(mode){Send_Byte(0x40);}
//        else{Send_Byte(0x00);}
//	I2C_WaitAck();
//	Send_Byte(dat);
//	I2C_WaitAck();
//	I2C_Stop();
//}

//开启OLED显示 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x14,OLED_CMD);//开启电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//点亮屏幕
}

//关闭OLED显示 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//电荷泵使能
	OLED_WR_Byte(0x10,OLED_CMD);//关闭电荷泵
	OLED_WR_Byte(0xAF,OLED_CMD);//关闭屏幕
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	uint8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//更新显示
}

//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint(uint8 x,uint8 y,uint8 t)
{
	uint8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}

//x1,y1,x2,y2 填充区域的对角坐标
//确保x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,清空;1,填充	  
void OLED_Fill(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 dot)
{  
	uint8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//更新显示
}


/***********功能描述：显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
void Draw_BMP()
{ 	
 uint8 i=0,j=0;
 uint8 x,y,y0,t,t1,temp;
	for(i=0;i<128;i++)//行
	{
			x=i%16*8;
			y=i/16*8;
			y0=y;
			for(t=0;t<8;t++)
			{   
			 temp=bmp1[i][t];		                           
			 for(t1=0;t1<8;t1++)
			 {
					if(temp&0x01)OLED_DrawPoint(x,y,1);
					else OLED_DrawPoint(x,y,0);
					temp>>=1;
					y++;
					if((y-y0)==8)
					{
						y=y0;
						x++;
						break;
					}
				}
			}
		OLED_Refresh_Gram();
	}
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示				 
//size:选择字体 16/12 
void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 size,uint8 mode)
{      			    
	uint8 temp,t,t1;
	uint8 y0=y;
	chr=chr-' ';//得到偏移后的值				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  //调用1206字体
		else temp=oled_asc2_1608[chr][t];		 //调用1608字体 	                          
     for(t1=0;t1<8;t1++)
		 {
			if(temp&0x80)OLED_DrawPoint(x,y,mode);
			else OLED_DrawPoint(x,y,!mode);
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
    }          
}
//m^n函数
uint32 oled_pow(uint8 m,uint8 n)
{
	uint32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//显示2个数字
//x,y :起点坐标	 
//len :数字的位数
//size:字体大小
//mode:模式	0,填充模式;1,叠加模式
//num:数值(0~4294967295);	 		  
void OLED_ShowNum(uint8 x,uint8 y,uint32 num,uint8 len,uint8 size)
{         	
	uint8 t,temp;
	uint8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size/2)*t,y,' ',size,1);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size,1); 
	}
} 
//显示字符串
//x,y:起点坐标  
//*p:字符串起始地址
//用16字体
void OLED_ShowString(uint8 x,uint8 y,const uint8 *p)
{
#define MAX_CHAR_POSX 122
#define MAX_CHAR_POSY 58          
    while(*p!='\0')
    {       
        if(x>MAX_CHAR_POSX){x=0;y+=16;}
        if(y>MAX_CHAR_POSY){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*p,16,1);	 
        x+=8;
        p++;
    }  
}	  

//PTXn_e OLED_PTxn[LED_MAX] = {PTC16,PTC17,PTC18,PTC19};
//初始化SSD1306					    
void OLED_Init(void)
{ 	
//    GPIO_InitTypeDef GPIO_InitStructure;
//    /* GPIOD Periph clock enable */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//
//    /* Configure PB5-PB7 in output pushpull mode ....OLED*/
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(GPIOB, &GPIO_InitStructure);
  
//  gpio_init(PTE0,GPO,0);
//  gpio_init(PTE1,GPO,0);
  
    OLED_PORT_INIT(1000 * 1000);//初始化I2C接口，波特率400k
    
    my_delay(20);
    
    OLED_WR_Byte(0xAE,OLED_CMD); //关闭显示
	OLED_WR_Byte(0xD5,OLED_CMD); //设置时钟分频因子,震荡频率
	OLED_WR_Byte(80,OLED_CMD);   //[3:0],分频因子;[7:4],震荡频率
	OLED_WR_Byte(0xA8,OLED_CMD); //设置驱动路数
	OLED_WR_Byte(0X3F,OLED_CMD); //默认0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); //设置显示偏移
	OLED_WR_Byte(0X00,OLED_CMD); //默认为0

	OLED_WR_Byte(0x40,OLED_CMD); //设置显示开始行 [5:0],行数.
													    
	OLED_WR_Byte(0x8D,OLED_CMD); //电荷泵设置
	OLED_WR_Byte(0x14,OLED_CMD); //bit2，开启/关闭
	OLED_WR_Byte(0x20,OLED_CMD); //设置内存地址模式
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;
	OLED_WR_Byte(0xA1,OLED_CMD); //段重定义设置,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数
	OLED_WR_Byte(0xDA,OLED_CMD); //设置COM硬件引脚配置
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]配置
		 
	OLED_WR_Byte(0x81,OLED_CMD); //对比度设置
	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;默认0X7F (亮度设置,越大越亮)
	OLED_WR_Byte(0xD9,OLED_CMD); //设置预充电周期
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //设置VCOMH 电压倍率
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)
	OLED_WR_Byte(0xA6,OLED_CMD); //设置显示方式;bit0:1,反相显示;0,正常显示	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //开启显示	 
	OLED_Clear();
}  



///*****************************************************************************
// 函 数 名  : oLED_PrintImage
// 功能描述  : 将图像显示出来
// 输入参数  : uint8 *pucTable     二维图像数组的地址
//             uint16 usRowNum    二维图像的行数1~64
//             uint16 usColumnNum 二维图像的列数1~128
// 输出参数  : none
// 返 回 值  : none
//*****************************************************************************/
//void OLED_PrintImage(uchar *pucTable, uint16 usRowNum, uint16 usColumnNum)
//{
//    uint8 ucData;
//    uint16 i,j,k,m,n;
//    uint16 usRowTmp;
//
//    m = usRowNum >> 3;   //计算图片行数以8位为一组完整的组数
//    n = usRowNum % 8;    //计算分完组后剩下的行数
//    
//    for(i = 0; i < m; i++) //完整组行扫描
//    {
//        LED_SetPos(0,(uint8)i);
//        usRowTmp = i << 3;    //计算当前所在行的下标                  
//        for(j = 0; j < usColumnNum; j++) //列扫描        
//        {
//            ucData = 0;
//            for(k = 0; k < 8; k++) //在i组中对这8行扫描
//            {
//                ucData = ucData >> 1;
//                if((pucTable + (usRowTmp + k) * usColumnNum)[j] == LED_IMAGE_WHITE)
//                {
//                    ucData = ucData | 0x80;
//                }
//                
//            }
//            LED_WrDat(ucData);
//        }
//    }
//    
//    LED_SetPos(0,(uint8)i); //设置剩下的行显示的起始坐标
//    usRowTmp = i << 3;       //计算当前所在行的下标                  
//    for(j = 0; j < usColumnNum; j++) //列扫描        
//    {
//        ucData = 0;
//        for(k = 0; k < n; k++) //对剩下的行扫描
//        {
//            ucData = ucData >> 1;
//            if((pucTable + (usRowTmp + k) * usColumnNum)[j] == LED_IMAGE_WHITE)
//            {
//                ucData = ucData | 0x80;
//            }
//            
//        }
//        ucData = ucData >> (8 - n);
//        LED_WrDat(ucData);
//    }
//
//    return;
//}
/*!
 *  @brief      缩放灰度图像显示
 *  @param      site            左上角坐标
 *  @param      size            显示图像大小
 *  @param      img             图像地址
 *  @param      imgsize         图像大小
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};          //x = 10 ,y = 20
                        Size_t size = {80,60};          //W = 80,H = 60
                        Size_t imgsize = {320,240};     //W = 320,H = 240
                        LCD_Img_gray_Z(site, size, img,imgsize);
 */
void OLED_Img_gray_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize)
{

  uint8 dis_buff1[20]={0};  //OLED显示缓存
    uint32 temp, tempY;
    uint16 x, y;
    uint16 X, Y;
    uint8 *pimg = (uint8 *)img;
   // uint16 rgb;
    
    uint8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  //清零
    
    sprintf(dis_buff1,"img");//
	OLED_ShowString(90,0,dis_buff1);	
	sprintf(dis_buff1,"%d ",imgCount);//
	OLED_ShowString(90,16,dis_buff1);
 
	sprintf(dis_buff1,"P4");//
	OLED_ShowString(90,48,dis_buff1);
   

    for(y = 0; y < size.H; y++)
    {
        Y = ( (  y * imgsize.H   ) / size.H) ;//从图像中的Y行取数 按比例缩放
        tempY = Y * imgsize.W ;

        for(x = 0; x < size.W; x++)
        {
            X = ( x * imgsize.W  ) / size.W ;//列数 按比例缩放
            temp = tempY + X;//数据位置
           // rgb = GRAY_2_RGB565(pimg[temp]);    //
            if(pimg[temp]==0)
                OLED_DrawPoint(x,y,0);
            else 
                OLED_DrawPoint(x,y,1);
        }
    }
     OLED_Refresh_Gram();
}

