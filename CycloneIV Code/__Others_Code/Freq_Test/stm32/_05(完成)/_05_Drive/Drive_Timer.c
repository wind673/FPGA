/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : My_Timer.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Timer.h"
#include "User_Library.h" 
#include "OS_StartFile.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_Init()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : ����ϵͳʱ��  1us��
------------------------------------------------------------------------------*/
void TIM2_Init(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = 0xffffffff;//��װ��ֵ 32λ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@
	
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM2_IRQn; //��ʱ�� x �ж�							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_1 ; //��ռ���ȼ� 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;	
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC
 	TIM_Cmd(TIM2,ENABLE); //ʹ�ܶ�ʱ�� x												//@
/*---------------------------------------------------------------------------------------------*/
}   

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_Init()     
* @Description   : None 
* @Data          : 2016/3/18
* @Explain       : OSThread_Primary  1msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM3_Init(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period =OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//����ʱ��9�����ж�							//@
	
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM3_IRQn; //��ʱ�� x �ж�				//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_6 ; //��ռ���ȼ� 6
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //��Ӧ���ȼ� 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC		
 	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ�� x												//@
/*---------------------------------------------------------------------------------------------*/
}   
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_Init()     
* @Description   : None 
* @Data          : 2016/3/19
* @Explain       : OSThread_System  1msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM4_Init(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period =OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM4_IRQn; //��ʱ�� x �ж�							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_SYSTEM ; //��ռ���ȼ� 4
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC
 	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@
/*---------------------------------------------------------------------------------------------*/
}			
	
		
		
/**----------------------------------------------------------------------------
* @FunctionName  : TIM9_Init()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : OS_THREAD_5  1msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM9_Init(void)
{

	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler =168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM9, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM9,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM1_BRK_TIM9_IRQn; //��ʱ�� x �ж�							//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_3; //��ռ���ȼ� 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� _NVIC
 	TIM_Cmd(TIM9,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@ 
/*---------------------------------------------------------------------------------------------*/
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM10_Init()     
* @Description   : None 
* @Data          : 2016/4/19
* @Explain       : OS_THREAD_7  1msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM10_Init(void)
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM10, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM10,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM1_UP_TIM10_IRQn; //��ʱ�� x �ж�				//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= OS_THREAD_7 ; //��ռ���ȼ� 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC
 	TIM_Cmd(TIM10,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@
/*---------------------------------------------------------------------------------------------*/
}	
		
/**----------------------------------------------------------------------------
* @FunctionName  : TIM11_Init()     
* @Description   : None
* @Data          : 2016/7/20
* @Explain       : OS_THREAD_5  1msʱ��Ƭ
------------------------------------------------------------------------------*/
void TIM11_Init(void)
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = OS_TIME_SLICE-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM11, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM11,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM1_TRG_COM_TIM11_IRQn; //��ʱ�� x �ж�			//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 5 ; //��ռ���ȼ� 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC_
 	TIM_Cmd(TIM11,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@
/*---------------------------------------------------------------------------------------------*/
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM12_Init()     
* @Description   : ���������Ǳ�
* @Data          : 2016/7/20
* @Explain       : 0.1ms
------------------------------------------------------------------------------*/
void TIM12_Init(void)
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = 200000/MEASURING_ADC_LENTH - 1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 168 - 1;//Ԥ��Ƶ
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

/**----------------------------------------------------------------------------
* @FunctionName  : TIM13_Init()     
* @Description   : None 
* @Data          : 2016/7/20
* @Explain       : None
------------------------------------------------------------------------------*/
void TIM13_Init(void)
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
//����ʱ�Ӽ���ʼ��Ԥװֵ
/*---------------------------------------------------------------------------------------------*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE); ///ʹ�� TIMxʱ��				   //@
	TIM_TimeBaseStructure.TIM_Period = 20000-1;//��װ��ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = 168-1;//Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;//����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//�����ۼ�ģʽ������0��ʼ�ӵ����ֵ
	TIM_TimeBaseInit(TIM13, &TIM_TimeBaseStructure);//����						    		//@
	TIM_ITConfig(TIM13,TIM_IT_Update,ENABLE);//����ʱ�� �����ж�							//@ 
/*---------------------------------------------------------------------------------------------*/ 

//�����жϲ�
/*---------------------------------------------------------------------------------------------*/	
	NVIC_InitStructure.NVIC_IRQChannel= TIM8_UP_TIM13_IRQn; //��ʱ�� x �ж�			//@
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority= 5 ; //��ռ���ȼ� 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 0 ; //��Ӧ���ȼ�  
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);// ��ʼ�� NVIC_
 	TIM_Cmd(TIM13,ENABLE); //ʹ�ܶ�ʱ�� x				4								//@
/*---------------------------------------------------------------------------------------------*/
}	


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/












