/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/
/**============================================================================
* @FileName    : Drive_Message.c
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind（谢玉伸）
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* 头文件包含 ----------------------------------------------------------------*/
#include "Drive_Message.h"

/* 私有宏定义 ----------------------------------------------------------------*/

/* 私有（静态）函数声明 ------------------------------------------------------*/

/* 全局变量定义 --------------------------------------------------------------*/ 
type_Message MessageFPGA = {0}; 

/* 全局函数编写 --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC8_Count()
* @Description   : CRC8计算
* @Data          : 2016/11/16
* @Explain       : 起始位，CRC校验位，结束位不计入计算
------------------------------------------------------------------------------*/
void Message_CRC8_Count(u8 *buff)
{
    u8 CRC_Result = 0;
    u8 byte; 

    for (byte = 1; byte < MESSAGE_LENTH - 1; byte++)//去掉起始码和终止码,两位CRC码
    {
        CRC_Result += buff[byte]*byte;
    } 
	
    buff[MESSAGE_LENTH - 1] = CRC_Result%256; //CRC_

}


/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC8_Test()
* @Description   : CRC8测试
* @Data          : 2016/11/16
* @Explain       : 起始位，CRC校验位，结束位不计入计算；校验成功返回1，否则返回0
------------------------------------------------------------------------------*/
u8 Message_CRC8_Test(u8 *buff)
{ 
	u8 CRC_Result = 0;
    u8 byte; 

    for (byte = 1; byte < MESSAGE_LENTH - 1; byte++)//去掉起始码和终止码,两位CRC码
    {
        CRC_Result += buff[byte]*byte;
    } 
	
    if(buff[MESSAGE_LENTH - 1] == CRC_Result%256) return 1; //CRC 
    else return 0;
}




/**----------------------------------------------------------------------------
* @FunctionName  : MessageFPGA_Receive()
* @Description   : FPGA通信接收
* @Data          : 2016/11/18
* @Explain       : 放置在串口接收中断中
------------------------------------------------------------------------------*/
void MessageFPGA_Receive(void)
{
    static u32 time = 0, Clock = 0;
    static u8 Receive_Cnt = 0;

    if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffffffff - time > MESSAGE_GAP)
    {
        Receive_Cnt = 0;
        MessageFPGA.Receive_Flag = 0;//开始接收
    }

    MessageFPGA.Receive_Buff[Receive_Cnt++] = USART_ReceiveData(USART3);//读取接收到的数据

    if(Receive_Cnt == MESSAGE_LENTH)
    {
        if(MessageFPGA.Receive_Buff[0] == 0xAA) 
			if(Message_CRC8_Test(MessageFPGA.Receive_Buff)) //CRC16校验  
				MessageFPGA.Receive_Flag = 1;//接收完毕
		
		
        Receive_Cnt = 0;
    }

    Receive_Cnt %= MESSAGE_LENTH;
    Clock = OS_Clock;
    time = TIM_GetCounter(TIM2);
}


/**----------------------------------------------------------------------------
* @FunctionName  : MessageFPGA_Send()
* @Description   : 发送给FPGA
* @Data          : 2016/11/15
* @Explain       : None
------------------------------------------------------------------------------*/
void MessageFPGA_Send(void)
{
    int i = 0;
    MessageFPGA.Send_Buff[0] = 0xaa;//起始符  
    Message_CRC8_Count(MessageFPGA.Send_Buff);
	USART_SendData(USART3,0x55); //FPGA第一个数据会丢失
	delay_ms(1);
    for(i = 0; i < MESSAGE_LENTH; i ++)
    {
        USART_SendData(USART3,MessageFPGA.Send_Buff[i]); //向从机发送数据
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET); //等待发送结束
		delay_ms(1);
    } 
	delay_ms(11);
}




/*******************************(C) COPYRIGHT 2016 Wind（谢玉伸）*********************************/




















