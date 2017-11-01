/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_DMA.h
* @Description : DMA�������
* @Date        : 2016/05/22 
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_DMA_H
#define __DRIVE_DMA_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
//#define 	ADC1_DMA2_LENTH 		4000
//#define 	DAC1_DMA1_LENTH			2000 
#define 	ADC1_DMA2_LENTH 		1
#define 	ADC3_DMA2_LENTH 		6000
#define 	DAC1_DMA1_LENTH			1


/* �ṹ������ ----------------------------------------------------------------*/ 
																	
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
extern Type_AppList APP_DMA;
extern u16 ADC1_DMA2_Buff[ADC1_DMA2_LENTH];
extern u16 ADC3_DMA2_Buff[ADC3_DMA2_LENTH];
extern u16 DAC1_DMA1_Buff[DAC1_DMA1_LENTH];



/* ȫ�ֺ������� --------------------------------------------------------------*/    
void ADC1_DMA2_Reload(u8 Speed); 

void ADC3_DMA2_Reload(u8 Speed);
void ADC3_DMA2_Init(void);	

void DAC1_DMA1_Init(void);
void DAC1_DMA1_Reload(u32 speed);

#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



