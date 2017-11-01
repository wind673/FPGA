/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_DAC.c
* @Description : None
* @Date        : 2016/7/10
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_DAC.h"


/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : DAC1_Init()     
* @Description   : None 
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/ 
void DAC1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//��ʹ�� PA ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��ʹ�� DAC ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//�ٳ�ʼ�� GPIO
	DAC_InitType.DAC_Trigger=DAC_Trigger_None; //��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0; //���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//�������ر�
	DAC_Init(DAC_Channel_1,&DAC_InitType); //�۳�ʼ�� DAC ͨ�� 1
	DAC_Cmd(DAC_Channel_1, ENABLE); //��ʹ�� DAC ͨ�� 1
	DAC_SetChannel1Data(DAC_Align_12b_R , 0); //��12 λ�Ҷ������ݸ�ʽ
	 
}


/**----------------------------------------------------------------------------
* @FunctionName  : Get_ADC_Average()
* @Description   : None
* @Data          : 2016/7/11
* @Explain       :
-------------------------------------------------------------------------------
����ͨ�� 1(PA4) �����ѹ
vol 0~3.3V
------------------------------------------------------------------------------*/
void DAC1_Vol_Set(u16 vol)
{
//	double temp = vol*4096/3.3; 
	DAC_SetChannel1Data(DAC_Align_12b_R,vol);//12 λ�Ҷ������ݸ�ʽ
}



/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





