#ifndef __HMI_INTERFACE_H
#define __HMI_INTERFACE_H			




void display_logo(void);
/***********************��������*******************************/
void key_msg_process(void);

/***********************���뿪�ش���*******************************/
void switch_msg_process(void);

/***********************OLED��ʾ����*******************************/
void OLED_process(void);

/***********************LCD��ʾ����*******************************/
void LCD_process(void);

void bm_switch_init(void);
uint8 get_sw_status(void);


#endif  