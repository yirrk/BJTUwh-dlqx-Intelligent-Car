

#ifndef __PID_H__
#define __PID_H__

struct PID 
{
    float kp;                   //����ϵ��
    float ki;                   //����ϵ��
    float kd;                   //΢��ϵ��
    float kc;                   //�������� 

    double targetPoint;         //Ŀ���
    double lastError;           //Error[-1]
    double prevError;           //Error[-2]
};

void PID_Init(struct PID *this, double targetPoint);
double PID_OutputLimit(struct PID *this, double output, float Max, float Min);
void PID_SetParameter(struct PID *this, float kp, float ki, float kd, float kc);
void PID_SetTargetValue(struct PID *this, double targetPoint);
double PID_GetTargetValue(struct PID *this);
double PID_IncCalculate(struct PID *this, double samplePoint);



#endif  

