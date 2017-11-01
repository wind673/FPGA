/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_AD9851.c
* @Description : None
* @Date        : 2016/7/20
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     :  
-------------------------------------------------------------------------------
Ƶ�ʻ���ΪƵ����ϵ��
�ɼ��㹫ʽ��Fout=(Freq*AD9851_SystemCloc)/2^32 Freq ΪƵ�ʿ�����
�� Freq=FC*Fout
FC=2^32/AD9851_SystemCloc
��AD9851_SystemCloc=30MHz
ʱ FC=143.16557653333333333333333333333f 
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_AD9851.h"							

/* ˽�к궨�� ----------------------------------------------------------------*/ 
#define M20				 				214.7483648f
#define M30							 	143.16557653333333333333333333333f 
#define M50 							85.89934592f
#define M120							35.791394133333333333333333333333f 

#define MULT 							0  //6��Ƶ  	0�رգ�1��
#define POWER_MODE 						0 //����ģʽ 0��Power-up_ mode 1:Power-down_ 
#define FC 								M20//���㹫ʽ���ļ�˵����

#define BASE_FREQ 						34700000//34.7M��Ƶ
#define BASE_FREQ_SHIFT_LIMIT 			5000//5000ƫ�Ʒ�Χ

/* ˽�У���̬���������� ------------------------------------------------------*/ 
static void AD9851_Write(uint8_t*Control_Word);

/* ȫ�ֱ������� --------------------------------------------------------------*/ 
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/ 

/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_Init()     
* @Description   : AD9851��ʼ������ 
* @Data          : 2016/7/20
* @Explain        
-------------------------------------------------------------------------------
* None
------------------------------------------------------------------------------*/
void AD9851_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3
								  |GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOG, &GPIO_InitStructure); 
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_12|GPIO_Pin_10|GPIO_Pin_11 ;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	//AD9851 ��ʼ��	
	AD9851_WCLK=0;
	AD9851_FQUD=0;
	AD9851_RESET=1; 	// �ߵ�ƽ��λ
	OSdelay_ms(100);		
	AD9851_RESET=0;
	OSdelay_ms(100);		 
}
 
  
/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_Set()     
* @Description   : ����AD9851�����Ƶ�ʺ���λ
* @Data          : 2016/7/20
* @Explain        
-------------------------------------------------------------------------------
F:Ƶ�� �ֱ���Ϊ0.04Hz,���Ƶ��Fmax=AD9851_SystemCloc/2.5
Phase:��λ 1����λ��ʾPi/16 ��11.25��
------------------------------------------------------------------------------*/
void AD9851_Set(double F,uint8_t Phase)
{	
	uint32_t Freq;									 
	uint8_t CW[5];
	if(MULT)Freq=FC*F/6;
	else Freq=FC*F;
	
	CW[4] = Freq & 0xff;	    // Ƶ�ʿ���������ֽ�LSB
	CW[3] = (Freq>>8) & 0xff;
	CW[2] = (Freq>>16) & 0xff;
	CW[1] = (Freq>>24) & 0xff;  // Ƶ�ʿ���������ֽ�MSB
	CW[0] = (Phase<<3)|(POWER_MODE<<2)|MULT; 
	AD9851_Write(CW);
}
 
 
/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_FM()     
* @Description   : ����FM
* @Data          : 2016/7/24
* @Explain        
-------------------------------------------------------------------------------
Vol:��ֵ 0~3.3V
------------------------------------------------------------------------------*/
void AD9851_FM(double Vol)
{	
	u32 TempVol = Vol*10000/3.3f;//ת����Hz
	if(TempVol > BASE_FREQ_SHIFT_LIMIT*2) TempVol = BASE_FREQ_SHIFT_LIMIT*2; 
	AD9851_Set((BASE_FREQ - BASE_FREQ_SHIFT_LIMIT)+TempVol,0);
}
  

/**----------------------------------------------------------------------------
* @FunctionName  : AD9851_Set()     
* @Description   : дAD9851�����֣�����ģʽ
* @Data          : 2016/7/20
* @Explain        
-------------------------------------------------------------------------------
Control_Word:������ָ��
------------------------------------------------------------------------------*/  
static void AD9851_Write(uint8_t*Control_Word)
{
	AD9851_FQUD=0;			   // FQ_UD�õ�
	AD9851_WCLK=0;			   // w_clk�õ�
	/*---���д��������---*/
		AD9851_Data = Control_Word[0];
		AD9851_WCLK = 1;		
		AD9851_WCLK = 0;	 
		AD9851_Data = Control_Word[1];
		AD9851_WCLK = 1;		
		AD9851_WCLK = 0;
		AD9851_Data = Control_Word[2];
		AD9851_WCLK = 1;	
		AD9851_WCLK = 0;	
		AD9851_Data = Control_Word[3];
		AD9851_WCLK = 1;	
		AD9851_WCLK = 0;
		AD9851_Data = Control_Word[4];
		AD9851_WCLK = 1;	
		AD9851_WCLK = 0;		
		AD9851_FQUD = 1;  //�����ظ���Ƶ��
		AD9851_FQUD = 0;
} 
 
 

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





