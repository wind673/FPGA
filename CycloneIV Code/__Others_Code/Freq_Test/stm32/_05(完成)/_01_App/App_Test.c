/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : App_Test.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "App_Test.h"  
#include <stdio.h>  

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/
 
/* 全局变量声明 --------------------------------------------------------------*/
  
/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Test()     
* @Description   : None 
* @Data          : 2016/7/20
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Test_Main(void)		
{    
	int i = 0; 
	unsigned long int temp;
	double tem;
	char str[64] = {0};
	static int success = 0;  
	
	if(MessageFPGA.Receive_Flag == 1)
	{ 
		success ++;
		for(i = 0;i < 5;i++)
			OS_Num_Show(i*120,100,MessageFPGA.Receive_Buff[i],5,32,1); 
		for(i = 5;i < 10;i++)
			OS_Num_Show((i - 5)*120,200,MessageFPGA.Receive_Buff[i],5,32,1);
		 //将分散的32位数据整合
		temp= MessageFPGA.Receive_Buff[5]|(MessageFPGA.Receive_Buff[4]<<8)|(MessageFPGA.Receive_Buff[3]<<16)|(MessageFPGA.Receive_Buff[2]<<24);
		//--------------高频数据显示------------------------------ 
		OS_Num_Show(0,300,temp,10,32,1);
		
		//-------------------------------------------------------------------------
		
		
		//------------低频数据转换与显示----------------------------------
		tem=100000000.00f/temp; 
		sprintf(str,"%.3f",tem);	
		OS_String_Show(400, 300, (u8*)str, 32, 1);
		  
		MessageFPGA.Receive_Flag = 0;
	}
	
	MessageFPGA.Cnt = (MessageFPGA.Cnt + 1)%10;
	LED1 = !LED1;
	
	MessageFPGA.Send_Buff[1] = 6;									//4测量高频  6测量低频
	MessageFPGA.Send_Buff[2] = 23;
	MessageFPGA.Send_Buff[3] = 34;
	MessageFPGA.Send_Buff[4] = 45;
	MessageFPGA.Send_Buff[5] = 56;
	MessageFPGA.Send_Buff[6] = 67;
	MessageFPGA.Send_Buff[7] = 78;
	MessageFPGA.Send_Buff[8] = 123; 
	 
	OS_Num_Show(600,0,success,5,32,1); 
	OS_Num_Show(0,400,MessageFPGA.Cnt,5,32,1);
	
	
	MessageFPGA_Send();
	
	return 0;																	
}		
 			
unsigned int Test_Start(void)		
{    
	Usart3_Init(MESSAGE_BAUD); 
	Exti0_Init();
	
	return 0;																	
}	

Type_AppList App_Test = {Test_Main,NULL,Test_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"Test",100};			
																
																				
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/





