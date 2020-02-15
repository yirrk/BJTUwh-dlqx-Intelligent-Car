#include "common.h"
#include "include.h"

#define S3010_FTM   SPI1
#define S3010_CH    SPI1_PCS0
#define S3010_HZ    (100)

/*!
 *  @brief      main����
 *  @since      v5.0
 *  @note       ɽ�� S3010��� ����ʵ�� ,ɽ�� �ṩ�� �������ģ�飬�ܽŶ����� MOS �ܸ��룬�ź��Ƿ���ġ�
                ���糣��� �ߵ�ƽ ʹ��
                ������ϣ��뿴�������ӣ�
                http://www.vcan123.com/forum.php?mod=collection&action=view&ctid=25
 */
void main()
{
    uint8 i;
    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,100);      //��ʼ�� ��� PWM

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