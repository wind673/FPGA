/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.h
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : 
-------------------------------------------------------------------------------
从左到右，从0~MESSAGE_LENTH - 1  
代表从高到低位，例如，CRC16[0] 是 CRC16_H
*=============================================================================*/

/* 防止重调用 ----------------------------------------------------------------*/
#ifndef __DRIVE_MESSAGE_H
#define __DRIVE_MESSAGE_H 

/* 头文件包含 ----------------------------------------------------------------*/  
#include "User_Library.h" 

/* 全局宏定义 ----------------------------------------------------------------*/
#define MESSAGE_LENTH  				10 
#define MESSAGE_BAUD   				9600 //串口波特率
#define MESSAGE_GAP   			 	10000 //每个字节之间时间间隔为 ： 10ms 


/* 结构体声明 ----------------------------------------------------------------*/  
typedef struct
{
	u8  Receive_Buff[MESSAGE_LENTH];  //接收缓冲,最大USART_REC_LEN个字节. 
	u8  Send_Buff[MESSAGE_LENTH];     //发送缓冲,最大USART_REC_LEN个字节.   
	u8  Receive_Flag;  
	u8  Cnt;
}type_Message;
  

/* 全局变量声明 --------------------------------------------------------------*/    
extern type_Message 	MessageFPGA;   

/* 全局函数声明 --------------------------------------------------------------*/  
void MessageFPGA_Send(void); 
void MessageFPGA_Receive(void);
	
void Message_CRC8_Count(u8 *buff);
u8 Message_CRC8_Test(u8 *buff);
 
 
#endif
/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/


























