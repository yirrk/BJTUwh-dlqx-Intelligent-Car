#ifndef __HMI_INTERFACE_H
#define __HMI_INTERFACE_H			




void display_logo(void);
/***********************按键处理*******************************/
void key_msg_process(void);

/***********************拨码开关处理*******************************/
void switch_msg_process(void);

/***********************OLED显示处理*******************************/
void OLED_process(void);

/***********************LCD显示处理*******************************/
void LCD_process(void);

void bm_switch_init(void);
uint8 get_sw_status(void);


#endif  