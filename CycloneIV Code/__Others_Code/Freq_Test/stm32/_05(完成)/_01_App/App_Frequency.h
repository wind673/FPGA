/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Frequency.h
* @Description : None
* @Date        : 2016/7/12
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_FREQUENCY_H
#define __APP_FREQUENCY_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define FREQ_MODE_FREE  0
#define FREQ_MODE_LF   	1
#define FREQ_MODE_HF 	2
#define FREQ_MODE_DUTY 	3

/* �ṹ������ ----------------------------------------------------------------*/ 
																	
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern u8 g_FreqMod;
extern u32 g_FreqCnt;
extern double g_FreqT;  
extern double g_FreqT_H;
extern double g_Freq;  
extern double g_FreqDuty;

/* ȫ�ֺ������� --------------------------------------------------------------*/  
extern Type_AppList App_Frequency;
void Frequency_Mode_Low(void);
unsigned int Frequency_Main(void);

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



