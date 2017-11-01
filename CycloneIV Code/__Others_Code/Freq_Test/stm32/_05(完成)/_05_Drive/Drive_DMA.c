/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_DMA.c
* @Description : DMA�������
* @Date        : 2016/05/22
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/ 
#include "Drive_DMA.h"   
#define  ADC_PRECISION 			ADC_Resolution_12b 

/* ˽�к궨�� ----------------------------------------------------------------*/ 

/* ˽�У���̬���������� ------------------------------------------------------*/
 
/* ȫ�ֱ������� --------------------------------------------------------------*/ 
u16  ADC1_DMA2_Buff[ADC1_DMA2_LENTH] = {0};		 
u16  ADC3_DMA2_Buff[ADC3_DMA2_LENTH] = {0};	
u16  DAC1_DMA1_Buff[DAC1_DMA1_LENTH] = {0};		

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_DMA2_ReLoad()    	 
* @Description   : None 	
* @Data          : 2016/5/24	
* @Explain       : Speed: 0 ~ 7 ��8����λ����ֵԽС�ɼ��ٶ�Խ��	
------------------------------------------------------------------------------*/ 	
void ADC1_DMA2_Reload(u8 Speed)
{ 
	uint32_t ADC_SampleTime = ADC_SampleTime_3Cycles;
	DMA_InitTypeDef 	  DMA_InitStructure;  
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	GPIO_InitTypeDef  	  GPIO_InitStructure;
	switch(Speed)
	{
		case 0:	ADC_SampleTime = ADC_SampleTime_3Cycles;break;
		case 1:	ADC_SampleTime = ADC_SampleTime_15Cycles;break;
		case 2:	ADC_SampleTime = ADC_SampleTime_28Cycles;break;
		case 3:	ADC_SampleTime = ADC_SampleTime_56Cycles;break;
		case 4:	ADC_SampleTime = ADC_SampleTime_84Cycles;break;
		case 5:	ADC_SampleTime = ADC_SampleTime_112Cycles;break;
		case 6:	ADC_SampleTime = ADC_SampleTime_144Cycles;break;
		case 7:	ADC_SampleTime = ADC_SampleTime_480Cycles;break;
		default : ADC_SampleTime = ADC_SampleTime_3Cycles;break;;
	}
	
	/* DMA���� ------------------------------------*/ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
	DMA_DeInit(DMA2_Stream0);
	while (DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}//�ȴ�DMA������ 
		 
	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;  //ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//DMA�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC1_DMA2_Buff;//DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
	DMA_InitStructure.DMA_BufferSize = ADC1_DMA2_LENTH;//���ݴ����� 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ��ѭ��ģʽ DMA_Mode_Normal DMA_Mode_Circular
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;//�е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA2_Stream0,&DMA_InitStructure);//��ʼ��DMA Stream
	  
	DMA_SetCurrDataCounter(DMA2_Stream0,ADC1_DMA2_LENTH);//���ݴ�����   
	DMA_Cmd(DMA2_Stream0, ENABLE);                      //����DMA���� 	
	
	/* GPIO���� -----------------------------------*/  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA5 ͨ��5
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
	
	/* ADC���� ------------------------------------*/ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); //ʹ��ADC1ʱ�� 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,ENABLE);	  //ADC1��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1,DISABLE);  //��λ����	 
  
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA 
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
	ADC_InitStructure.ADC_Resolution = ADC_PRECISION;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ�� 
	
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime);  
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE); 
	ADC_DMACmd(ADC1,ENABLE);	
	ADC_Cmd(ADC1,ENABLE);//����ADת����	
	ADC_SoftwareStartConv(ADC1); //��������ɼ�   
	
}	

/**----------------------------------------------------------------------------
* @FunctionName  : ADC3_DMA2_Init()    	 
* @Description   : None 	
* @Data          : 2016/8/16	
* @Explain       : Speed: 0 ~ 7 ��8����λ����ֵԽС�ɼ��ٶ�Խ��	
------------------------------------------------------------------------------*/ 	
void ADC3_DMA2_Init(void)
{ 
	uint32_t ADC_SampleTime = ADC_SampleTime_3Cycles;
	DMA_InitTypeDef 	  DMA_InitStructure;  
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure;
	GPIO_InitTypeDef  	  GPIO_InitStructure;
  
	/* DMA���� ------------------------------------*/ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
	DMA_DeInit(DMA2_Stream1);
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}//�ȴ�DMA������ 
		 
	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;  //ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC3->DR;//DMA�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC3_DMA2_Buff;//DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
	DMA_InitStructure.DMA_BufferSize = ADC3_DMA2_LENTH;//���ݴ����� 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ��ѭ��ģʽ DMA_Mode_Normal DMA_Mode_Circular
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//�е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA2_Stream1,&DMA_InitStructure);//��ʼ��DMA Stream
	  
	DMA_SetCurrDataCounter(DMA2_Stream1,ADC3_DMA2_LENTH);//���ݴ�����   
	DMA_Cmd(DMA2_Stream1, ENABLE);                      //����DMA���� 	
	
	/* GPIO���� -----------------------------------*/  
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//ͨ��3
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
	
	/* ADC���� ------------------------------------*/ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE); //ʹ��ADCʱ�� 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);  //��λ����	 
  
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //_DMA 
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
	ADC_InitStructure.ADC_Resolution = ADC_PRECISION;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC3, &ADC_InitStructure);//ADC��ʼ�� 
	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_3,1,ADC_SampleTime);  
	ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE); 
	ADC_DMACmd(ADC3,ENABLE);	
	ADC_Cmd(ADC3,ENABLE);//����ADת����	
	ADC_SoftwareStartConv(ADC3); //��������ɼ�   
	
}	



/**----------------------------------------------------------------------------
* @FunctionName  : ADC3_DMA2_Reload()    	 
* @Description   : None 	
* @Data          : 2016/8/16	
* @Explain       : Speed: 0 ~ 7 ��8����λ����ֵԽС�ɼ��ٶ�Խ��	
------------------------------------------------------------------------------*/ 	
void ADC3_DMA2_Reload(u8 Speed)
{ 
	uint32_t ADC_SampleTime = ADC_SampleTime_3Cycles;
	DMA_InitTypeDef 	  DMA_InitStructure;  
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
	ADC_InitTypeDef       ADC_InitStructure; 
	switch(Speed)
	{
		case 0:	ADC_SampleTime = ADC_SampleTime_3Cycles;break;
		case 1:	ADC_SampleTime = ADC_SampleTime_15Cycles;break;
		case 2:	ADC_SampleTime = ADC_SampleTime_28Cycles;break;
		case 3:	ADC_SampleTime = ADC_SampleTime_56Cycles;break;
		case 4:	ADC_SampleTime = ADC_SampleTime_84Cycles;break;
		case 5:	ADC_SampleTime = ADC_SampleTime_112Cycles;break;
		case 6:	ADC_SampleTime = ADC_SampleTime_144Cycles;break;
		case 7:	ADC_SampleTime = ADC_SampleTime_480Cycles;break;
		default : ADC_SampleTime = ADC_SampleTime_3Cycles;break;;
	}
	
	/* DMA���� ------------------------------------*/ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2,ENABLE);//DMA2ʱ��ʹ�� 
	DMA_DeInit(DMA2_Stream1);
	while (DMA_GetCmdStatus(DMA2_Stream1) != DISABLE){}//�ȴ�DMA������ 
		 
	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_2;  //ͨ��ѡ��
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC3->DR;//DMA�����ַ
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ADC3_DMA2_Buff;//DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;//���赽�洢��ģʽ
	DMA_InitStructure.DMA_BufferSize = ADC3_DMA2_LENTH;//���ݴ����� 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;// ʹ��ѭ��ģʽ DMA_Mode_Normal DMA_Mode_Circular
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;//�е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA2_Stream1,&DMA_InitStructure);//��ʼ��DMA Stream
	  
	DMA_SetCurrDataCounter(DMA2_Stream1,ADC3_DMA2_LENTH);//���ݴ�����   
	DMA_Cmd(DMA2_Stream1, ENABLE);                      //����DMA���� 	
	
//	/* GPIO���� -----------------------------------*/  
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��  
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//ͨ��3
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
//	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
	
	/* ADC���� ------------------------------------*/ 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3,ENABLE); //ʹ��ADCʱ�� 
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,ENABLE);	  //ADC��λ
	RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3,DISABLE);  //��λ����	 
  
	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
	ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
	ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //DMA 
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//Ԥ��Ƶ4��Ƶ��ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz 
	ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
	ADC_InitStructure.ADC_Resolution = ADC_PRECISION;//12λģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ	
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//����ת��
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���	
	ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1 
	ADC_Init(ADC3, &ADC_InitStructure);//ADC��ʼ�� 
	
	ADC_RegularChannelConfig(ADC3,ADC_Channel_3,1,ADC_SampleTime);  
	ADC_DMARequestAfterLastTransferCmd(ADC3,ENABLE); 
	ADC_DMACmd(ADC3,ENABLE);	
	ADC_Cmd(ADC3,ENABLE);//����ADת����	
	ADC_SoftwareStartConv(ADC3); //��������ɼ�   
	
}	

/**----------------------------------------------------------------------------
* @FunctionName  : DMA1_Init()    	 
* @Description   : None 	
* @Data          : 2016/7/15	
* @Explain       : None	
------------------------------------------------------------------------------*/ 						
void DAC1_DMA1_Init(void)
{
	DMA_InitTypeDef 	  DMA_InitStructure;   
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	/* DMA���� ------------------------------------*/ 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1,ENABLE);//DMA2ʱ��ʹ�� 
	DMA_DeInit(DMA1_Stream5);
	while (DMA_GetCmdStatus(DMA1_Stream5) != DISABLE){}//�ȴ�DMA������ 
		
	/* ���� DMA Stream */
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;  //ͨ��ѡ�� 
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&DAC ->DHR12R1;//DMA�����ַ  DAC1
		
	DMA_InitStructure.DMA_Memory0BaseAddr = (u32)DAC1_DMA1_Buff;//DMA �洢��0��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;// 
	DMA_InitStructure.DMA_BufferSize = DAC1_DMA1_LENTH;//���ݴ����� 
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;//���������ģʽ
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;//�洢������ģʽ
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//�������ݳ���:16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;//�洢�����ݳ���:16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;// ʹ��ѭ��ģʽ DMA_Mode_Normal DMA_Mode_Circular
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;//�е����ȼ�
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;         
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;//�洢��ͻ�����δ���
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;//����ͻ�����δ���
	DMA_Init(DMA1_Stream5,&DMA_InitStructure);//��ʼ��DMA Stream 
	DMA_SetCurrDataCounter(DMA1_Stream5,DAC1_DMA1_LENTH);//���ݴ�����   
	DMA_Cmd(DMA1_Stream5, ENABLE);//����DMA���� 	  
	
	/* DAC���� ------------------------------------*/ 

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//��ʹ�� PA ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//��ʹ�� DAC ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);//�ٳ�ʼ�� GPIO
	DAC_InitType.DAC_Trigger=DAC_Trigger_T6_TRGO; //��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0; //���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;//�������ر�
	DAC_Init(DAC_Channel_1,&DAC_InitType); //�۳�ʼ�� DAC ͨ�� 1
	
	DAC_SetChannel1Data(DAC_Align_12b_R ,0); //��12 λ�Ҷ������ݸ�ʽ 
	
	DAC_DMACmd(DAC_Channel_1,ENABLE);  
	DAC_Cmd(DAC_Channel_1, ENABLE); //��ʹ�� DAC ͨ�� 1
	DAC1_DMA1_Reload(100);
   
}	

void DAC1_DMA1_Reload(u32 speed)
{	 
	u16 speed0 = 1;
	TIM_TimeBaseInitTypeDef    TIM_TimeBaseStructure; 
	if(speed == 0) return; 
	if(speed > 0xffff)  
	{
		speed0 = speed/0xffff;
		speed = speed%0xffff; 
	}
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
	TIM_TimeBaseStructure.TIM_Period = speed;          
	TIM_TimeBaseStructure.TIM_Prescaler = speed0;       
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure); 
	TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);  
	TIM_Cmd(TIM6, ENABLE);
  
	 
}
	
 
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





