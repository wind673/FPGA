/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : Drive_Usart.c
* @Description : None
* @Date        : 2016/11/11
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "Drive_Usart.h"
#include "sys.h"
#include "stdio.h"  

/* ˽�к궨�� ----------------------------------------------------------------*/ 
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	 
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	  
	USART2->DR = (u8) ch;
	while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
	 
	return ch;
} 

/* ˽�У���̬���������� ------------------------------------------------------*/

/* ȫ�ֱ������� --------------------------------------------------------------*/ 

/* ȫ�ֺ�����д --------------------------------------------------------------*/ 
/**----------------------------------------------------------------------------
* @FunctionName  : USART3_Init()
* @Description   : U1
* @Data          : 2016/11/11
* @Explain       : None
------------------------------------------------------------------------------*/
void Usart3_Init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE); //ʹ��USART3ʱ��
	
    //����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_USART3); //GPIOA9����ΪUSART3
    GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_USART3); //GPIOA10����ΪUSART3
	
    //USART�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11; //_GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOC, &GPIO_InitStructure); //��ʼ�� _GPIO

    //USART��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART3, &USART_InitStructure); //��ʼ������1 
    USART_Cmd(USART3, ENABLE);  //ʹ�ܴ���1 
    USART_ClearFlag(USART3, USART_FLAG_TC); 
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//��������ж�

    //UsartNVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;//����1�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}


/**----------------------------------------------------------------------------
* @FunctionName  : Usart6_Init()
* @Description   : U4(����)
* @Data          : 2016/11/11
* @Explain       : None
------------------------------------------------------------------------------*/
void Usart6_Init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE); //ʹ��GPIOAʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE); //ʹ��USART3ʱ��
	
    //����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource9, GPIO_AF_USART6); //GPIOA9����ΪUSART3
    GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6); //GPIOA10����ΪUSART3
	
    //USART�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_14; //_GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOG, &GPIO_InitStructure); //��ʼ�� _GPIO

    //USART��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART6, &USART_InitStructure); //��ʼ������1 
    USART_Cmd(USART6, ENABLE);  //ʹ�ܴ���1 
    USART_ClearFlag(USART6, USART_FLAG_TC); 
    USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);//��������ж�

    //UsartNVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;//����1�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}




/**----------------------------------------------------------------------------
* @FunctionName  : Usart2_Init()
* @Description   : U3
* @Data          : 2016/11/11
* @Explain       : None
------------------------------------------------------------------------------*/
void Usart2_Init(u32 bound)
{
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure; 
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //ʹ��USART3ʱ��
	
    //����1��Ӧ���Ÿ���ӳ��
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2); //GPIOA9����ΪUSART3
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2); //GPIOA10����ΪUSART3
	
    //USART�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3; //_GPIO
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ�� _GPIO

    //USART��ʼ������
    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART2, &USART_InitStructure); //��ʼ������1 
    USART_Cmd(USART2, ENABLE);  //ʹ�ܴ���1 
    USART_ClearFlag(USART2, USART_FLAG_TC); 
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//��������ж�

    //UsartNVIC ����
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//����1�ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�2
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
    NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ�����
	
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/








