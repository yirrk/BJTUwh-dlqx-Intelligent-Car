#include "PID.c"
#include<stdio.h>

static struct PID MotorLeft;      //左电机速度 
static struct PID MotorRight;     //右电机速度 
static struct PID DirectionAngle; //方位角 

/*
*********************************************************************************************************
* Function Name : main
* Description   : PID测试 
* Input         : setpoint 
* Output        : PID值 
* Return        : None
*********************************************************************************************************
*/

/* 
void main()
{
	float setpoint, sample1, sample2;
	double result1, result2, adjust1, adjust2;
	
	printf("-----PID测试开始-----\n请输入Set point:");
	scanf("%f",&setpoint);
		
	PID_Init(&MotorLeft,setpoint);
	PID_Init(&MotorRight,setpoint);
	
	PID_SetParameter(&MotorLeft,0,1,0,5); 
	PID_SetParameter(&MotorRight,1,0,0,0);

	printf("-----PID测试开始-----\n");
	
	while(1)
	{
		adjust1 = PID_IncCalculate(&MotorLeft,sample1);
		adjust1 = PID_OutputLimit(&MotorLeft,adjust1,10000,-10000);
		result1 = result1 + adjust1;
		
		adjust2 = PID_IncCalculate(&MotorRight,sample2);
		adjust2 = PID_OutputLimit(&MotorRight,adjust2,10000,-10000);
		result2 = result2 + adjust2;
		
		sample1 = 0.9*result1;
		sample2 = 0.9*result2;
		printf("\t%.3f\t -- \t%.3f\n",result1, result2); 
		usleep(100000);
	}
	
} 
*/
 

