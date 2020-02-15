#include "common.h"
#include "include.h"



//#define MOTOR1_IO   PTD15
//#define MOTOR2_IO   PTA19
//#define MOTOR3_IO   PTA5
//#define MOTOR4_IO   PTA24

#define MOTOR_FTM   FTM0
#define MOTOR1_PWM  FTM_CH2
#define MOTOR2_PWM  FTM_CH3
#define MOTOR3_PWM  FTM_CH4
#define MOTOR4_PWM  FTM_CH0

#define MOTOR1_PWM_IO  FTM0_CH2
#define MOTOR2_PWM_IO  FTM0_CH3
#define MOTOR3_PWM_IO  FTM0_CH4
#define MOTOR4_PWM_IO  FTM1_CH0

//滑行模式下，频率应该是 30~100。  1
//常规模式下，频率应该是 20k 左右  0
#if 0
#define MOTOR_HZ    (50)
#else
#define MOTOR_HZ    (20*1000)
#endif


void main()
{
    uint8 i = 50;
    uart_init(VCAN_PORT,115200);
    printf("\n*****FTM 电机测试 测试*****\n");

    ftm_pwm_init(MOTOR_FTM, MOTOR1_PWM,MOTOR_HZ,50);      //初始化 电机 PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR2_PWM,MOTOR_HZ,100);
    ftm_pwm_init(MOTOR_FTM, MOTOR3_PWM,MOTOR_HZ,100);
    ftm_pwm_init(FTM1, MOTOR4_PWM,MOTOR_HZ,100);
    //IO管脚配置
    //gpio_init(MOTOR2_PWM,GPO,LOW);
    //gpio_init(MOTOR2_IO,GPO,LOW);


    while(1)
    {
        
        //ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,i);
        //ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,i);
        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,100);
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,70);
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,70);
        ftm_pwm_duty(FTM1, MOTOR4_PWM,100);
        DELAY_MS(1000);


        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,70);
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,100);
        ftm_pwm_duty(MOTOR_FTM, MOTOR3_PWM,100);
        ftm_pwm_duty(FTM1, MOTOR4_PWM,70);
        DELAY_MS(1000);
        //DELAY_MS(500);



    }

}