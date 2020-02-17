#include"Driving_Behaviour.c"

//ȫ����ʼ�� 
void Init()
{
	
	ControlInit();
	MotorInit();
	ServMotorInit();
	
}

//��ʻģʽѡ��(Normal��Radical) �����������Vehicle_State.h�� 
void ModeSelect(struct Mode Mode)
{
	 
	g_PID_Inc.pid.setParameter(&MotorLeft.dtvPid,      Mode.Mkp,  Mode.Mki,  Mode.Mkd,  Mode.Mkc );
	g_PID_Inc.pid.setParameter(&MotorLeft.dtvPid,      Mode.Mkp,  Mode.Mki,  Mode.Mkd,  Mode.Mkc );
	g_PID_Inc.pid.setParameter(&DirectionAngle.dtvPid, Mode.Dkp,  0,         Mode.Dkd,  0        );
	g_PID_Inc.pid.setParameter(&LineOffset.dtvPid,     Mode.Okp,  Mode.Oki,  Mode.Okd,  Mode.Okc );
	g_PID_Inc.pid.setParameter(&DiffAngle.dtvPid,      Mode.DAkp, Mode.DAki, Mode.DAkd, Mode.DAkc);
	
}

//��ʻ���ƣ��ڲ��޶�ʱ������Ҫ����ִ��
//��������turnflag���Ƿ�Ҫת�䣬��Ϊ1����Ϊ0 
//		  angle��ת��Ƕȣ�������0�м� 
//		  offset�������������ߵ�ƫ������������0�м�
//		  speed���ٶȣ�ǰ���������˸� 
//        diff��ת����٣���ת��ʱ���Һ���֮��Ӧ�����ٶȲ��Ҫ����ת�����ʵĲ�ͬ�ɾ��ߵ�Ԫ���м��� ������ֵΪ���Һ����ٶȲ��һ�� 
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

//��ֻ�Ǹ�ʾ����state����һ����6��ֵ������ȡ���Ƶķ�ʽ���� 
void ReportLSpeed(float LMotorSpeed)
{
    State.LMotorSpeed = LMotorSpeed;
}

