/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/
/**============================================================================
* @FileName    : App_Key.c
* @Description : None
* @Date        : 2016/7/19
* @By          : Wind��л���죩
* @Email       : 1659567673@ qq.com
* @Platform    : Keil uVision5 v5.15 (STM32F407ZG)
* @Explain     : None
*=============================================================================*/

/* ͷ�ļ����� ----------------------------------------------------------------*/
#include "App_Key.h"  
 
/* ˽�к궨�� ----------------------------------------------------------------*/
 
/* ˽�У���̬���������� ------------------------------------------------------*/ 
Type_AppList App_Key_Scan;

/* ȫ�ֱ������� --------------------------------------------------------------*/
Type_Key Key = {0};

/* ȫ�ֱ������� --------------------------------------------------------------*/

/* ȫ�ֺ�����д --------------------------------------------------------------*/
/**----------------------------------------------------------------------------
* @FunctionName  : Key()     
* @Description   : �������� 
* @Data          : 2016/7/19
* @Explain       : ����״̬��ɨ��
------------------------------------------------------------------------------*/
unsigned int Key_Main(void)		
{   
	if(!KEY_PRESS) //û�а�������
	{
		if(Key.CountLast[0] > KEY_MODE_SHORT && Key.CountLast[0] < KEY_COUNT_LONG)  
			Key.ResultShort |= WK_UP;
		
		if(Key.CountLast[1] > KEY_MODE_SHORT && Key.CountLast[1] < KEY_COUNT_LONG)
			Key.ResultShort |= KEY1; 
		
		if(Key.CountLast[2] > KEY_MODE_SHORT && Key.CountLast[2] < KEY_COUNT_LONG)
			Key.ResultShort |= KEY2; 
		
		if(Key.CountLast[3] > KEY_MODE_SHORT && Key.CountLast[3] < KEY_COUNT_LONG)
			Key.ResultShort |= KEY3;  
		 
		if(Key.CountLast[0] > KEY_COUNT_LONG && Key.CountLast[0] < KEY_COUNT_LIMIT)  
			Key.ResultLong |= WK_UP;
		
		if(Key.CountLast[1] > KEY_COUNT_LONG && Key.CountLast[1] < KEY_COUNT_LIMIT)
			Key.ResultLong |= KEY1; 
		
		if(Key.CountLast[2] > KEY_COUNT_LONG && Key.CountLast[2] < KEY_COUNT_LIMIT)
			Key.ResultLong |= KEY2; 
		
		if(Key.CountLast[3] > KEY_COUNT_LONG && Key.CountLast[3] < KEY_COUNT_LIMIT)
			Key.ResultLong |= KEY3;  
		 
		Key.CountLast[0] = 0;
		Key.CountLast[1] = 0;
		Key.CountLast[2] = 0;
		Key.CountLast[3] = 0; 
	}		
	else {Key.ResultShort = 0; Key.ResultLong = 0;}
	
	return 0;																	
}	 						

unsigned int Key_Start(void)		
{			
	static u8 first = 0;
	if(first == 0)
	{
		first = 1;	
		GPIO_Key_Init();
		OSTask_Creat(&App_Key_Scan);  	  	
	}
	return 0;
}
Type_AppList App_Key = {Key_Main,NULL,Key_Start,NULL, \
						OS_STATE_ACTIVE,OS_THREAD_PRIMARY, \
						(u8*)"Key",100};

						
/**----------------------------------------------------------------------------
* @FunctionName  : KeyScan()     
* @Description   : None 
* @Data          : 2016/7/19
* @Explain       : None
------------------------------------------------------------------------------*/
unsigned int Key_Scan_Main(void)		
{      
	if(GPIO_WK_UP == 0)	{ Key.CountNow[0]++;Key.CountLast[0]++;}
	else Key.CountNow[0]= 0;
	
	if(GPIO_KEY1 == 0)	{ Key.CountNow[1]++;Key.CountLast[1]++;}
	else Key.CountNow[1]= 0;
	
	if(GPIO_KEY2 == 0)	{ Key.CountNow[2]++;Key.CountLast[2]++;}
	else Key.CountNow[2]= 0;
	
	if(GPIO_KEY3 == 0)  { Key.CountNow[3]++;Key.CountLast[3]++;}
	else Key.CountNow[3]= 0; 
	
	return 0;																	
}	 
Type_AppList App_Key_Scan = {Key_Scan_Main,NULL,NULL,NULL, \
							OS_STATE_ACTIVE,OS_THREAD_SYSTEM, \
							(u8*)"Key_Scan",10};			
 
						
/**----------------------------------------------------------------------------
* @FunctionName  : Key_Now_Get()     
* @Description   : ������״��ȡ���� 
* @Data          : 2016/7/19
* @Explain       
-------------------------------------------------------------------------------		
 @param  	KeyNum: WK_UP|KEY1|KEY2|KEY3	
			Mode: KEY_MODE_SHORT|KEY_MODE_LONG						
 @return 	0����Ч��,1����Ч��							
------------------------------------------------------------------------------*/ 
u8 Key_Now_Get(u8 KeyNum,u8 Mode)
{
	u8 Result = 0;  
	if(Mode & KEY_MODE_SHORT)
	{
		if(KeyNum&WK_UP)
		{
			if(Key.CountNow[0] > KEY_MODE_SHORT)
				Result |= WK_UP;
		}
		if(KeyNum&KEY1)
		{
			if(Key.CountNow[1] > KEY_MODE_SHORT)
				Result |= KEY1;
		}
		if(KeyNum&KEY2)
		{
			if(Key.CountNow[2] > KEY_MODE_SHORT)
				Result |= KEY2;
		}
		if(KeyNum&KEY3)
		{
			if(Key.CountNow[3] > KEY_MODE_SHORT)
				Result |= KEY3;
		}
	}
	else if(Mode & KEY_MODE_LONG)
	{
		if(KeyNum&WK_UP)
		{
			if(Key.CountNow[0] > KEY_COUNT_LONG)
				Result |= WK_UP;
		}
		if(KeyNum&KEY1)
		{
			if(Key.CountNow[1] > KEY_COUNT_LONG)
				Result |= KEY1;
		}
		if(KeyNum&KEY2)
		{
			if(Key.CountNow[2] > KEY_COUNT_LONG)
				Result |= KEY2;
		}
		if(KeyNum&KEY3)
		{
			if(Key.CountNow[3] > KEY_COUNT_LONG)
				Result |= KEY3;
		}
		
	}
		
	if(Result == KeyNum) return 1;
	else return 0;  
}

/**----------------------------------------------------------------------------
* @FunctionName  : Key_Get()     
* @Description   : ������ȡ���� 
* @Data          : 2016/7/19
* @Explain       ������ | ���Ӹ�����
 -------------------------------------------------------------------------------		
 @param  	KeyNum: WK_UP|KEY1|KEY2|KEY3	
			Mode: KEY_MODE_SHORT|KEY_MODE_LONG
 @return 	0����Ч��,1����Ч��							
------------------------------------------------------------------------------*/ 
u8 Key_Get(u8 KeyNum,u8 Mode)
{ 
	if(Mode & KEY_MODE_SHORT)
	{ 
		if(Key.ResultShort == KeyNum) return 1;
		else return 0; 
	}
	if(Mode & KEY_MODE_LONG)
	{ 
		if(Key.ResultLong == KeyNum) return 1;
		else return 0; 
	}
	return 0;	
}
 

/**----------------------------------------------------------------------------
* @FunctionName  : Key_Clear()     
* @Description   : ����������� 
* @Data          : 2016/7/19
* @Explain       ������ | ���Ӹ�����  
-------------------------------------------------------------------------------		
 ��Key_Get()����ʹ��
 @param Mode: KEY_MODE_SHORT|KEY_MODE_LONG
------------------------------------------------------------------------------*/
void Key_Clear(u8 Mode)
{ 
	if(Mode & KEY_MODE_SHORT) Key.ResultShort = 0;
	if(Mode & KEY_MODE_LONG)  Key.ResultLong = 0;
}


/*******************************(C) COPYRIGHT 2016 Wind��л���죩*********************************/


















