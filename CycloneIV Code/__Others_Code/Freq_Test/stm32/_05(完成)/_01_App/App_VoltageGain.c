/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_VoltageGain.c
* @Description : ��ѹ����
* @Date        : 2016/7/29
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
#include "App_VoltageGain.h"  
#include <math.h>

/* ˽�к궨�� ----------------------------------------------------------------*/ 

/* ˽�У���̬���������� ------------------------------------------------------*/  
	
/* ȫ�ֱ������� --------------------------------------------------------------*/  
double Volt_Zoom = 0;
	
/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : VoltageGain()     
* @Description   : ��ѹ����
* @Data          : 2016/7/29
* @Explain       : None
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
unsigned int VoltageGain_Main(void)		
{  	 
	static int Voltage_Gain_Level = 0;
	
	/* �Զ����� -------------------------------------*/
	if(Voltage_Gain_Level > 0)
		if(Measuring.ReallyVpp > 3.2) Volt_Zoom = Voltage_Gain(--Voltage_Gain_Level);
	
	if(Voltage_Gain_Level < 67)
		if(Measuring.ReallyVpp < 2.5) Volt_Zoom = Voltage_Gain(++Voltage_Gain_Level);
	
	return 0;																	
}		

unsigned int VoltageGain_Start(void)		
{
	static u8 first = 0;
	if(first == 0)
	{ 
		first = 1; 
		PGA2310_Init();  
		Volt_Zoom = Voltage_Gain(0); 
		
	}   
	return 0;
} 
Type_AppList App_VoltageGain = {VoltageGain_Main,NULL,VoltageGain_Start,NULL, \
								OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
								(u8*)"VoltageGain",50};	
						
								
/**----------------------------------------------------------------------------
* @FunctionName  : Voltage_Gain()     
* @Description   : ��ѹ����
* @Data          : 2016/7/29
* @Explain       : 
-------------------------------------------------------------------------------
_dB: 0~67(��Ӧ-4~63dB)	
����ֵ���Ŵ���			
------------------------------------------------------------------------------*/
double Voltage_Gain(int _dB)
{
	double Temp; 
	if(_dB > 67) _dB = 67;	
	else if(_dB < 0) _dB = 0;	
	_dB	-= 4;		
	Temp = pow(10,(double)_dB/20.0f); 
	_dB += 192;//����ʽ(Page10)  
	PGA2310_Control(_dB,_dB); 
	return Temp;//ת���ɷŴ���
}	
	
	
								
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/

 

								
								
								

