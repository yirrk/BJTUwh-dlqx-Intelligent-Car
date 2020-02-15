truct  //车当前状态 
{

    float LMotorSpeed;          //左后轮速度 (M/S)
    float RMotorSpeed;          //右后轮速度 (M/S)
	float DirectionAngle;       //偏向角     ( ° 右偏为正，左偏为负，中间为零)
    float LineOffset; 			//中线偏移量 ( M  右偏为正，左偏为负，中间为零) 
    int Turn;					//是否在转弯，是为1，不是为0 
    int DrivingMode;			//驾驶模式，0为正常驾驶，1为激进驾驶(待开发功能) 

}
State;

struct  //控制输出量 (无实际意义) 
{

    float LSpeed;          //左后轮速度 (M/S)
    float RSpeed;          //右后轮速度 (M/S)
	float SAngle;          //舵机转角   ( ° 右偏为正，左偏为负，中间为零)
	 
}
Output;

struct Mode //运动行为模式参数 
{

	//电机动态PID控制系数 
    const float Mkp;        //比例 
    const float Mki;        //积分 
	const float Mkd;        //微分 
	const float Mkc;		//变积分 (一般不大于1) 
	
	//偏向角PD控制系数 
    const float Dkp;        //比例 
	const float Dkd;        //微分 

	//中线偏移量动态PID控制系数 
    const float Okp;        //比例 
    const float Oki;        //积分 
	const float Okd;        //微分 
	const float Okc;	    //变积分 (一般不大于1)
		
	//偏向角轮差动动态PID控制系数 
    const float DAkp;       //比例 
    const float DAki;       //积分 
	const float DAkd;       //微分 
	const float DAkc;	    //变积分 (一般不大于1)

};
				   
                   //比例 积分 微分 变积分
struct Mode Normal  = {0,   0,   0,   0,   /*电机*/
					   0,        0,        /*偏向角*/
					   0,   0,   0,   0,   /*中线偏移量*/
					   0,   0,   0,   0};  /*偏向角差动*/ 

struct Mode Radical = {0,   0,   0,   0,   /*电机*/
					   0,        0,        /*偏向角*/
					   0,   0,   0,   0,   /*中线偏移量*/
					   0,   0,   0,   0};  /*偏向角差动*/


