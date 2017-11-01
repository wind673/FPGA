/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 
-------------------------------------------------------------------------------
�����ң���0~MESSAGE_LENTH - 1  
����Ӹߵ���λ�����磬CRC16[0] �� CRC16_H
*=============================================================================*/

/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "User_Library.h" 

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/
#define MESSAGE_LENTH  				10 
#define MESSAGE_BAUD   				9600 //���ڲ�����
#define MESSAGE_GAP   			 	10000 //ÿ���ֽ�֮��ʱ����Ϊ �� 10ms 


/* �ṹ������ ----------------------------------------------------------------*/  
typedef struct
{
	u8  Receive_Buff[MESSAGE_LENTH];  //���ջ���,���USART_REC_LEN���ֽ�. 
	u8  Send_Buff[MESSAGE_LENTH];     //���ͻ���,���USART_REC_LEN���ֽ�.   
	u8  Receive_Flag;  
	u8  Cnt;
}type_Message;
  

/* ȫ�ֱ������� --------------------------------------------------------------*/    
extern type_Message 	MessageFPGA;   

/* ȫ�ֺ������� --------------------------------------------------------------*/  
void MessageFPGA_Send(void); 
void MessageFPGA_Receive(void);
	
void Message_CRC8_Count(u8 *buff);
u8 Message_CRC8_Test(u8 *buff);
 
 
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/


























