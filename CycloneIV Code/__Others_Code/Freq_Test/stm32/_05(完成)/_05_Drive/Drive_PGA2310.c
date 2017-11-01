/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_PGA2310.c
* @Description : None
* @Date        : 2016/7/29
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_PGA2310.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
#define PGA2310_MUTE   		GPIOF_OUT(6)
#define PGA2310_CLK    		GPIOF_OUT(8) 
#define PGA2310_SDI   		GPIOF_OUT(10)
#define PGA2310_CS    		GPIOF_OUT(12)   

#define PGA2310_MUTE_1  	GPIOF_OUT(5)
#define PGA2310_CLK_1    	GPIOF_OUT(7) 
#define PGA2310_SDI_1    	GPIOF_OUT(9)
#define PGA2310_CS_1    	GPIOF_OUT(11)   


/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/

/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Init()
* @Description   : PGA2310��ʼ������
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void PGA2310_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_8|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOF, &GPIO_InitStructure);
    PGA2310_CLK = 1;
    PGA2310_SDI = 1;
    PGA2310_CS = 1;
    PGA2310_MUTE = 1;  
	
	PGA2310_CLK_1 = 1;
    PGA2310_SDI_1 = 1;
    PGA2310_CS_1 = 1;
    PGA2310_MUTE_1 = 1; 
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Mute()
* @Description   : PGA2310��������
* @Data          : 2016/7/21
* @Explain
-------------------------------------------------------------------------------
NewState : ENABLE or DISABLE
------------------------------------------------------------------------------*/
void PGA2310_Mute( FunctionalState NewState)
{
    if (NewState == ENABLE)
    {
        PGA2310_MUTE = 1;
		PGA2310_MUTE_1 = 1;
    }
    else
    {
        PGA2310_MUTE = 0;
		PGA2310_MUTE_1 = 0;
    }
}

 
/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Data_Send()
* @Description   : PGA2310��������
* @Data          : 2016/7/29
* @Explain
------------------------------------------------------------------------------- 
Data����ͨ���ڸ�8λ����ͨ���ڵ�8λ
------------------------------------------------------------------------------*/
void PGA2310_Data_Send(u16 Data)
{
    uint8_t i;
    PGA2310_CS = 0; //ʹ�ܣ���Ƭѡ 
	PGA2310_CS_1 = 0; //ʹ�ܣ���Ƭѡ 
    OSdelay_ms(1); 
    for(i = 0; i < 16; i++ )
    { 
        if( Data & 0x8000 )
        {
            PGA2310_SDI = 1;
			PGA2310_SDI_1 = 1;
        }		
        else	
        {	
            PGA2310_SDI = 0;
			PGA2310_SDI_1 = 0;
        } 	
		OSdelay_us(100);
        PGA2310_CLK = 1;
        PGA2310_CLK_1 = 1;
		
        OSdelay_us(100);
        PGA2310_CLK = 0; 
		PGA2310_CLK_1 = 0;
		
		Data <<= 1;
    }
    PGA2310_CS = 1; //ʧ��
	PGA2310_CS_1 = 1; //ʧ��
}


/**----------------------------------------------------------------------------
* @FunctionName  : PGA2310_Control()
* @Description   : PGA2310�Ŵ����
* @Data          : 2016/7/29
* @Explain
-------------------------------------------------------------------------------
Right: ��ͨ���Ŵ��� Left: ��ͨ���Ŵ���
���ݸ�ʽ����ͨ���ڸ�8λ����ͨ���ڵ�8λ
------------------------------------------------------------------------------*/
void PGA2310_Control(u8 Right, u8 Left)
{
    u16 Data;
    Data = Right;
    Data = (Data << 8) + Left;
    PGA2310_Data_Send(Data);
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/










