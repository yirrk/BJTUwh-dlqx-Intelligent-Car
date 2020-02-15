
#ifndef __HMI_INTERFACE_H
#define __HMI_INTERFACE_H	

void init_sensor(void);
void get_sensor_val(void);

extern uint8 sen_var[5];
extern uint32 BAT_VOL_mV;

#endif  