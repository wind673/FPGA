/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Measuring.c
* @Description : �����Ǳ����
* @Date        : 2016/7/29
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
#include "App_Measuring.h"  
 
/* ˽�к궨�� ----------------------------------------------------------------*/  
#define SHOW_HANDLE(X)			OS_Decim_Show(16*6,460,X,4,0,16,1)
 		 	

#define ADC_OVR_CLEAR()			{	ADC1->SR &= ~(0x0001<<5); \
									ADC2->SR &= ~(0x0001<<5); \
									ADC3->SR &= ~(0x0001<<5);	}

#define ADC_OVR	(ADC1->SR << 5 ||ADC2->SR << 5||ADC3->SR << 5)
							 

									
/* ˽�У���̬���������� ------------------------------------------------------*/  
static Type_AppList App_Measuring_Show;
static Type_AppList App_Measuring_FFT;
static void Measuring_Analysis(void);	
static void Measuring_ADC_Spped(u32 T);

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
u8 	MeasuringMode = 0; 
Type_Measuring Measuring = {9999999.9f,9999999.9f,9999999.9f,9999999.9f,9999999.9f,9999999.9f};//����Сֵ��ʼ��
 
 
/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Measuring()     
* @Description   : �����Ǳ�
* @Data          : 2016/7/29
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Measuring_Main(void)		
{  	 
	static u32 LastT = 0;
	u32 tempT = 0;
	
	if(Measuring.ADC_Flag == MEASURING_COMPLETE)
	{
		Measuring_Analysis();//���ݷ���     
		App_VoltageGain.AppMain(); 
		tempT = 1000000/Measuring.Freq; 
		if(LastT != tempT)
		{
			LastT = tempT; 
			if(Measuring.Freq < 110)
			{ 
				Measuring_ADC_Spped(tempT); 
				OS_String_Show(600,120,(u8*)"ʹ�õ����ڣ�",16,1); OS_Num_Show(600+16*6,120,tempT,9,16,1);   	
			}
		}
		 
		
		Measuring.ADC_Flag = MEASURING_START;//���¿�ʼADC�ɼ� 
	}
	 
	return 0;																	
}		
 
unsigned int Measuring_Start(void)		
{	
	static u8 first = 0;	
	if(first == 0)
	{ 
		first = 1;		
		ADC1_Init();	
		ADC2_Init();	 
		ADC3_DMA2_Init();	
		TIM12_Init();//���ڲ�AD	 
		OSTask_Creat(&App_Measuring_Show);   
		OSTask_Creat(&App_Measuring_FFT);    
		OSTask_Creat(&App_PhaseShift);	//�̿�����	  
		OSTask_Creat(&App_Frequency);	//��Ƶ 
		App_VoltageGain.AppStart();	
		
	}   
	return 0;
} 
Type_AppList App_Measuring = {Measuring_Main,NULL,Measuring_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
								(u8*)"Measuring",200};	
								
								
/**----------------------------------------------------------------------------
* @FunctionName  : Measuring_Analysis()     
* @Description   : �����Ǳ����ݷ���
* @Data          : 2016/7/29
* @Explain       : None
------------------------------------------------------------------------------*/								
static void Measuring_Analysis(void)		
{	 
	u16 i = 0;
	Measuring.Volt_Max = 0.0f;
	Measuring.Volt_Min = 999999.0f; 
	Measuring.Elect_Max = 0.0f;
	Measuring.Elect_Min = 999999.0f;
	Measuring.CountP = 0.0f; 
	
	for(i = 0;i < MEASURING_ADC_LENTH;i++)//��ѯ���ֵ����Сֵ
	{  
		if(Measuring.Volt_Max < Measuring.ADC1_Buff[i])		   Measuring.Volt_Max = Measuring.ADC1_Buff[i]; 
		if(Measuring.Volt_Min > Measuring.ADC1_Buff[i])        Measuring.Volt_Min = Measuring.ADC1_Buff[i];   
		
		if(Measuring.Elect_Max < Measuring.ADC2_Buff[i]) 	   Measuring.Elect_Max = Measuring.ADC2_Buff[i]; 
		if(Measuring.Elect_Min > Measuring.ADC2_Buff[i]) 	   Measuring.Elect_Min = Measuring.ADC2_Buff[i];
		  
	}  
	for(i = 0;i < MEASURING_ADC_LENTH;i++)//ƫ�õ�0
	{  
		Measuring.ADC1_Buff[i] = (Measuring.ADC1_Buff[i] - Measuring.Volt_Min)/Volt_Zoom;  
		Measuring.ADC2_Buff[i] = (Measuring.ADC2_Buff[i] - Measuring.Elect_Min)/Volt_Zoom;    
	}  
	Measuring.ReallyVpp = (Measuring.Volt_Max - Measuring.Volt_Min)/100.0f;
	Measuring.Volt_Max = (Measuring.Volt_Max - Measuring.Volt_Min)/Volt_Zoom;
	Measuring.Elect_Max = (Measuring.Elect_Max - Measuring.Elect_Min)/Volt_Zoom;
	Measuring.Volt_Min = 0;
	Measuring.Elect_Min = 0;
	
	Measuring.CountS = ((Measuring.Volt_Max))*((Measuring.Elect_Max))/8.0f; //���ڹ���	 
	for(i = 0;i < MEASURING_ADC_LENTH;i++) 
		Measuring.CountP += ((Measuring.ADC1_Buff[i] - Measuring.Volt_Max/2)*((Measuring.ADC2_Buff[i] - Measuring.Elect_Max/2)))/MEASURING_ADC_LENTH;//�й�����(����) 
	Measuring.CountQ = sqrt(Measuring.CountS*Measuring.CountS - Measuring.CountP*Measuring.CountP);//�޹�����   
	Measuring.CountPF = Measuring.CountP/Measuring.CountS;//��������  
	Measuring.Freq = g_Freq;//Ƶ��
	Measuring.EffecVolt = Measuring.Volt_Max/(2.0f*sqrt(2));//��ѹ��Чֵ
	Measuring.EffecElect = Measuring.Elect_Max/(2.0f*sqrt(2));//������Чֵ	
	
	if(Measuring.g_EffecVolt_Max < Measuring.EffecVolt)  Measuring.g_EffecVolt_Max = Measuring.EffecVolt;
	if(Measuring.g_EffecVolt_Min > Measuring.EffecVolt)  Measuring.g_EffecVolt_Min = Measuring.EffecVolt;
	if(Measuring.g_EffecElect_Max < Measuring.EffecElect)  Measuring.g_EffecElect_Max = Measuring.EffecElect;
	if(Measuring.g_EffecElect_Min > Measuring.EffecElect) Measuring.g_EffecElect_Min = Measuring.EffecElect;
	
	if(Measuring.g_P_Max < Measuring.CountP)  Measuring.g_P_Max = Measuring.CountP;		
	if(Measuring.g_P_Min > Measuring.CountP)  Measuring.g_P_Min = Measuring.CountP;		
	if(Measuring.g_Q_Max < Measuring.CountQ)  Measuring.g_Q_Max = Measuring.CountQ;		
	if(Measuring.g_Q_Min > Measuring.CountQ)  Measuring.g_Q_Min = Measuring.CountQ;		
	
	if(Measuring.FFT_Flag == MEASURING_START)//ת�����ݸ�FFT
	{ 
		for(i = 0;i < MEASURING_ADC_LENTH;i++)	
			Measuring.FFT_Buff[i] = (Measuring.ADC1_Buff[i])/100; 	
		
		Measuring.FFT_Flag = MEASURING_COMPLETE;	
	} 
 
	
}  
	
/**----------------------------------------------------------------------------
* @FunctionName  : �����Ǳ�FFT����()     	
* @Description   : FFT	
* @Data          : 2016/7/29	
* @Explain       : None	
------------------------------------------------------------------------------*/
unsigned int Measuring_FFT_Main(void)
{   
	u16 i = 0,BasisX1 = 1,BasisX2 = 1,BasisX3 = 1,temp = 0;
	u16 PointNum = 1;
	static double LastFFT_THD[2] = {0.0f};
	double  FFT_THD = 0.0f;//ʧ���
	u8 ERROR_Flag = 0;
	static u8 cnt = 0;
	 
	ERROR_HANDLE(0);	 
	if(Measuring.FFT_Flag == MEASURING_COMPLETE)
	{  
		ERROR_HANDLE(1);
		if(Measuring.Freq > 100)
		{  
			if(ADC_OVR) ADC_OVR_CLEAR();//ADC�������
			
			if(Measuring.Freq < 1500)		ADC3_DMA2_Reload(5); 
				 
			else ADC3_DMA2_Reload(0);   
			
//			while(DMA_GetFlagStatus(DMA2_Stream1,DMA_FLAG_TCIF1) != SET){}
			ERROR_HANDLE(2);
			OSdelay_ms(100);	
			PointNum = ADC_Waveform_Get(ADC3_DMA2_Buff,ADC3_DMA2_LENTH,Measuring.FFT_Buff,MEASURING_ADC_LENTH); 
		}
		ERROR_HANDLE(3);	
		if(PointNum)//û�е����򲻸�������
		{
			Measuring.FFT_Basis = 0;
			Measuring.FFT_HarmonicSum = 0; 
			FFT_Exchange_Measuring();//FFT�任 
			ERROR_HANDLE(4);	
			for(i = 1;i<MEASURING_ADC_LENTH/2;i++)
			{
				if(Measuring.FFT_Basis < Measuring.FFT_Buff[i])
					{
						Measuring.FFT_Basis = Measuring.FFT_Buff[i];
						BasisX1 = i;
					}
				
			} 
			temp = 0;
			ERROR_HANDLE(5);	
			for(i = BasisX1+1;i<MEASURING_ADC_LENTH/2;i++)
			{
				if(temp < Measuring.FFT_Buff[i])
					{temp = Measuring.FFT_Buff[i];BasisX2 = i;}
				
			}
			temp = 0;
			ERROR_HANDLE(6);	
			for(i = BasisX2+1;i<MEASURING_ADC_LENTH/2;i++)
			{
				if(temp < Measuring.FFT_Buff[i])
					{temp = Measuring.FFT_Buff[i];BasisX3 = i;}
				
			}
			ERROR_HANDLE(7);				
			
			
			for(i = BasisX1*2;i<MEASURING_ADC_LENTH/2;i+=BasisX1)
			{ 
				Measuring.FFT_HarmonicSum += pow(Measuring.FFT_Buff[i],2); 
			}
			
			
			ERROR_HANDLE(8);					
			Measuring.FFT_HarmonicSum = sqrt(Measuring.FFT_HarmonicSum); //г���ܺ�
			 
			FFT_THD = Measuring.FFT_HarmonicSum/Measuring.FFT_Basis;//ʧ��Ȳ��� 
			
			Measuring.FFT_THD = FFT_THD;
			 
			if(fabs(LastFFT_THD[0] - FFT_THD) > 0.01)//�˵���Ƶ����	
			{
				if(FFT_THD != LastFFT_THD[1])	ERROR_Flag = 1;
				LastFFT_THD[1] = LastFFT_THD[0];
				LastFFT_THD[0] = FFT_THD; 
			}
			
			
			if(ERROR_Flag == 0)//û�д���
			{ 
				OS_FFT_Draw_Double(500,150,750,350,Measuring.FFT_Buff,1,1,1.0f/1.0f);
				ERROR_HANDLE(9);	
				OS_Decim_Show(500,360,BasisX1,4,1,16,1);ERROR_HANDLE(10);	
				OS_Decim_Show(600,360,BasisX2,4,1,16,1);ERROR_HANDLE(11);	
				OS_Decim_Show(700,360,BasisX3,4,1,16,1);ERROR_HANDLE(12);	
				
				OS_String_Show(500,400,(u8*)"������",16,1);		OS_Decim_Show(500 + 16*5,400,Measuring.FFT_Basis,7,2,16,1);  ERROR_HANDLE(13);	
				OS_String_Show(500,420,(u8*)"г��֮�ͣ�",16,1);	OS_Decim_Show(500 + 16*5,420,Measuring.FFT_HarmonicSum,7,2,16,1); ERROR_HANDLE(14);	
				OS_String_Show(500,440,(u8*)"ʧ��ȣ�",16,1);	OS_Decim_Show(500 + 16*5,440,FFT_THD,2,4,16,1);  ERROR_HANDLE(15);	
			}
			ERROR_HANDLE(16);		
		}
		 
		OS_Decim_Show(16*12,460,cnt++,4,0,16,1);
		
		SHOW_HANDLE(ERROR_Flag);
		Measuring.FFT_Flag = MEASURING_START;//�ٴο���FFTת���ɼ�
	}
	
	return 0;
}
static Type_AppList App_Measuring_FFT = {Measuring_FFT_Main,NULL,NULL,NULL, \
										OS_STATE_ACTIVE,OS_THREAD_FREE, \
										(u8*)"Measuring_FFT",10};	
	
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : �����Ǳ���ʾ����()     	
* @Description   : �����Ǳ�	
* @Data          : 2016/7/29	
* @Explain       : None	
------------------------------------------------------------------------------*/
unsigned int Measuring_Show_Main(void)
{   
	u16 TempColor = TextColor;
	TextColor = WHITE;
	
	OS_String_Show(300,20,(u8*)"�����Ǳ�",32,1);  	
	 
//	OS_String_Show(20,60,(u8*)"���������PF1~12  ADC1,2  PE4",24,1);  
//	OS_String_Show(50,90, (u8*)"PF1 | PF2 |  PF3   PF4    |",16,1);   
//	OS_String_Show(50,106,(u8*)"SCL | SDA |  �̵���1,2    |",16,1);   
//		
//	OS_String_Show(300,90, (u8*)"ADC1 | ADC2 |  PE4 |   ",16,1);   
//	OS_String_Show(300,106,(u8*)"��ѹ | ���� |  ��Ƶ|  ",16,1);  
		
//	OS_String_Show(50,130,(u8*)"-------------------------------------------------------",16,1);     
//	 
//	OS_String_Show(50,150,(u8*)"     PF5,7,9,11           |",16,1);    
//	OS_String_Show(50,166,(u8*)"����:MUTE,CLK,SDI,CS      |",16,1);
//		
//	OS_String_Show(300,150,(u8*)"     PF6,8,10,12      ",16,1);    
//	OS_String_Show(300,166,(u8*)"��ѹ:MUTE,CLK,SDI,CS  ",16,1);
//		  
//	OS_String_Show(20,200,(u8*)"������ʾ��",24,1);   
	
	 
	OS_String_Show(50,230,(u8*)"���ڹ��ʣ�",16,1);  OS_Decim_Show(50+16*5,230,Measuring.CountS,5,3,16,1);  
	OS_String_Show(50,246,(u8*)"�й����ʣ�",16,1);  OS_Decim_Show(50+16*5,246,Measuring.CountP,5,3,16,1);  
	OS_String_Show(50,262,(u8*)"�޹����ʣ�",16,1);  OS_Decim_Show(50+16*5,262,Measuring.CountQ,5,3,16,1);  
	OS_String_Show(50,278,(u8*)"����������",16,1);  OS_Decim_Show(50+16*5,278,Measuring.CountPF,5,3,16,1);  
		
	OS_String_Show(225,230, (u8*)"||  ��ѹ��Чֵ��",16,1); OS_Decim_Show(225+16*8,230,Measuring.EffecVolt,5,3,16,1);  
	OS_String_Show(225,246, (u8*)"||  ������Чֵ��",16,1); OS_Decim_Show(225+16*8,246,Measuring.EffecElect,5,3,16,1);
	OS_String_Show(225,262, (u8*)"||  ��ѹ���ֵ��",16,1); OS_Decim_Show(225+16*8,262,Measuring.Volt_Max,5,3,16,1);  
	OS_String_Show(225,278, (u8*)"||  �������ֵ��",16,1); OS_Decim_Show(225+16*8,278,Measuring.Elect_Max,5,3,16,1);
		  
	OS_String_Show(50,310,(u8*)"��ѹ��Чֵ���ֵ:",16,1); OS_Decim_Show(50+16*9,310,Measuring.g_EffecVolt_Max,5,3,16,1);  
	OS_String_Show(50,330,(u8*)"��ѹ��Чֵ��Сֵ:",16,1); OS_Decim_Show(50+16*9,330,Measuring.g_EffecVolt_Min,5,3,16,1);  
	OS_String_Show(50,350,(u8*)"������Чֵ���ֵ:",16,1); OS_Decim_Show(50+16*9,350,Measuring.g_EffecElect_Max,5,3,16,1);  
	OS_String_Show(50,370,(u8*)"������Чֵ��Сֵ:",16,1); OS_Decim_Show(50+16*9,370,Measuring.g_EffecElect_Min,5,3,16,1);  
	
	if(Measuring.Volt_Max > 477.0f) OS_String_Show(20+5*24,200,(u8*)"���棡���� �ѳ���������Χ ",24,1);//������ָʾ
	else									OS_String_Show(20+5*24,200,(u8*)"���ڲ����У�һ������......",24,1);//������ָʾ
	
	OS_String_Show(600,50,(u8*)"Ƶ�ʣ�",16,1); OS_Num_Show(600+16*4,50,Measuring.Freq ,9,16,1);  
	OS_String_Show(600,70,(u8*)"���ڣ�",16,1); OS_Num_Show(600+16*4,70,Measuring.T,9,16,1);   	
	OS_String_Show(600,90,(u8*)"���ţ�",16,1); OS_Decim_Show(600+16*3,90,Volt_Zoom,5,3,16,1); 
	
	TextColor = TempColor;
	
	
	return 0;
}
static Type_AppList App_Measuring_Show = {Measuring_Show_Main,NULL,NULL,NULL, \
										OS_STATE_ACTIVE,OS_THREAD_7, \
										(u8*)"Measuring_Show",200};	

										
static void Measuring_ADC_Spped(u32 T)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	//����ʱ�Ӽ���ʼ��Ԥװֵ
	/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = T*4/MEASURING_ADC_LENTH - 1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 42 - 1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM12,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
	/*---------------------------------------------------------------------------------------------*/ 

	//�����жϲ�
	/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM8_BRK_TIM12_IRQn; //��ʱ�� x �ж�			//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 2; //��ռ���ȼ� 4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC_
 	TIM_Cmd(TIM12,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@ 
	/*---------------------------------------------------------------------------------------------*/
	 
}
										
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/




								
								
								

