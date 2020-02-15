#include"Driving_Behaviour.c"

//全部初始化 
void Init()
{
	
	ControlInit();
	MotorInit();
	ServMotorInit();
	
}

//驾驶模式选择(Normal或Radical) ，具体参数在Vehicle_State.h中 
void ModeSelect(struct Mode Mode)
{
	 
	g_PID_Inc.pid.setParameter(&MotorLeft.dtvPid,      Mode.Mkp,  Mode.Mki,  Mode.Mkd,  Mode.Mkc );
	g_PID_Inc.pid.setParameter(&MotorLeft.dtvPid,      Mode.Mkp,  Mode.Mki,  Mode.Mkd,  Mode.Mkc );
	g_PID_Inc.pid.setParameter(&DirectionAngle.dtvPid, Mode.Dkp,  0,         Mode.Dkd,  0        );
	g_PID_Inc.pid.setParameter(&LineOffset.dtvPid,     Mode.Okp,  Mode.Oki,  Mode.Okd,  Mode.Okc );
	g_PID_Inc.pid.setParameter(&DiffAngle.dtvPid,      Mode.DAkp, Mode.DAki, Mode.DAkd, Mode.DAkc);
	
}

//驾驶控制，内部无定时器，需要反复执行
//输入量：turnflag：是否要转弯，是为1不是为0 
//		  angle：转向角度：左负右正0中间 
//		  offset：距赛道中心线的偏移量，左负右正0中间
//		  speed：速度，前进正，后退负 
//        diff：转向差速，在转向时左右后轮之间应该有速度差，需要根据转弯曲率的不同由决策单元自行计算 ，输入值为左右后轮速度差的一半 
void Driving(int turnflag, float angle, float offset, float speed, float diff)
{
	if(turnflag == 0)
	{
		StraightDriving(offset, speed);
	}
	else if(turnflag == 1)
	{
		Turning(angle, offset, speed, diff);
	}
}

//这只是个示例，state里面一共有6个值，都采取类似的方式返回 
void ReportLSpeed(float LMotorSpeed)
{
    State.LMotorSpeed = LMotorSpeed;
}

