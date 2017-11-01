/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Interrupt.c
* @Description : None
* @Date        : 2016/3/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Interrupt.h"
#include "User_Library.h" 
#include "OS_StartFile.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� -------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : TIM2_IRQHandler()     
* @Description   : ��ʱ 
* @Data          : 2016/3/19
* @Explain       : 1us * 0xffffffff
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update); //����жϱ�־λ 	
		OS_Clock ++; //��ֹʱ������������������
	}		
}	

/**----------------------------------------------------------------------------
* @FunctionName  : TIM3_IRQHandler()     
* @Description   : ���߳� 
* @Data          : 2016/3/18
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
//=========================================================================
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update); //����жϱ�־λ
		OSThread_6();
	}		
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM4_IRQHandler()     
* @Description   : ϵͳ�߳� 
* @Data          : 2016/3/19
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update); //����жϱ�־λ
		OSThread_4(); 
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_UP_TIM10_IRQHandler()     
* @Description   : �߳�7���ͼ��̣߳� 
* @Data          : 2016/4/19
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM1_UP_TIM10_IRQHandler(void)  
{ 
	if(TIM_GetITStatus(TIM10,TIM_IT_Update) != RESET)
	{ 
		TIM_ClearITPendingBit(TIM10,TIM_IT_Update); //����жϱ�־λ	
		OSThread_7();   			
			
			
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_BRK_TIM9_IRQHandler()     
* @Description   : ��Ƶ
* @Data          : 2016/4/19
* @Explain       : None
------------------------------------------------------------------------------*/ 
void TIM1_BRK_TIM9_IRQHandler(void)   
{
	static u16 _cnt = 0;
	if(TIM_GetITStatus(TIM9,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM9,TIM_IT_Update); //����жϱ�־λ
 		
		_cnt ++;	
		if(_cnt >= 1000)	
		{   								
			TIM_Cmd(TIM9,DISABLE);  		
			Exti_Disable(4);			
			g_FreqMod = FREQ_MODE_FREE;	
			_cnt = 0;	
		}
		 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : TIM1_TRG_COM_TIM11_IRQHandler()     
* @Description   : �߳�5���м��̣߳� 
* @Data          : 2016/7/20
* @Explain       : 1us * 1000 = 1ms 
------------------------------------------------------------------------------*/ 
void TIM1_TRG_COM_TIM11_IRQHandler(void)   
{ 
	if(TIM_GetITStatus(TIM11,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM11,TIM_IT_Update); //����жϱ�־λ 
		OSThread_5(); 	
		
		
	}
}
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM8_BRK_TIM12_IRQHandler()     
* @Description   : �����Ǳ�
* @Data          : 2016/7/22
* @Explain       : 10ms/50Hz
------------------------------------------------------------------------------*/ 
void  TIM8_BRK_TIM12_IRQHandler(void)   
{  
	if(TIM_GetITStatus(TIM12,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM12,TIM_IT_Update); //����жϱ�־λ 
		if(Measuring.ADC_Flag != MEASURING_START) return;
		
		Measuring.ADC1_Buff[Measuring.ADC_Cnt] = ADC_Result_Get(1,0)*3.3/4096*100; //��ѹ
		Measuring.ADC2_Buff[Measuring.ADC_Cnt] = ADC_Result_Get(2,0)*3.3/4096*10; //����
		Measuring.ADC_Cnt ++;
		
		if(Measuring.ADC_Cnt >= MEASURING_ADC_LENTH)
		{
			Measuring.ADC_Cnt = 0;				
			Measuring.ADC_Flag = MEASURING_COMPLETE; 
		}
	} 
}		
	
	
/**----------------------------------------------------------------------------
* @FunctionName  : TIM8_UP_TIM13_IRQHandler()     
* @Description   : None
* @Data          : 2016/7/20
* @Explain       : None
------------------------------------------------------------------------------*/ 
void  TIM8_UP_TIM13_IRQHandler(void)   
{ 
	if(TIM_GetITStatus(TIM13,TIM_IT_Update) != RESET)
	{
		TIM_ClearITPendingBit(TIM13,TIM_IT_Update); //����жϱ�־λ 
		 
		
	} 
}





/**----------------------------------------------------------------------------
* @FunctionName  : EXTI0_IRQHandler()     
* @Description   : �ⲿ�ж�0������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI0_IRQHandler(void)
{ 
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
	{ 
		MessageFPGA.Cnt ++;
		MessageFPGA.Send_Buff[1] = MessageFPGA.Cnt;
		MessageFPGA_Send();
		LED1 = !LED1;
		delay_ms(3000);
		
		EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI1_IRQHandler()     
* @Description   : �ⲿ�ж�1������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line1)!=RESET)
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line1); //���LINE1�ϵ��жϱ�־λ 
	}
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : EXTI2_IRQHandler()     
* @Description   : �ⲿ�ж�2������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI2_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line2)!=RESET)
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line2); //���LINE2�ϵ��жϱ�־λ 
	}
}

/**----------------------------------------------------------------------------
* @FunctionName  : EXTI3_IRQHandler()     
* @Description   : �ⲿ�ж�3������� 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void EXTI3_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line3)!=RESET)	
	{ 
 
		EXTI_ClearITPendingBit(EXTI_Line3); //���LINE3�ϵ��жϱ�־λ 
	}
}


/**----------------------------------------------------------------------------
* @FunctionName  : EXTI4_IRQHandler()     
* @Description   : �ⲿ�ж�4������� 
* @Data          : 2016/7/12
* @Explain       : ������Ƶ��PE4��
------------------------------------------------------------------------------*/ 
void EXTI4_IRQHandler(void)
{
	static u32 TimeRecord[3] = {0};		
	static u8 _cnt = 0,OS_ClockNow;
	u32 TempTime = 	0;
	TempTime = TIM_GetCounter(TIM2);
	if(EXTI_GetITStatus(EXTI_Line4)!=RESET)
	{ 
		if(g_FreqMod == FREQ_MODE_HF) //��Ƶ�����				
		{  	
			g_FreqCnt ++; 		
		}
		
		else if(g_FreqMod == FREQ_MODE_LF) //��Ƶ��ʱ��	
		{
			if(_cnt == 0) OS_ClockNow = OS_Clock;	//��¼��ǰ���ֵ
			
			TimeRecord[_cnt++] = TempTime;	//��¼ʱ��
			
			if(_cnt >= 2)
			{
				g_FreqMod = FREQ_MODE_FREE;		
				_cnt = 0; 	
				g_FreqT = (OS_Clock - OS_ClockNow)*0xffffffff + TimeRecord[1] - TimeRecord[0];		
			}			
		}			
		 
		else if(g_FreqMod == FREQ_MODE_DUTY) //��ռ�ձ�	
		{
			if(_cnt == 0) OS_ClockNow = OS_Clock; //��¼��ǰ���ֵ	
			
			TimeRecord[_cnt++] = TempTime; //��¼ʱ��	
			
			if(_cnt == 2) 
			{	  
				g_FreqT_H = (OS_Clock - OS_ClockNow)*0xffffffff + TimeRecord[1] - TimeRecord[0];		 
			}
			
			if(_cnt >= 3) 
			{	
				g_FreqMod = FREQ_MODE_FREE;		
				_cnt = 0; 	
				g_FreqT = (OS_Clock - OS_ClockNow)*0xffffffff + TimeRecord[2] - TimeRecord[0];		 
			}	
				
		}	
			
		else if(g_FreqMod == FREQ_MODE_FREE)	
		{
			_cnt = 0; 
			OS_ClockNow = OS_Clock; 
			TimeRecord[0] = 0; 
			TimeRecord[1] = 0; 
			TimeRecord[2] = 0; 
			Exti_Disable(4);	
		}	
		
		EXTI_ClearITPendingBit(EXTI_Line4); //���LINE4�ϵ��жϱ�־λ 
	}
}
 
/**----------------------------------------------------------------------------
* @FunctionName  : USART3_IRQHandler()     
* @Description   : ����1������� 
* @Data          : 2016/11/11
* @Explain       : ������ӻ�ͨ��
------------------------------------------------------------------------------*/ 
void USART3_IRQHandler(void)                	//����1�жϷ������
{   
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{ 
		MessageFPGA_Receive();
		
	} 
	
}









/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





