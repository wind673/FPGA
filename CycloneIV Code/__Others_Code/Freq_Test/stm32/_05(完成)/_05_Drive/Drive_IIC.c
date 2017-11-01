/*******************************(C) COPYRIGHT 2016 DreamFox���ŵ��ǣ�*********************************/
/**============================================================================
* @FileName    : Drive_IIC.c
* @Description : None
* @Date        : 2016/7/24
* @By          : DreamFox���ŵ��ǣ�
* @Email       : 446127056@ qq.com
* @Platform    : Keil uVision5 v5.20 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_IIC.h"

/* ˽�к궨�� ----------------------------------------------------------------*/
//IO��������
#define SDA_IN()  {GPIOF->MODER&=~(3<<(2*2));GPIOF->MODER|=0<<2*2;}	//PF2����ģʽ
#define SDA_OUT() {GPIOF->MODER&=~(3<<(2*2));GPIOF->MODER|=1<<2*2;} //PF2���ģʽ
//IO��������	 
#define IIC_SCL    GPIOF_OUT(1) //SCL	
#define IIC_SDA    GPIOF_OUT(2) //SDA	 
#define READ_SDA   GPIOF_IN(2)	//����SDA 	

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/
 
/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Init()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : IIC��ʼ��
------------------------------------------------------------------------------*/  
//��ʼ��IIC
void IIC_Init(void)
{			
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOBʱ��

  //GPIOB8,B9��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��
  IIC_SCL=1;
  IIC_SDA=1;
}

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Start()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : IIC�źŲ���
------------------------------------------------------------------------------*/  
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	Delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Stop()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : ����IICֹͣ�ź�
------------------------------------------------------------------------------*/  

void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	Delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	Delay_us(4);							   	
}

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Wait_Ack()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : �ȴ�Ӧ���źŵ���
------------------------------------------------------------------------------*/  
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
	IIC_SDA=1;Delay_us(1);	   
	IIC_SCL=1;Delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Ack()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : ����ACKӦ��
------------------------------------------------------------------------------*/  
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	Delay_us(2);
	IIC_SCL=1;
	Delay_us(2);
	IIC_SCL=0;
}

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_NAck()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : ������ACKӦ��
------------------------------------------------------------------------------*/     
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	Delay_us(2);
	IIC_SCL=1;
	Delay_us(2);
	IIC_SCL=0;
}					 			

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Send_Byte()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : IIC����һ���ֽ�
------------------------------------------------------------------------------*/  
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	  SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
    IIC_SDA=(txd&0x80)>>7;
    txd<<=1; 	  
		Delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		Delay_us(2); 
		IIC_SCL=0;	
		Delay_us(2);
    }	 
} 	    

/**----------------------------------------------------------------------------
* @FunctionName  : IIC_Read_Byte()     
* @Description   : None 
* @Data          : 2016/7/24
* @Explain       : ��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK  
------------------------------------------------------------------------------*/  
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        Delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		Delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}
	
	
	
	





/*******************************(C) COPYRIGHT 2016 DreamFox���ŵ��ǣ�*********************************/








