/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_MCP42100.c
* @Description : None
* @Date        : 2016/7/21
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_MCP42100.h"							

/* ˽�к궨�� ----------------------------------------------------------------*/ 
 
/* ˽�У���̬���������� ------------------------------------------------------*/  
//static void SendByte(u8 Data);

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : MCP42100_Init()     
* @Description   : MCP42100��ʼ������ 
* @Data          : 2016/7/21
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void MCP42100_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure; 

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOʱ�� 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* ʹ�ܶ����� ---------------------------------------*/ 
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6; 	
	GPIO_Init(GPIOB,&GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;		
	GPIO_Init(GPIOC,&GPIO_InitStructure);	  
	MCP42100_DISABLE();		
}



/**----------------------------------------------------------------------------
* @FunctionName  : MCP42100_Control()     
* @Description   : MCP42100���Ƴ��� 
* @Data          : 2016/7/21
* @Explain        
------------------------------------------------------------------------------- 
_ch 	ͨ��
_value 	ֵ��0~255��
------------------------------------------------------------------------------*/
void MCP42100_Control(u8 _ch,u8 _value)
{	 
	u8 i = 0;
	MCP42100_ENABLE();	   
	for(i = 0;i<8;i++)
	{
		MCP42100_SCK_L(); 
		if(_ch & (0x80>>i)) MCP42100_SI_H();
		else MCP42100_SI_L();
		OSdelay_us(1);
		MCP42100_SCK_H();
		OSdelay_us(1);
	}
	for(i = 0;i<8;i++)
	{
		MCP42100_SCK_L();
		if(_value & (0x80>>i)) MCP42100_SI_H();
		else MCP42100_SI_L();
		OSdelay_us(1);
		MCP42100_SCK_H();
		OSdelay_us(1);
	}
	MCP42100_SCK_L();	 			
	MCP42100_DISABLE();						
}
 


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





















