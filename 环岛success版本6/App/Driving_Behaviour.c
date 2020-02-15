#define PI (3.14159265)
#define DEG2RAD(x) (3.14159265*(x)/180.0)
#define RAD2DEG(x) ((x)*180.0/3.14159265)3
 
#include "Vehicle_State.h"
#include "PID_API.c"
#include "main.c" 
#include "math.h"

//控制器初始化 
void ControlInit()
{
	
	g_PID_Inc.pid.init(&MotorLeft.dtvPid,0);
	g_PID_Inc.pid.init(&MotorRight.dtvPid,0);
	g_PID_Inc.pid.init(&DirectionAngle.dtvPid,0);
	g_PID_Inc.pid.init(&LineOffset.dtvPid,0);
	g_PID_Inc.pid.init(&DiffAngle.dtvPid,0);
	
}

//直线行驶决策 
void StraightDriving(float offset, float speed)
{
		
	float coef = 0.4;
	double LAdjustSpeed, RAdjustSpeed, AdjustAngle, AdjustOffsetAngle, AngleDiff,AdjustEqualAngle;
	
	g_PID_Inc.pid.settarget(&MotorLeft.dtvPid,speed);
	g_PID_Inc.pid.settarget(&MotorRight.dtvPid,speed);
	g_PID_Inc.pid.settarget(&DirectionAngle.dtvPid,0);
	g_PID_Inc.pid.settarget(&LineOffset.dtvPid,offset);
	g_PID_Inc.pid.settarget(&DiffAngle.dtvPid,0);

	LAdjustSpeed = g_PID_Inc.pid.calculate(&MotorLeft.dtvPid,State.LMotorSpeed);
	LAdjustSpeed = g_PID_Inc.pid.outputLimit(&MotorLeft.dtvPid,LAdjustSpeed,12.762, -12.762);
	
	RAdjustSpeed = g_PID_Inc.pid.calculate(&MotorRight.dtvPid,State.RMotorSpeed);
	RAdjustSpeed = g_PID_Inc.pid.outputLimit(&MotorRight.dtvPid,RAdjustSpeed,12.762, -12.762);
	
	AngleDiff = g_PID_Inc.pid.calculate(&DiffAngle.dtvPid,State.DirectionAngle);
	AngleDiff = g_PID_Inc.pid.outputLimit(&DiffAngle.dtvPid,AngleDiff,2,-2);
	
	AdjustAngle = g_PID_Inc.pid.calculate(&DirectionAngle.dtvPid,State.DirectionAngle);
	AdjustAngle = g_PID_Inc.pid.outputLimit(&DirectionAngle.dtvPid,AdjustAngle,35, -35);
	
	AdjustOffsetAngle = g_PID_Inc.pid.calculate(&LineOffset.dtvPid,State.LineOffset);
	AdjustOffsetAngle = g_PID_Inc.pid.outputLimit(&LineOffset.dtvPid,AdjustOffsetAngle,5, -5);
	
	AdjustEqualAngle = coef*AdjustAngle + (1-coef)*AdjustOffsetAngle;
	
	Output.LSpeed = Output.LSpeed + LAdjustSpeed + AngleDiff;
	Output.RSpeed = Output.RSpeed + RAdjustSpeed - AngleDiff;
	Output.SAngle = Output.SAngle + AdjustEqualAngle;
	Power();
	
}

//转弯决策 
void Turning(float angle, float offset, float speed, float diff)
{
	
	float coef = 0.6;
	double LAdjustSpeed, RAdjustSpeed, AdjustAngle, AdjustOffsetAngle, AdjustEqualAngle;
	
	g_PID_Inc.pid.settarget(&MotorLeft.dtvPid,speed + diff);
	g_PID_Inc.pid.settarget(&MotorRight.dtvPid,speed - diff);
	g_PID_Inc.pid.settarget(&DirectionAngle.dtvPid,angle);
	g_PID_Inc.pid.settarget(&LineOffset.dtvPid,offset);

	LAdjustSpeed = g_PID_Inc.pid.calculate(&MotorLeft.dtvPid,State.LMotorSpeed);
	LAdjustSpeed = g_PID_Inc.pid.outputLimit(&MotorLeft.dtvPid,LAdjustSpeed,12.7, -12.762);
	
	RAdjustSpeed = g_PID_Inc.pid.calculate(&MotorRight.dtvPid,State.RMotorSpeed);
	RAdjustSpeed = g_PID_Inc.pid.outputLimit(&MotorRight.dtvPid,RAdjustSpeed,12.7, -12.762);
	
	AdjustAngle = g_PID_Inc.pid.calculate(&DirectionAngle.dtvPid,State.DirectionAngle);
	AdjustAngle = g_PID_Inc.pid.outputLimit(&DirectionAngle.dtvPid,AdjustAngle,35, -35);
	
	AdjustOffsetAngle = g_PID_Inc.pid.calculate(&LineOffset.dtvPid,State.LineOffset);
	AdjustOffsetAngle = g_PID_Inc.pid.outputLimit(&LineOffset.dtvPid,AdjustOffsetAngle,5, -5);
	
	AdjustEqualAngle = coef*AdjustAngle + (1-coef)*AdjustOffsetAngle;
	
	Output.LSpeed = Output.LSpeed + LAdjustSpeed;
	Output.RSpeed = Output.RSpeed + RAdjustSpeed;
	Output.SAngle = Output.SAngle + AdjustEqualAngle;
	Power();
	
}

//启动元件 
void Power()
{
	MotorPower((Output.LSpeed*4*100) / (15000*PI*0.0065) / 60);
	Motor2Power( - (Output.RSpeed*4*100) / (15000*PI*0.0065) / 60);
	Turn(1520 + 600 * RAD2DEG(2 * asin(1.3/3.2 * sin( DEG2RAD(Output.SAngle) / 2))) / 90);
}


