truct  //����ǰ״̬ 
{

    float LMotorSpeed;          //������ٶ� (M/S)
    float RMotorSpeed;          //�Һ����ٶ� (M/S)
	float DirectionAngle;       //ƫ���     ( �� ��ƫΪ������ƫΪ�����м�Ϊ��)
    float LineOffset; 			//����ƫ���� ( M  ��ƫΪ������ƫΪ�����м�Ϊ��) 
    int Turn;					//�Ƿ���ת�䣬��Ϊ1������Ϊ0 
    int DrivingMode;			//��ʻģʽ��0Ϊ������ʻ��1Ϊ������ʻ(����������) 

}
State;

struct  //��������� (��ʵ������) 
{

    float LSpeed;          //������ٶ� (M/S)
    float RSpeed;          //�Һ����ٶ� (M/S)
	float SAngle;          //���ת��   ( �� ��ƫΪ������ƫΪ�����м�Ϊ��)
	 
}
Output;

struct Mode //�˶���Ϊģʽ���� 
{

	//�����̬PID����ϵ�� 
    const float Mkp;        //���� 
    const float Mki;        //���� 
	const float Mkd;        //΢�� 
	const float Mkc;		//����� (һ�㲻����1) 
	
	//ƫ���PD����ϵ�� 
    const float Dkp;        //���� 
	const float Dkd;        //΢�� 

	//����ƫ������̬PID����ϵ�� 
    const float Okp;        //���� 
    const float Oki;        //���� 
	const float Okd;        //΢�� 
	const float Okc;	    //����� (һ�㲻����1)
		
	//ƫ����ֲ��̬PID����ϵ�� 
    const float DAkp;       //���� 
    const float DAki;       //���� 
	const float DAkd;       //΢�� 
	const float DAkc;	    //����� (һ�㲻����1)

};
				   
                   //���� ���� ΢�� �����
struct Mode Normal  = {0,   0,   0,   0,   /*���*/
					   0,        0,        /*ƫ���*/
					   0,   0,   0,   0,   /*����ƫ����*/
					   0,   0,   0,   0};  /*ƫ��ǲ*/ 

struct Mode Radical = {0,   0,   0,   0,   /*���*/
					   0,        0,        /*ƫ���*/
					   0,   0,   0,   0,   /*����ƫ����*/
					   0,   0,   0,   0};  /*ƫ��ǲ*/


