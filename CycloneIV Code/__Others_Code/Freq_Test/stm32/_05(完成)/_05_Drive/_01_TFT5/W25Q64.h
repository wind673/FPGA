/***************************************************************************************************
  * �� �� ����W25Q64.c
  * ��    �ߣ��µܱ�
  *	��    �ڣ�2015.7.4
  * ��    ����Stm32F407ZG
  * �� �� �壺stm32f407ZG--2015������
  * �޸�ʱ�䣺�� 
  * �� �� ��: keil.5
  * �� �� ����V1.4
  *************************************************************************************************/ 
/* -------��ֹ�ݹ�����Ķ���-----------------------------------------------------------------------*/
#ifndef __W25Q64_H
#define __W25Q64_H	
/*--------����ͷ�ļ�------------------------------------------------------------------------------*/
#include "delay.h"
/*----------------оƬ�б�궨��-------------------------------------------------------------------*/	
#define W25Q80 	0XEF13 	
#define W25Q16 	0XEF14
#define W25Q32 	0XEF15
#define W25Q64 	0XEF16
#define W25Q128	0XEF17

//extern uint16_t W25QXX_TYPE; //����оƬ�ͺ�
/*----------------Ƭѡ�ź�------------------------------------------------------------------*/	
#define	W25Q64_CS_H 	GPIO_SetBits(GPIOB,GPIO_Pin_9); 



#define	W25Q64_CS_L 	GPIO_ResetBits(GPIOB,GPIO_Pin_9);  
						
						
/*----------------ָ���------------------------------------------------------------------*/	
#define W25X_WriteEnable		0x06 
#define W25X_WriteDisable		0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData		    0x03 
#define W25X_FastReadData		0x0B 
#define W25X_FastReadDual		0x3B 
#define W25X_PageProgram		0x02 
#define W25X_BlockErase			0xD8 
#define W25X_SectorErase		0x20 
#define W25X_ChipErase			0xC7 
#define W25X_PowerDown			0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID			0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 
/*---------------------���ں���ģ��---------------------------------------------------------------*/  
void W25Q64_Init(void);
uint16_t  W25Q64_ReadID(void);  	    		//��ȡFLASH ID
uint8_t	 W25Q64_ReadSR(void);        		//��ȡ״̬�Ĵ��� 
void W25Q64_Write_SR(uint8_t sr);  			//д״̬�Ĵ���
void W25Q64_Write_Enable(void);  		//дʹ�� 
void W25Q64_Write_Disable(void);		//д����
void W25Q64_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);
void W25Q64_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //��ȡflash
void W25Q64_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//д��flash
void W25Q64_Erase_Chip(void);    	  	//��Ƭ����
void W25Q64_Erase_Sector(uint32_t Dst_Addr);	//��������
void W25Q64_Wait_Busy(void);           	//�ȴ�����
void W25Q64_PowerDown(void);        	//�������ģʽ
void W25Q64_WAKEUP(void);				//����
#endif
















