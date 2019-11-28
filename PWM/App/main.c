#include "common.h"
#include "include.h"

//��ɽ��������������Ȩ�������ƣ���ԭ��·�ı�ɫ��
//ע�⣺ɽ�������� �� ���� MOS �� ���뷴��ģ�IO ��� �͵�ƽ������ MOS �ܺ�ᷴ�࣬��� �ߵ�ƽ��������Ȼ��


//����ģʽ: PWM ���� IN �ܽ� ,IO���� INH ��ʹ�� ��
// INH ����Ϊ �ߵ�ƽ ��ʹ�� BTN7971
// IN  ����Ϊ �ߵ�ƽ , ���� �� IN ����Ϊ �͵�ƽ��ɲ����ע�⣬��ɲ�������ǽ�����ô�򵥣�
//����ģʽ �� ��ͣ���٣�INΪ�ߣ���Ȼ����٣�INΪ�ͣ����Ƿ�˼�������ܳ�������õķ���
//Ч����Σ� һ�߲� ���� ��һ�߲� ɲ��  ��������أ�

//���ɹ���ģʽ: PWM ���� INH �ܽ� ���� �Ƿ�ʹ�� ��IO ���� IN �ܽ�
// IN ����Ϊ �ߵ�ƽ  �� ����
// INH ����Ϊ �ߵ�ƽ , ʹ��оƬ������ȫ��״̬ �� INH ����Ϊ �͵�ƽ ������оƬ������ ������״̬
//���ɹ���ģʽ �� һʱ���ͣ�һʱ�ɿ����������������ٶ���ǰ������
//Ч����Σ� ���� BTN7971 ��ʵ���� ����Ϊ �ı� ��ѹֵ ���Ӷ� �ﵽ ���� ������ ��Ŀ�� ��оƬ�����������٣���������


//��ɱģʽ��PWM ���� INH �ܽ� ���� �Ƿ�ʹ�� ��IO ���� IN �ܽ�
// IN ����Ϊ �͵�ƽ  �� ɲ��
// INH ����Ϊ �ߵ�ƽ , ʹ��оƬ������ɲ��״̬ �� INH ����Ϊ �͵�ƽ ������оƬ������ ������״̬
//���һֱ���� ɲ��״̬���ᱧ��������Ӷ�ʹ�� С�� �򻬣������������ Ư�ơ�
//���һֱ���� ������״̬ ����� ����С���Ĺ���һֱ��������Ȼ�������֮���Ǿ�Ħ�������ﲻ�����Ħ������Ч���������ҪPWM����ռ�ձ�����ɱ


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
#define MOTOR4_PWM_IO  FTM0_CH0

//����ģʽ�£�Ƶ��Ӧ���� 30~100��  1
//����ģʽ�£�Ƶ��Ӧ���� 20k ����  0
#if 0
#define MOTOR_HZ    (50)
#else
#define MOTOR_HZ    (20*1000)
#endif


void main()
{
    uint8 i = 0;
    printf("\n*****FTM ������� ����*****\n");

    ftm_pwm_init(MOTOR_FTM, MOTOR1_PWM,MOTOR_HZ,100);      //��ʼ�� ��� PWM
    ftm_pwm_init(MOTOR_FTM, MOTOR2_PWM,MOTOR_HZ,100);
    //IO�ܽ�����
    //gpio_init(MOTOR1_IO,GPO,LOW);
    //gpio_init(MOTOR2_IO,GPO,LOW);


    while(1)
    {
        i += 10;
        if(i > 50)
        {
            i = 0;
        }
        ftm_pwm_duty(MOTOR_FTM, MOTOR1_PWM,i);
        ftm_pwm_duty(MOTOR_FTM, MOTOR2_PWM,i);

        DELAY_MS(500);



    }

}