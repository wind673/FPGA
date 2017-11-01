/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Measuring.h
* @Description : FM��Ƶͨ��
* @Date        : 2016/7/29
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_MEASURING_H
#define __APP_MEASURING_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define MEASURING_MODE_PHASE				0
#define MEASURING_MODE_VOLTAGE				1
#define MEASURING_MODE_2					2
#define MEASURING_MODE_3					3
#define MEASURING_MODE_4					4

#define MEASURING_START						0
#define MEASURING_COMPLETE					1 

#define MEASURING_ADC_LENTH					1024

#define ERROR_HANDLE(X)			{OS_Decim_Show(0,460,X,4,0,16,1);}

/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct 
{   
	double 	Elect_Min;//��ǰ������Сֵ 
	double 	Volt_Min;//��ǰ��ѹ��Сֵ 
	double 	g_EffecElect_Min;//ȫ�ֵ�����Чֵ��Сֵ	
	double 	g_EffecVolt_Min;//ȫ�ֵ�ѹ��Чֵ��Сֵ	
	double 	g_P_Min;	 		
	double 	g_Q_Min;	
	 
	double 	Elect_Max;//��ǰ�������ֵ   
	double 	Volt_Max;//��ǰ��ѹ���ֵ 
	double 	ReallyVpp;//��ʵ�ɼ���Vpp

	
	double 	CountS;//���ڹ��� 
	double 	CountP;//�й����� 
	double 	CountQ;//�޹����� 
	double 	CountPF;//��������Ĺ������� PF = P/S 
	
	double  EffecVolt;//��Чֵ		
	double  EffecElect;		
	
	double 	g_EffecVolt_Max;	//ȫ����Чֵ				
	double 	g_EffecElect_Max;		
				 
	double 	g_P_Max;	//ȫ�ֹ���				
	double 	g_Q_Max;		
		  
	u32 	Freq;//Ƶ��
	double 	Duty;//ռ�ձ�
	u32 	T;//Ƶ��
	
	u8 		ADC_Flag;//��ʱ���ɼ�ADC��־ 
	u16 	ADC_Cnt;//��ʱ���ɼ�ADC����  
	double 	ADC1_Buff[MEASURING_ADC_LENTH];//0.1ms/Point,2000Point ->200ms ���� 
	double 	ADC2_Buff[MEASURING_ADC_LENTH];//0.1ms/Point,2000Point ->200ms ���� 
	
	u8 		FFT_Flag;//��ʱ���ɼ�ADC��־  
	double  FFT_Basis;//����
	double  FFT_HarmonicSum;//г���ܺ�
	
	double  FFT_Buff[MEASURING_ADC_LENTH];
	double  FFT_THD;//ʧ���
	
	u8 		Show_Flag;//��ʾ��־ 
}Type_Measuring;

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern u8 MeasuringMode;
extern Type_Measuring Measuring;

/* ȫ�ֺ������� --------------------------------------------------------------*/   
extern Type_AppList App_Measuring;


#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



