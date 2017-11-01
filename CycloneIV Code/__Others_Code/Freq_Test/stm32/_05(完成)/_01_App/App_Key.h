/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Key.h
* @Description : None
* @Date        : 2016/7/19
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/
							
/* ��ֹ�ص��� ----------------------------------------------------------------*/
#ifndef __APP_KEY_H
#define __APP_KEY_H 

/* ͷ�ļ����� ----------------------------------------------------------------*/  
#include "OS_StartFile.h"

/* ȫ�ֺ궨�� ----------------------------------------------------------------*/ 
#define KEY_MODE_SHORT		(0x01<<0)	
#define KEY_MODE_LONG		(0x01<<1)	
  
#define KEY_COUNT_SHORT		20
#define KEY_COUNT_LONG		100
#define KEY_COUNT_LIMIT		500


#define GPIO_WK_UP 	PAin(0)	
#define GPIO_KEY1 	PCin(1)	
#define GPIO_KEY2 	PCin(2)	
#define GPIO_KEY3 	PCin(3)	

#define KEY_PRESS 	(GPIO_WK_UP == 0||GPIO_KEY1 == 0||GPIO_KEY2 == 0||GPIO_KEY3 == 0)

#define WK_UP		(0x01<<0)	
#define KEY1		(0x01<<1)													
#define KEY2		(0x01<<2)	
#define KEY3		(0x01<<3)	 
#define KEY_ALL		 0xff


/* �ṹ������ ----------------------------------------------------------------*/ 
typedef struct
{ 
	u16	CountNow[4];//����
	u16	CountLast[4];//��һ�η��ټ���ͣ��
	u8 ResultShort;//�̰�������Ͻ��
	u8 ResultLong;//����������Ͻ��
	
}Type_Key;

/* ȫ�ֱ������� --------------------------------------------------------------*/  
extern Type_Key Key;

/* ȫ�ֺ������� --------------------------------------------------------------*/  				
extern Type_AppList App_Key;
u8 Key_Now_Get(u8 KeyNum,u8 Mode);
u8 Key_Get(u8 KeyNum,u8 Mode);
void Key_Clear(u8 Mode);
 
 
 
 
 
#endif
/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/



