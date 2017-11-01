/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_x9421.c
* @Description : x9421���ֵ�λ������
* @Date        : 2016/7/29
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_x9421.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
#define  X9421_Address  0x5a  //��4λ��ַΪ0101���������ͱ�ʶ��������4λ��ַ��A3~A0�����״̬����

//�Ĵ���0~3
#define  X9421_REG   (0x03)
#define  X9421_REG0  (0x00)
#define  X9421_REG1  (0x01)
#define  X9421_REG2  (0x02)
#define  X9421_REG3  (0x03)

//���ֵ�λ��0~3��Digital Potentiometer��
#define  X9421_DP   (0x03<<2)
#define  X9421_DP0  (0x00<<2)
#define  X9421_DP1  (0x01<<2)
#define  X9421_DP2  (0x02<<2)
#define  X9421_DP3  (0x03<<2)

//ָ�� 
#define  ReadWCR       (0x09<<4)
#define  WriteWCR      (0x0a<<4)
#define  ReadREG       (0x0b<<4)
#define  WriteREG      (0x0c<<4)
#define  REGtoWCR_one  (0x0d<<4)
#define  WCRtoREG_one  (0x0e<<4)
#define  REGtoWCR_all  (0x01<<4)
#define  WCRtoREG_all  (0x08<<4)
#define  Inc_Dec_WCR   (0x02<<4)

#define  CM  (0x01<<7)  //������ʽ����Ϊ0ʱ��λ��������������Ϊ1ʱ����λ���������ڵĸ���ŵĵ�λ����������
#define  DW  (0x01<<6)  //��ֹ�����ˣ���Ϊ0ʱ������ʹ�ܣ�Ϊ1ʱ�����˱���ֹ����ʱ�������ǵ����ϸ���Ĳ����Ǹ��յ�



/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Init()
* @Description   : x9421��ʼ������
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void x9421_Init(void)
{
    /* ���ü̵���IO�� --------------------------------------*/
    GPIO_InitTypeDef  GPIO_InitStructure;
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

    /* ����IIC --------------------------------------------*/
    IIC_Init();	
	
}



/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Control()
* @Description   : x9421���Ƴ���
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void x9421_Control(u8 num)  
{
    u8 DP = 0, byte[4] = {0, 0, 0, 0};
    if(num > 252) //�������ֵ
        return;

    if(num >= 189)
    {
        byte[3] = num - 189;
        byte[2] = 63;
        byte[1] = 63;
        byte[0] = 63;

    }
    else if(num >= 126)
    {
        byte[3] = 0;
        byte[2] = num - 126;
        byte[1] = 63;
        byte[0] = 63;
    }
    else if(num >= 63)
    {
        byte[3] = 0;
        byte[2] = 0;
        byte[1] = num - 63;
        byte[0] = 63;
    }
    else
    {
        byte[3] = 0;
        byte[2] = 0;
        byte[1] = 0;
        byte[0] = num;
    }
    for(DP = 0; DP < 4; DP++)
    {
        IIC_Start();
        IIC_Send_Byte(X9421_Address);
        IIC_Wait_Ack();
        IIC_Send_Byte(WriteWCR | (DP << 2));
        IIC_Wait_Ack();
        IIC_Send_Byte( (63 - byte[DP]) & 0x3f); //���ǻ�Ƭ�Ӹ߶ˣ�����(63- byte[DP])������ֱ����(byte[DP])
        IIC_Wait_Ack();
        IIC_Stop();
    }

}

/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Send()
* @Description   : x9421���ͳ���
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void x9421_Send(u8 DP, u8 num) //дָ��WCRֵ
{
    //  	num = 63-num;
    if(num > 63) //�������ֵ
        return;
	
    IIC_Start();
    IIC_Send_Byte(X9421_Address);
    IIC_Wait_Ack();
    IIC_Send_Byte(WriteWCR | (DP << 2));
    IIC_Wait_Ack();
    IIC_Send_Byte((num) & 0x3f); //��������
    IIC_Wait_Ack();
    IIC_Stop();
}


/**----------------------------------------------------------------------------
* @FunctionName  : x9421_Init()
* @Description   : x9421��ȡ����
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
u8 x9421_Read(u8 DP, u8 num) //��ָ��WCRֵ
{
    u8 byte = 0;
    IIC_Start();
    IIC_Send_Byte(X9421_Address);
    IIC_Wait_Ack();
    IIC_Send_Byte(WriteWCR | (DP << 2));
    IIC_Wait_Ack();
    byte = IIC_Read_Byte(1); //IIC_Send_Byte((num) & 0x3f); //��������
    IIC_Wait_Ack();
    IIC_Stop();
    return (byte);
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/










