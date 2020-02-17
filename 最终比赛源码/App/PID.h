

#ifndef __PID_H__
#define __PID_H__

struct PID 
{
    float kp;                   //比例系数
    float ki;                   //积分系数
    float kd;                   //微分系数
    float kc;                   //积分门限 

    double targetPoint;         //目标点
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

