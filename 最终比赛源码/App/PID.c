#include <math.h>
#include "PID.h"

/*
*********************************************************************************************************
*                                           增量式PID
*********************************************************************************************************
*/

/*struct PID 
{
    float kp;                   //比例系数
    float ki;                   //积分系数
    float kd;                   //微分系数
    float kc;                   //积分门限 

    double targetPoint;         //目标点
    double lastError;           //Error[-1]
    double prevError;           //Error[-2]
};*/

/*
*********************************************************************************************************
* Function Name : PID_Init
* Description   : PID初始化
* Input         : None
* Output        : None
* Return        : None
*********************************************************************************************************
*/
void PID_Init(struct PID *this, double targetPoint)
{
    this->targetPoint = targetPoint;
    this->lastError = 0;
    this->prevError = 0;    
}

/*
*********************************************************************************************************
* Function Name : PID_OutputLimit
* Description   : PID输出限制
* Input         : None
* Output        : None
* Return        : None
*********************************************************************************************************
*/
double PID_OutputLimit(struct PID *this, double output, float Max, float Min)
{
	float max = Max;
	float min = Min;
	
    if (output < min) 
	{
        output = min;
    } 
	else if (output > max) 
	{
        output = max;
    }
    return output;
}

/*
*********************************************************************************************************
* Function Name : PID_SetParameter
* Description   : PID设置参数
* Input         : None
* Output        : None
* Return        : None
*********************************************************************************************************
*/
void PID_SetParameter(struct PID *this, float kp, float ki, float kd, float kc)
{
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->kc = kc;
}

/*
*********************************************************************************************************
* Function Name : PID_SetTargetValue
* Description   : PID设置目标值
* Input         : None
* Output        : None
* Return        : None
*********************************************************************************************************
*/
void PID_SetTargetValue(struct PID *this, double targetPoint)
{
    this->targetPoint = targetPoint;
}

/*
*********************************************************************************************************
* Function Name : PID_GetTargetValue
* Description   : PID获取目标值
* Input         : None
* Output        : None
* Return        : None
*********************************************************************************************************
*/
double PID_GetTargetValue(struct PID *this)
{
    return this->targetPoint;
}

/*
*********************************************************************************************************
* Function Name : PID_IncCalculate
* Description   : 增量式变积分PID计算
* Input         : None
* Output        : None
* Return        : None
*********************************************************************************************************
*/
double PID_IncCalculate(struct PID *this, double samplePoint)
{   
    double nowError = this->targetPoint - samplePoint;
    double pError, dError, iError; 
    float KI;
    
	pError = nowError - this->lastError;
	iError = nowError;
	dError = nowError - 2*(this->lastError) + this->prevError;
	
	KI = this->ki;// * (1 - abs(tanh(1*(nowError / this->kc)))); 
	
    double out = this->kp * pError +\
                       KI * iError -\
                 this->kd * dError;
                 
    //printf("% .3f\t -- \t%.3f\t -- ",this->lastError, this->prevError);
    
    this->prevError = this->lastError;
    this->lastError = nowError;
	
    return out;
}
