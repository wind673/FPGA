/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Message.c
* @Description : None
* @Date        : 2016/11/15
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Message.h"

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
type_Message MessageFPGA = {0}; 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC8_Count()
* @Description   : CRC8����
* @Data          : 2016/11/16
* @Explain       : ��ʼλ��CRCУ��λ������λ���������
------------------------------------------------------------------------------*/
void Message_CRC8_Count(u8 *buff)
{
    u8 CRC_Result = 0;
    u8 byte; 

    for (byte = 1; byte < MESSAGE_LENTH - 1; byte++)//ȥ����ʼ�����ֹ��,��λCRC��
    {
        CRC_Result += buff[byte]*byte;
    } 
	
    buff[MESSAGE_LENTH - 1] = CRC_Result%256; //CRC_

}


/**----------------------------------------------------------------------------
* @FunctionName  : Message_CRC8_Test()
* @Description   : CRC8����
* @Data          : 2016/11/16
* @Explain       : ��ʼλ��CRCУ��λ������λ��������㣻У��ɹ�����1�����򷵻�0
------------------------------------------------------------------------------*/
u8 Message_CRC8_Test(u8 *buff)
{ 
	u8 CRC_Result = 0;
    u8 byte; 

    for (byte = 1; byte < MESSAGE_LENTH - 1; byte++)//ȥ����ʼ�����ֹ��,��λCRC��
    {
        CRC_Result += buff[byte]*byte;
    } 
	
    if(buff[MESSAGE_LENTH - 1] == CRC_Result%256) return 1; //CRC 
    else return 0;
}




/**----------------------------------------------------------------------------
* @FunctionName  : MessageFPGA_Receive()
* @Description   : FPGAͨ�Ž���
* @Data          : 2016/11/18
* @Explain       : �����ڴ��ڽ����ж���
------------------------------------------------------------------------------*/
void MessageFPGA_Receive(void)
{
    static u32 time = 0, Clock = 0;
    static u8 Receive_Cnt = 0;

    if(TIM_GetCounter(TIM2) + (OS_Clock - Clock) * 0xffffffff - time > MESSAGE_GAP)
    {
        Receive_Cnt = 0;
        MessageFPGA.Receive_Flag = 0;//��ʼ����
    }

    MessageFPGA.Receive_Buff[Receive_Cnt++] = USART_ReceiveData(USART3);//��ȡ���յ�������

    if(Receive_Cnt == MESSAGE_LENTH)
    {
        if(MessageFPGA.Receive_Buff[0] == 0xAA) 
			if(Message_CRC8_Test(MessageFPGA.Receive_Buff)) //CRC16У��  
				MessageFPGA.Receive_Flag = 1;//�������
		
		
        Receive_Cnt = 0;
    }

    Receive_Cnt %= MESSAGE_LENTH;
    Clock = OS_Clock;
    time = TIM_GetCounter(TIM2);
}


/**----------------------------------------------------------------------------
* @FunctionName  : MessageFPGA_Send()
* @Description   : ���͸�FPGA
* @Data          : 2016/11/15
* @Explain       : None
------------------------------------------------------------------------------*/
void MessageFPGA_Send(void)
{
    int i = 0;
    MessageFPGA.Send_Buff[0] = 0xaa;//��ʼ��  
    Message_CRC8_Count(MessageFPGA.Send_Buff);
	USART_SendData(USART3,0x55); //FPGA��һ�����ݻᶪʧ
	delay_ms(1);
    for(i = 0; i < MESSAGE_LENTH; i ++)
    {
        USART_SendData(USART3,MessageFPGA.Send_Buff[i]); //��ӻ���������
        while(USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET); //�ȴ����ͽ���
		delay_ms(1);
    } 
	delay_ms(11);
}




/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/




















