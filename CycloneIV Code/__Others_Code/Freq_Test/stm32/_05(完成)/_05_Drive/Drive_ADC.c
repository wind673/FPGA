/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_ADC.c
* @Description : None
* @Date        : 2016/7/11
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_ADC.h" 

/* ˽�к궨�� ----------------------------------------------------------------*/

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : ADC1_Init()
* @Description   : None
* @Data          : 2016/7/11
* @Explain       : None
------------------------------------------------------------------------------*/
void ADC1_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //ʹ��ADC1ʱ��
	
    //�ȳ�ʼ��ADC1ͨ��1 IO��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, ENABLE);	//ADC1��λ
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);	//��λ����
	
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //�ر�DMAʹ��
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;//Ԥ��Ƶ2��Ƶ��//ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
    ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ	
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
    ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1
    ADC_Init(ADC1, &ADC_InitStructure);//ADC��ʼ��
 
    ADC_Cmd(ADC1, ENABLE);//����ADת����	

}

/**----------------------------------------------------------------------------
* @FunctionName  : ADC2_Init()
* @Description   : ADC2��ʼ������
* @Data          : 2016/7/24
* @Explain       : ������Ƶ�ɼ�
------------------------------------------------------------------------------*/
void ADC2_Init(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); //ʹ��ADC1ʱ��
	
    //�ȳ�ʼ��ADC1ͨ��1 IO��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;//PA
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//ģ������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//����������
    GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, ENABLE);	//ADC1��λ
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);	//��λ����
	
    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;//����ģʽ
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ��
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; //�ر�DMAʹ��
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;//Ԥ��Ƶ2��Ƶ��//ADCCLK=PCLK2/4=84/4=21Mhz,ADCʱ����ò�Ҫ����36Mhz
    ADC_CommonInit(&ADC_CommonInitStructure);//��ʼ��
		
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12λģʽ	
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//��ɨ��ģʽ
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//�ر�����ת��
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ֹ������⣬ʹ���������
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//�Ҷ���
    ADC_InitStructure.ADC_NbrOfConversion = 1;//1��ת���ڹ��������� Ҳ����ֻת����������1
    ADC_Init(ADC2, &ADC_InitStructure);//ADC��ʼ��
 
    ADC_Cmd(ADC2, ENABLE);//����ADת����	

}
 
/**----------------------------------------------------------------------------
* @FunctionName  : ADC_Result_Get()
* @Description   : ���ADCֵ
* @Data          : 2016/7/24
* @Explain       : 
------------------------------------------------------------------------------- 
Channel:  ADC_Channel_0~ADC_Channel_18 (��0~18Ҳ��) 
Speed  :  0~7(ԽСԽ��)
����ֵ:ת�����
------------------------------------------------------------------------------*/
u16 ADC_Result_Get(u8 Channel,u8 Speed)
{  
	ADC_TypeDef* ADCx = ADC1;
	if(Channel == 2) ADCx = ADC2;
	else if(Channel == 3) ADCx = ADC3;	 
	if(Speed > 7) Speed = 7; 
    ADC_RegularChannelConfig(ADCx,Channel, 1, Speed );	 
    ADC_SoftwareStartConv(ADCx);		//ʹ��ָ����ADC1�����ת���������� 
    while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC ));//�ȴ�ת������ 
    return ADC_GetConversionValue(ADCx);	//�������һ��ADC1�������ת�����
}





/**----------------------------------------------------------------------------
* @FunctionName  : Get_ADC_Average()
* @Description   : ����ADC�ɼ���ƽ��ֵ
* @Data          : 2016/7/24
* @Explain       :
-------------------------------------------------------------------------------
��ȡͨ��ch��ת��ֵ��ȡtimes��,Ȼ��ƽ��
Channel:ͨ�����
Times:��ȡ����
����ֵ:ͨ��ch��times��ת�����ƽ��ֵ
------------------------------------------------------------------------------*/
u16 ADC_Average_Get(u8 Channel, u8 Times)
{
    u32 Result = 0; 
	while(Times--)
    {
        Result += ADC_Result_Get(Channel,3);
		Result/=2;
        OSdelay_ms(1);
    }
    return Result;
}

 
 

/**----------------------------------------------------------------------------
* @FunctionName  : ADC_Waveform_Get()     	
* @Description   : ������ȡ
* @Data          : 2016/8/17	
* @Explain       : None	
-------------------------------------------------------------------------------
SourceBuff :Դ��������
SourceLenth��Դ���ݳ���
ResultBuff�����������
ResultLenth��������ݳ���
return:0ʧ��   ������ȡ������
------------------------------------------------------------------------------*/
u16 ADC_Waveform_Get(u16 *SourceBuff,u16 SourceLenth,double *ResultBuff,u16 ResultLenth)
{
	double ZoomX = 0.0f,SourceX = 0.0f,SourceDecimX = 0.0f;
	u16 i = 0,StartX = 0,EndX = 0;
	u16 Max = 0,Min = 0xffff,Vpp = 0;   
	ERROR_HANDLE(11);
	/* ȡ������ -------------------------------------*/
	for(i = 0;i< SourceLenth;i++)
	{
		if(SourceBuff[i] > 4096) return 0; //DMA�������  
			 
		if(Max < SourceBuff[i]) Max = SourceBuff[i];
		if(Min > SourceBuff[i]) Min = SourceBuff[i]; 
	}	  
	Vpp = Max - Min;
	ERROR_HANDLE(12);
	i = SourceLenth/100;//ȥ��ǰ��1%�Ĳ��ȶ�����
	for(;i< SourceLenth;i++)
		if(SourceBuff[i] + Min > Vpp - Vpp/10) break;
	for(;i< SourceLenth;i++)
		if(SourceBuff[i] + Min  < Vpp/2) break;
	StartX = i;
	ERROR_HANDLE(13);	
	for(;i< SourceLenth;i++)
		if(SourceBuff[i] + Min  > Vpp - Vpp/10) break;
	for(;i< SourceLenth;i++)
		if(SourceBuff[i] + Min  < Vpp/2) break;
	EndX = i;		
	ERROR_HANDLE(14);	  
	ZoomX = (double)(EndX - StartX)/ResultLenth;
	
	for(i = 0;i < ResultLenth;i ++)
	{ 
		SourceX = (double)StartX+(i*ZoomX);
		SourceDecimX = SourceX - (u16)SourceX;//ȡС��
		 
		if(SourceX < SourceLenth-1)
		{
			ResultBuff[i] = (SourceBuff[(u16)SourceX] + ((double)SourceBuff[(u16)SourceX + 1] - (double)SourceBuff[(u16)SourceX])*SourceDecimX)*3.3f/4096.0f;//������ 
		} 
		
	}ERROR_HANDLE(15);
	OS_String_Show(0,0,(u8*)"���Ŷȣ�",16,1); OS_Decim_Show(0+16*4,0,ZoomX,8,2,16,1); 
	
	OS_String_Show(0,40+16*0,(u8*)"ȡ��������",16,1);	OS_Decim_Show(0+16*5,40+16*0,EndX - StartX,8,0,16,1); 
	OS_String_Show(0,40+16*1,(u8*)"������꣺",16,1);	OS_Decim_Show(0+16*5,40+16*1,StartX,8,0,16,1);
	OS_String_Show(0,40+16*2,(u8*)"�յ����꣺",16,1);	OS_Decim_Show(0+16*5,40+16*2,EndX,8,0,16,1);  
	
	OS_String_Show(0,100+16*0,(u8*)"Vpp��",16,1);		OS_Decim_Show(0+16*3,100+16*0,Vpp*3.3/4096,4,3,16,1);
	OS_String_Show(0,100+16*1,(u8*)"Max��",16,1);		OS_Decim_Show(0+16*3,100+16*1,Max*3.3/4096,4,3,16,1);
	OS_String_Show(0,100+16*2,(u8*)"Min��",16,1);		OS_Decim_Show(0+16*3,100+16*2,Min*3.3/4096,4,3,16,1);//���ֵ ��ѹ���ֵ  ��ѹ��Сֵ 
	ERROR_HANDLE(16);
	return EndX - StartX;
}





/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/








