#include "common.h"
#include "include.h"

#define S3010_FTM   SPI1
#define S3010_CH    SPI1_PCS0
#define S3010_HZ    (100)

/*!
 *  @brief      main函数
 *  @since      v5.0
 *  @note       山外 S3010舵机 测试实验 ,山外 提供的 电机驱动模块，管脚都加入 MOS 管隔离，信号是反相的。
                例如常规的 高电平 使能
                舵机资料，请看如下链接：
                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=25
 */
void main()
{
    uint8 i;
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,100);      //初始化 舵机 PWM

    while(1)
    {

        for(i = 13;i<25;i++)
        {
            ftm_pwm_duty(S3010_FTM, S3010_CH,100-i);
            DELAY_MS(200);
        }

        for(;i>13;i--)
        {
            ftm_pwm_duty(S3010_FTM, S3010_CH,100-i);
            DELAY_MS(200);
        }
    }

}