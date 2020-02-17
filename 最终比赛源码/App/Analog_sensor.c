#include "common.h"
#include "include.h"

#define AMP1     ADC1_SE18        //
#define AMP2     ADC0_SE16        //
#define AMP3     ADC1_SE23       //
#define AMP4     ADC0_SE23       //
#define BAT      ADC1_SE16       //
uint8 sen_var[5]={0};//存放传感器电压值 分别时电磁1-4 电池电压
uint32 BAT_VOL_mV=0;//电池电压 单位mV


void init_sensor(void)
{
    adc_init(AMP1);
    adc_init(AMP2);
    adc_init(AMP3);
    adc_init(AMP4);
    adc_init(BAT);  
}

void get_sensor_val(void)
{
    sen_var[0] = adc_once   (AMP1, ADC_8bit);
    sen_var[1] = adc_once   (AMP2, ADC_8bit);
    sen_var[2] = adc_once   (AMP3, ADC_8bit);
    sen_var[3] = adc_once   (AMP4, ADC_8bit);
    sen_var[4] = adc_once   (BAT, ADC_8bit);
    
    if(sen_var[4]>150)//打开电机开关后测量端口电压较低，不再进行测量
      BAT_VOL_mV=(sen_var[4]*40.05+125.98)*0.5+BAT_VOL_mV*0.5;//滤波算法
}
