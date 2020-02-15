#ifndef __OLED_H
#define __OLED_H			


#define OLED_DEVICE I2C1
#define OLED_ADRESS          (0x78)      /*OLED_ Address*/
//OLED模式设置
//0:4线串行模式
//1:并行8080模式
#define OLED_MODE 0
		    						  
//-----------------OLED端口定义----------------  					   

//#define OLED_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_9)//CS 片选
//#define OLED_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_9)
//
//#define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_7)//RES 复位
//#define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_7)
//
//#define OLED_RS_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)//DC
//#define OLED_RS_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)
//
//#define OLED_WR_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_14)
//#define OLED_WR_Set() GPIO_SetBits(GPIOG,GPIO_Pin_14)
//
//#define OLED_RD_Clr() GPIO_ResetBits(GPIOG,GPIO_Pin_13)
//#define OLED_RD_Set() GPIO_SetBits(GPIOG,GPIO_Pin_13)
//
//
//
////PC0~7,作为数据线
//#define DATAOUT(x) GPIO_Write(GPIOC,x);//输出  
////使用4线串行接口时使用 
//
//#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_5)//CLK D0 时钟
//#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_5)
//
//#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_6)//DATA D1 数据
//#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_6)
//
// 	

#define OLED_SCLK_Clr() gpio_set (PTE1, 0)
#define OLED_SCLK_Set() gpio_set (PTE1, 1)//SCL

#define OLED_SDIN_Clr() gpio_set (PTE0, 0)
#define OLED_SDIN_Set() gpio_set (PTE0, 1)//SDA

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

void OLED_WR_Byte(uint8 dat,uint8 cmd);	    
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);		   
void Draw_BMP(void);
							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8 x,uint8 y,uint8 t);
void OLED_Fill(uint8 x1,uint8 y1,uint8 x2,uint8 y2,uint8 dot);
void OLED_ShowChar(uint8 x,uint8 y,uint8 chr,uint8 size,uint8 mode);
void OLED_ShowNum(uint8 x,uint8 y,uint32 num,uint8 len,uint8 size);
void OLED_ShowString(uint8 x,uint8 y,const uint8 *p);	 
void OLED_Img_gray_Z(Site_t site, Size_t size, uint8 *img, Size_t imgsize);

#endif  
	 



