/**********************************************************************************************
 *   �� �� ����PS2.c
 *
 *   ����ƽ̨��������STM32������
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2015.7.16
 **********************************************************************************************/

/* ���� --------------------------------------------------------------------------------------*/
#include "PS2.h" 
/* ˽�к� ------------------------------------------------------------------------------------*/
#define PS2_SCL 	GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)
#define PS2_SDA   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11)

#define PS2_Count   10000
/* ˽�б��� ----------------------------------------------------------------------------------*/
__IO uint32_t Count = PS2_Count;
/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* ˽�к������� ------------------------------------------------------------------------------*/
static void PS2_SCL_Set(uint8_t Mode);
static uint8_t PS2_SCL_Wait(uint8_t Mode);
static void PS2_GPIO_Init(void);
//static void TIM4_Configuration(void);
/* ˽�к���ģ�� ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *��    �ƣ�void PS2_Keyboard_Init(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ����PS2���̳�ʼ��
 *********************************************************************************************/
void PS2_Keyboard_Init(void)
{
	PS2_GPIO_Init(); 
//	TIM4_Configuration();
}
/**********************************************************************************************
 *��    �ƣ�void PS2_GPIO_Init(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ����PS2 IO�ڳ�ʼ��
 *********************************************************************************************/
static void PS2_GPIO_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11| GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}
/**********************************************************************************************
 *��    �ƣ�static void PS2_SCL_Set(uint8_t Mode)
 *
 *��    ����uint8_t Mode    1�����   0������
 *
 *�� �� ֵ����
 *
 *��    ����SCL IO�˿�״̬����
 *********************************************************************************************/
static void PS2_SCL_Set(uint8_t Mode)
{
	GPIO_InitTypeDef  GPIO_InitStructure;	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	if(Mode)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	}
	else
	{
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	}
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	if(Mode)
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
}
/**********************************************************************************************
 *��    �ƣ�void PS2_ReadKeyCodon(volatile uint8_t* Key_Num)
 *
 *��    ����volatile uint8_t* Key_Num  ������ջ�����ָ��
 *
 *�� �� ֵ��void
 *
 *��    ����PS2 �����ȡ����
 *********************************************************************************************/
void PS2_ReadKeyCodon(volatile uint8_t* Key_Num)
{
	uint8_t i;
	PS2_SCL_Set(0);
	if(!PS2_SCL_Wait(0))
	{
		*Key_Num = 0;
		return;
	}
	if(!PS2_SCL_Wait(1))
	{
		*Key_Num = 0;
		return;
	}
	if(!PS2_SCL_Wait(0))
	{
		*Key_Num = 0;
		return;
	}
	for(i = 0;i < 8;i++)
	{
		*Key_Num >>= 1;
		if(PS2_SDA)
			*Key_Num |= 0x80;
		if(!PS2_SCL_Wait(1))
		{
			*Key_Num = 0;
			return;
		}
		if(!PS2_SCL_Wait(0))
		{
			*Key_Num = 0;
			return;
		}
	}
	if(!PS2_SCL_Wait(1))
	{
		*Key_Num = 0;
		return;
	}
	if(!PS2_SCL_Wait(0))
	{
		*Key_Num = 0;
		return;
	}
	if(!PS2_SCL_Wait(1))
	{
		*Key_Num = 0;
		return;
	}
	PS2_SCL_Set(1);
}

/**********************************************************************************************
 *��    �ƣ�static uint8_t PS2_SCL_Wait(uint8_t Mode)
 *
 *��    ����uint8_t Mode  1�ȴ�������   0�ȴ��½���
 *
 *�� �� ֵ��1�ȴ��ɹ�  0�ȴ���ʱ
 *
 *��    ����PS2 SCL�ȴ�����
 *********************************************************************************************/
static uint8_t PS2_SCL_Wait(uint8_t Mode)
{
	if(Mode)
	{
		while((!PS2_SCL) && Count)
		Count--;
		if(!Count)
		{
			Count = PS2_Count;
			PS2_SCL_Set(1);
			return 0;
		}
		else
			return 1;
	}
	else
	{
		while(PS2_SCL && Count)
		Count--;
		if(!Count)
		{
			Count = PS2_Count;
			PS2_SCL_Set(1);
			return 0;
		}
		else
			return 1;
	}
}

/**********************************************************************************************
 *��    �ƣ�void TIM4_Configuration(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ����TIM4����
 *********************************************************************************************/
//static void TIM4_Configuration(void)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  ///ʹ��TIM4ʱ��
//	
//     TIM_TimeBaseInitStructure.TIM_Period = 1000-1; 	//�Զ���װ��ֵ
//	TIM_TimeBaseInitStructure.TIM_Prescaler=840-1;  //��ʱ����Ƶ
//	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
//	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
//	
//	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);//��ʼ��TIM4
//	
//	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //����ʱ��4�����ж�
//	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��4
//	
//	NVIC_InitStructure.NVIC_IRQChannel= TIM4_IRQn; //��ʱ��4�ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3; //��ռ���ȼ�3��
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority= 1; //�����ȼ�1��
//	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//}
/**********************************************************************************************
 *��    �ƣ�void TIM4_IRQHandler(void)
 *
 *��    ������
 *
 *�� �� ֵ����
 *
 *��    ����TIM4�жϷ�����
 *********************************************************************************************/
//void TIM4_IRQHandler(void)
//{
//	if(TIM_GetITStatus(TIM4,TIM_IT_Update)==SET) //����ж�
//	{
//		
//		Key_StateSweep(&Key_FSM_PS2);  
//	}
//	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);  //����жϱ�־λ
//}
/* �ļ����� ---------------------------------------------------------------------------------*/
/**********************************************************************************************
 *   �� �� ����Key_State.c
 *
 *   ����ƽ̨��������STM32������
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2015.7.17
 **********************************************************************************************/

/* ���� --------------------------------------------------------------------------------------*/
/* ˽�к� ------------------------------------------------------------------------------------*/
#define OPEN_CODE         0xf0   //����
#define LONG_KEY_COUNT    3      //����������
/* ˽�б��� ----------------------------------------------------------------------------------*/

/* ˽�нṹ�� --------------------------------------------------------------------------------*/
__KEY_StateMachine  Key_FSM_PS2;
/* ˽�к������� ------------------------------------------------------------------------------*/

/* ˽�к���ģ�� ------------------------------------------------------------------------------*/

/**********************************************************************************************
 *��    �ƣ�void Key_StateSweep(__KEY_StateMachine *Key_FSM)
 *
 *��    ����__KEY_StateMachine *Key_FSM  ״̬���ṹ��ָ��
 *
 *�� �� ֵ��void
 *
 *��    ����״̬��ɨ�躯��
 *********************************************************************************************/
void Key_StateSweep(__KEY_StateMachine *Key_FSM)
{
	PS2_ReadKeyCodon(&Key_FSM ->Key_Code_Pre);
	if(Key_FSM ->Key_Code_Pre == 0)
	{
		Key_FSM ->Key_Filt++;
		if(Key_FSM ->Key_Filt > 50)
		{
			Key_FSM ->Key_Filt = 0;
			Key_FSM ->State_Flag = 0;
		}
		return;
	}
	else
		Key_FSM ->Key_Filt = 0;
	switch(Key_FSM ->State_Flag)
	{
		case 0:
			if((Key_FSM ->Key_Code_Pre != 0) && (Key_FSM ->Key_Code_Pre != OPEN_CODE))
			{
				Key_FSM ->Key_Code_Bef = Key_FSM ->Key_Code_Pre;
				Key_FSM ->State_Flag = 1;
				Key_FSM ->Key_Mode = 1;
			}
			else
			{
				Key_FSM ->Key_Code_Bef = 0;
				Key_FSM ->Key_Mode = 0;
				Key_FSM ->State_Flag = 0;
			}
			break;
			
		case 1:
			if(Key_FSM ->Key_Code_Bef == Key_FSM ->Key_Code_Pre)
			{
				Key_FSM ->State_Flag = 1;   //ͣ���ڵڶ�������
				Key_FSM ->Key_Count++;
				if(Key_FSM ->Key_Count == LONG_KEY_COUNT)
				{
					Key_FSM ->State_Flag = 2;
					Key_FSM ->Key_Count = 0;
					Key_FSM ->Key_Mode = 2;  //����������
				}
			}
			else if(Key_FSM ->Key_Code_Pre == OPEN_CODE)
			{
				Key_FSM ->Key_Code_Bef = Key_FSM ->Key_Code_Pre;
				Key_FSM ->State_Flag = 1;
			}
			else
			{
				Key_FSM ->Key_Count = 0;
				Key_FSM ->State_Flag = 0;
				Key_FSM ->Key_Code_Bef = 0;
			}
			break;
			
		case 2:
			if(Key_FSM ->Key_Code_Bef == Key_FSM ->Key_Code_Pre)
			{
					Key_FSM ->Key_Mode = 3;   //������������
			}
			else if(Key_FSM ->Key_Code_Pre == OPEN_CODE)
			{
				Key_FSM ->Key_Code_Bef = Key_FSM ->Key_Code_Pre;
				Key_FSM ->State_Flag = 2;
			}
			else
			{
				Key_FSM ->Key_Mode = 0;
				Key_FSM ->State_Flag = 0;
			}
			break;
	}
}


/* �ļ����� ---------------------------------------------------------------------------------*/






