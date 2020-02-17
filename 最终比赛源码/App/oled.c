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

//�궨����õײ��I2C�ӿ�
#define OLED_PORT_INIT(baud)      i2c_init(OLED_DEVICE,baud)
#define OLED_WR(reg,value)        i2c_write_reg(OLED_DEVICE,OLED_ADRESS,reg,value)  //д�Ĵ���


//OLED���Դ�
//��Ÿ�ʽ����.
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

//�����Դ浽LCD		 
void OLED_Refresh_Gram(void)
{
	uint8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)
          OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}


//��ʼ�ź�
void I2C_Start(void)
{
    OLED_SCLK_Set();
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

//�����ź�
void I2C_Stop(void)
{
	OLED_SCLK_Set();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
}

//�ȴ��ź���Ӧ
void I2C_WaitAck(void) //�������źŵĵ�ƽ
{
	OLED_SCLK_Set();
	OLED_SCLK_Clr();
}

//д��һ���ֽ�
void Send_Byte(uint8 dat)
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		OLED_SCLK_Clr();//��ʱ���ź�����Ϊ�͵�ƽ
		if(dat&0x80)//��dat��8λ�����λ����д��
		{
			OLED_SDIN_Set();
    }
		else
		{
			OLED_SDIN_Clr();
    }
    OLED_SCLK_Set();//��ʱ���ź�����Ϊ�ߵ�ƽ
    OLED_SCLK_Clr();//��ʱ���ź�����Ϊ�͵�ƽ
    dat<<=1;
  }
}

/*
	@brief			��OLEDд��һ���ֽ�
	@param			dat������
					mode��1��д�����ݣ�0��д������
	@retval			��
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

//����OLED��ʾ 
void OLED_DisPlay_On(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x14,OLED_CMD);//������ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//������Ļ
}

//�ر�OLED��ʾ 
void OLED_DisPlay_Off(void)
{
	OLED_WR_Byte(0x8D,OLED_CMD);//��ɱ�ʹ��
	OLED_WR_Byte(0x10,OLED_CMD);//�رյ�ɱ�
	OLED_WR_Byte(0xAF,OLED_CMD);//�ر���Ļ
}

//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	uint8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  
	OLED_Refresh_Gram();//������ʾ
}

//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���				   
void OLED_DrawPoint(uint8 x,uint8 y,uint8 t)
{
	uint8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM[x][pos]|=temp;
	else OLED_GRAM[x][pos]&=~temp;	    
}

//x1,y1,x2,y2 �������ĶԽ�����
//ȷ��x1<=x2;y1<=y2 0<=x1<=127 0<=y1<=63	 	 
//dot:0,���;1,���	  
void OLED_Fill(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 dot)
{  
	uint8 x,y;  
	for(x=x1;x<=x2;x++)
	{
		for(y=y1;y<=y2;y++)OLED_DrawPoint(x,y,dot);
	}													    
	OLED_Refresh_Gram();//������ʾ
}


/***********������������ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7*****************/
void Draw_BMP()
{ 	
 uint8 i=0,j=0;
 uint8 x,y,y0,t,t1,temp;
	for(i=0;i<128;i++)//��
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
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/12 
void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 size,uint8 mode)
{      			    
	uint8 temp,t,t1;
	uint8 y0=y;
	chr=chr-' ';//�õ�ƫ�ƺ��ֵ				   
    for(t=0;t<size;t++)
    {   
		if(size==12)temp=oled_asc2_1206[chr][t];  //����1206����
		else temp=oled_asc2_1608[chr][t];		 //����1608���� 	                          
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
//m^n����
uint32 oled_pow(uint8 m,uint8 n)
{
	uint32 result=1;	 
	while(n--)result*=m;    
	return result;
}				  
//��ʾ2������
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//mode:ģʽ	0,���ģʽ;1,����ģʽ
//num:��ֵ(0~4294967295);	 		  
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
//��ʾ�ַ���
//x,y:�������  
//*p:�ַ�����ʼ��ַ
//��16����
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
//��ʼ��SSD1306					    
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
  
    OLED_PORT_INIT(1000 * 1000);//��ʼ��I2C�ӿڣ�������400k
    
    my_delay(20);
    
    OLED_WR_Byte(0xAE,OLED_CMD); //�ر���ʾ
	OLED_WR_Byte(0xD5,OLED_CMD); //����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WR_Byte(80,OLED_CMD);   //[3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WR_Byte(0xA8,OLED_CMD); //��������·��
	OLED_WR_Byte(0X3F,OLED_CMD); //Ĭ��0X3F(1/64) 
	OLED_WR_Byte(0xD3,OLED_CMD); //������ʾƫ��
	OLED_WR_Byte(0X00,OLED_CMD); //Ĭ��Ϊ0

	OLED_WR_Byte(0x40,OLED_CMD); //������ʾ��ʼ�� [5:0],����.
													    
	OLED_WR_Byte(0x8D,OLED_CMD); //��ɱ�����
	OLED_WR_Byte(0x14,OLED_CMD); //bit2������/�ر�
	OLED_WR_Byte(0x20,OLED_CMD); //�����ڴ��ַģʽ
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WR_Byte(0xA1,OLED_CMD); //���ض�������,bit0:0,0->0;1,0->127;
	OLED_WR_Byte(0xC0,OLED_CMD); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WR_Byte(0xDA,OLED_CMD); //����COMӲ����������
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]����
		 
	OLED_WR_Byte(0x81,OLED_CMD); //�Աȶ�����
	OLED_WR_Byte(0xEF,OLED_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WR_Byte(0xD9,OLED_CMD); //����Ԥ�������
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //����VCOMH ��ѹ����
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;

	OLED_WR_Byte(0xA4,OLED_CMD); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WR_Byte(0xA6,OLED_CMD); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //������ʾ	 
	OLED_Clear();
}  



///*****************************************************************************
// �� �� ��  : oLED_PrintImage
// ��������  : ��ͼ����ʾ����
// �������  : uint8 *pucTable     ��άͼ������ĵ�ַ
//             uint16 usRowNum    ��άͼ�������1~64
//             uint16 usColumnNum ��άͼ�������1~128
// �������  : none
// �� �� ֵ  : none
//*****************************************************************************/
//void OLED_PrintImage(uchar *pucTable, uint16 usRowNum, uint16 usColumnNum)
//{
//    uint8 ucData;
//    uint16 i,j,k,m,n;
//    uint16 usRowTmp;
//
//    m = usRowNum >> 3;   //����ͼƬ������8λΪһ������������
//    n = usRowNum % 8;    //����������ʣ�µ�����
//    
//    for(i = 0; i < m; i++) //��������ɨ��
//    {
//        LED_SetPos(0,(uint8)i);
//        usRowTmp = i << 3;    //���㵱ǰ�����е��±�                  
//        for(j = 0; j < usColumnNum; j++) //��ɨ��        
//        {
//            ucData = 0;
//            for(k = 0; k < 8; k++) //��i���ж���8��ɨ��
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
//    LED_SetPos(0,(uint8)i); //����ʣ�µ�����ʾ����ʼ����
//    usRowTmp = i << 3;       //���㵱ǰ�����е��±�                  
//    for(j = 0; j < usColumnNum; j++) //��ɨ��        
//    {
//        ucData = 0;
//        for(k = 0; k < n; k++) //��ʣ�µ���ɨ��
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
 *  @brief      ���ŻҶ�ͼ����ʾ
 *  @param      site            ���Ͻ�����
 *  @param      size            ��ʾͼ���С
 *  @param      img             ͼ���ַ
 *  @param      imgsize         ͼ���С
 *  @since      v5.0
 *  Sample usage:       Site_t site = {10,20};          //x = 10 ,y = 20
                        Size_t size = {80,60};          //W = 80,H = 60
                        Size_t imgsize = {320,240};     //W = 320,H = 240
                        LCD_Img_gray_Z(site, size, img,imgsize);
 */
void OLED_Img_gray_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize)
{

  uint8 dis_buff1[20]={0};  //OLED��ʾ����
    uint32 temp, tempY;
    uint16 x, y;
    uint16 X, Y;
    uint8 *pimg = (uint8 *)img;
   // uint16 rgb;
    
    uint8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM[n][i]=0X00;  //����
    
    sprintf(dis_buff1,"img");//
	OLED_ShowString(90,0,dis_buff1);	
	sprintf(dis_buff1,"%d ",imgCount);//
	OLED_ShowString(90,16,dis_buff1);
 
	sprintf(dis_buff1,"P4");//
	OLED_ShowString(90,48,dis_buff1);
   

    for(y = 0; y < size.H; y++)
    {
        Y = ( (  y * imgsize.H   ) / size.H) ;//��ͼ���е�Y��ȡ�� ����������
        tempY = Y * imgsize.W ;

        for(x = 0; x < size.W; x++)
        {
            X = ( x * imgsize.W  ) / size.W ;//���� ����������
            temp = tempY + X;//����λ��
           // rgb = GRAY_2_RGB565(pimg[temp]);    //
            if(pimg[temp]==0)
                OLED_DrawPoint(x,y,0);
            else 
                OLED_DrawPoint(x,y,1);
        }
    }
     OLED_Refresh_Gram();
}

