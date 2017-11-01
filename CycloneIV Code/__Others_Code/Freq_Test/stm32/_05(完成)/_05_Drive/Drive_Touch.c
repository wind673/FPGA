/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Touch.c
* @Description : None
* @Date        : 2016/7/13
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Touch.h"						
#include "OS_StartFile.h"						

/* ˽�к궨�� ----------------------------------------------------------------*/
#if MACHINE == RECEIVE		 
#define	SCREEN_TOUCH	1//0�Ǵ��������м��������Ļ��1���ұ�
#else
#define SCREEN_TOUCH	0
#endif

/* ˽�У���̬���������� ------------------------------------------------------*/
//static void EXTILine13_Config(void);
static void	GPIO_Configuration(void);
static uint16_t ADS_Read_XY(uint8_t xy);
static void Delay(__IO uint32_t nCount);


/* ȫ�ֱ������� --------------------------------------------------------------*/
#define T_PEN  	GPIOD_IN(6)    //PG0  INT
#define T_MISO 	GPIOB_IN(14)   //PG5  MISO
#define T_MOSI 	GPIOB_OUT(15)  //PG2  MOSI
#define T_SCK  	GPIOB_OUT(13)  //PG1  SCLK
#define T_CS  	GPIOC_OUT(13)  //PG3 CS 

#define READ_TIMES 15 //��������
#define LOST_VAL 5	 //����ֵ 
#define CMD_RDX 0XD0
#define CMD_RDY 0X90   
#define Touch_Delay() Delay(1)


/* ȫ�ֺ�����д --------------------------------------------------------------*/
static void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {	
  }	
}

 
static void	GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC, ENABLE);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15|GPIO_Pin_13;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
//	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  /* ����PA.6λ�������� */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	/* ����PD.13λ�������� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	T_SCK=1; 
	T_CS=1;
	T_MOSI=1;

 
	 
	
}


static void ADS_Write_Byte(uint8_t data)    
{  
	uint8_t count=0;   
	for(count=0;count<8;count++)  
	{ 	  
		if(data&0x80)T_MOSI=1;  
		else T_MOSI=0;   
		data<<=1;  
		Touch_Delay();			
		T_SCK=0;//��������Ч	   
		Touch_Delay();		
		T_SCK=1; 
		Touch_Delay();			
	} 			    
}

static uint16_t ADS_Read_AD(uint8_t CMD)	  
{ 	 
	uint8_t count=0; 	  
	u16 Num=0; 
	T_SCK=0;//������ʱ�� 	 
	T_CS=0; //ѡ��ADS7843	 		
	ADS_Write_Byte(CMD);//����������
	OSdelay_us(6);//ADS7846��ת��ʱ���Ϊ6us
	T_SCK=1;//��1��ʱ�ӣ����BUSY   
	Touch_Delay();	
	T_SCK=0; 	
	Touch_Delay();	
	for(count=0;count<16;count++)  
	{ 				  
		Num<<=1; 	 
		T_SCK=0;//�½�����Ч  
		Touch_Delay();		
		T_SCK=1;
		Touch_Delay();
		if(T_MISO)Num++; 	
		Touch_Delay();		
	}  	
	Num>>=4;   //ֻ�и�12λ��Ч.
	T_CS=1;//�ͷ�ADS7843	 
	Touch_Delay();
	return(Num);   
} 

static uint16_t ADS_Read_XY(uint8_t xy)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum=0;
	uint16_t temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(xy);	    
	}				    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	return temp;   
} 

#if SCREEN_TOUCH == 1
/**----------------------------------------------------------------------------
* @FunctionName  : TouchRead()     
* @Description   : None 
* @Data          : 2016/7/19
* @Explain       : ���������ұߵ�������Ļ
------------------------------------------------------------------------------*/
void TouchRead(u16 *x,u16 *y)
{ 
	u16 tempX,tempY;
	tempX = 800 - ADS_Read_XY(CMD_RDX)*800/2048; 
  	tempY = 480 - ADS_Read_XY(CMD_RDY)*480/2048;
	
	if(tempX > 400) tempX += (tempX - 400)/20;
	else tempX -= (400 - tempX)/10;				
	
	if(tempY > 240) tempY += (tempY - 240)/10;
	else tempY -= (240 - tempY)/5;
	 
	if(tempX > 800 || tempX == 0) *x = 0xffff;
	else *x = tempX;
		
	if(tempY > 480 || tempY == 0) *y = 0xffff;
	else *y = tempY;  
}
#else
/**----------------------------------------------------------------------------
* @FunctionName  : TouchRead()     
* @Description   : None 
* @Data          : 2016/7/19
* @Explain       : ���������м��������Ļ
------------------------------------------------------------------------------*/
void TouchRead(u16 *x,u16 *y)
{ 
	u16 tempX,tempY;
	tempX = ADS_Read_XY(CMD_RDX)*800/2048; 
  	tempY = 480 - ADS_Read_XY(CMD_RDY)*480/2048;
	
	if(tempX > 400) tempX += (tempX - 400)/20;
	else tempX -= (400 - tempX)/20;
	
	if(tempY > 240) tempY += (tempY - 240)/20;
	else tempY -= (240 - tempY)/20;
	 
	if(tempX > 800 || tempX == 0) *x = 0xffff;
	else *x = tempX;
		
	if(tempY > 480 || tempY == 0) *y = 0xffff;
	else *y = tempY; 
}
#endif

/**----------------------------------------------------------------------------
* @FunctionName  : Touch_Init()     
* @Description   : None 
* @Data          : 2016/7/13
* @Explain       : None
------------------------------------------------------------------------------*/ 
void Touch_Init(void)
{ 
   GPIO_Configuration();   

}

/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/





