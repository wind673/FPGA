 
/*--------����ͷ�ļ�------------------------------------------------------------------------------*/
#include "W25Q64.h" 
#include "spi.h"  
#include "TFT_LCD.h"
#include "stm32f4xx_spi.h" 

/*--------��������-----------------------------------------------------------------------------*/
uint16_t W25Q64_TYPE=W25Q64;	


/************************************************************************************************
 * ����   : ��ʼ��SPI Flash��IO��
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/
void W25Q64_Init(void)
{ 
  GPIO_InitTypeDef  GPIO_InitStructure;
 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//ʹ��GPIOBʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��GPIOGʱ��

	  //GPIOB14
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;//PB14
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//PG7
	GPIO_Init(GPIOG, &GPIO_InitStructure);//��ʼ��
 
	GPIO_SetBits(GPIOG,GPIO_Pin_7);//PG7���1,��ֹNRF����SPI FLASH��ͨ�� 
	W25Q64_CS_H;			//SPI FLASH��ѡ��
	SPI1_Init();		   			//��ʼ��SPI
	SPI1_SetSpeed(SPI_BaudRatePrescaler_2);		//����Ϊ42Mʱ��,����ģʽ 
	W25Q64_TYPE=W25Q64_ReadID();	//��ȡFLASH ID.
}  

/************************************************************************************************
 * ����   : ��ȡW25Q64״̬
 * ����   : 
 * ����   : ��
 * ˵��   :
 *************************************************************************************************/
uint8_t W25Q64_ReadSR(void)   
{  
	uint8_t byte=0;   
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_ReadStatusReg);    //���Ͷ�ȡ״̬�Ĵ�������    
	byte=SPI1_ReadWriteByte(0Xff);             //��ȡһ���ֽ�  
	W25Q64_CS_H;                            //ȡ��Ƭѡ     
	return byte;   
}
/************************************************************************************************
 * ����   : дW25QXX״̬�Ĵ���
 * ����   : ��
 * ����   : ��
 * ˵��   :ֻ��SPR,TB,BP2,BP1,BP0(bit 7,5,4,3,2)����д!!!
 *************************************************************************************************/
void W25Q64_Write_SR(u8 sr)   
{   
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_WriteStatusReg);   //����дȡ״̬�Ĵ�������    
	SPI1_ReadWriteByte(sr);               //д��һ���ֽ�  
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
}   
/************************************************************************************************
 * ����   : W25Q64дʹ��
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/  
void W25Q64_Write_Enable(void)   
{
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_WriteEnable);      //����дʹ��  
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
} 
/************************************************************************************************
 * ����   : W25Q64д��ֹ
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/  
void W25Q64_Write_Disable(void)   
{  
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_WriteDisable);  //����д��ָֹ��    
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
} 		
/************************************************************************************************
 * ����   : ��ȡоƬID
 * ����   : ��
 * ����   : оƬID��Ӧֵ
 * ˵��   : ��
 *************************************************************************************************/   
u16 W25Q64_ReadID(void)
{
	uint16_t Temp = 0;	  
	W25Q64_CS_L;				    
	SPI1_ReadWriteByte(0x90);//���Ͷ�ȡID����	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	    
	SPI1_ReadWriteByte(0x00); 	 			   
	Temp|=SPI1_ReadWriteByte(0xFF)<<8;  
	Temp|=SPI1_ReadWriteByte(0xFF);	 
	W25Q64_CS_H;				    
	return Temp;
}  
/************************************************************************************************
 * ����   : ��ȡSPI Flash
 * ����   : ���ݴ洢�� ��ʼ��ȡ��ַ Ҫ��ȡ������ֽ���
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/  
void W25Q64_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead)   
{ 
 	u16 i;   										    
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_ReadData);         //���Ͷ�ȡ����   
	SPI1_ReadWriteByte((u8)((ReadAddr)>>16));  //����24bit��ַ    
	SPI1_ReadWriteByte((u8)((ReadAddr)>>8));   
	SPI1_ReadWriteByte((u8)ReadAddr);   
	for(i=0;i<NumByteToRead;i++)
  { 
			pBuffer[i]=SPI1_ReadWriteByte(0XFF);   //ѭ������  
	}
	W25Q64_CS_H;  				    	      
}
/************************************************************************************************
 * ����   : SPI��һҳ��д��256���ֽڵ�����
 * ����   : ���ݴ洢�� ��ʼ��ȡ��ַ Ҫд�������ֽ���
 * ����   : ��
 * ˵��   : Ҫд�������ֽ������ܳ�����ҳʣ����ֽ���
 *************************************************************************************************/  	 
void W25Q64_Write_Page(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)
{
 	uint16_t i;  
	W25Q64_Write_Enable();                  //SET WEL 
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_PageProgram);      //����дҳ����   
	SPI1_ReadWriteByte((u8)((WriteAddr)>>16)); //����24bit��ַ    
	SPI1_ReadWriteByte((u8)((WriteAddr)>>8));   
	SPI1_ReadWriteByte((u8)WriteAddr);   
	for(i=0;i<NumByteToWrite;i++)SPI1_ReadWriteByte(pBuffer[i]);//ѭ��д��  
	W25Q64_CS_H;                            //ȡ��Ƭѡ 
	W25Q64_Wait_Busy();					   //�ȴ�д�����
} 
/************************************************************************************************
 * ����   : �޼���дSPI Flash
 * ����   : ���ݴ洢��  ��ʼд��ĵ�ַ  Ҫд��������
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/ 
void W25Q64_Write_NoCheck(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite)   
{ 			 		 
	u16 pageremain;	   
	pageremain=256-WriteAddr%256; //��ҳʣ����ֽ���		 	    
	if(NumByteToWrite<=pageremain)pageremain=NumByteToWrite;//������256���ֽ�
	while(1)
	{	   
		W25Q64_Write_Page(pBuffer,WriteAddr,pageremain);
		if(NumByteToWrite==pageremain)break;//д�������
	 	else //NumByteToWrite>pageremain
		{
			pBuffer+=pageremain;
			WriteAddr+=pageremain;	

			NumByteToWrite-=pageremain;			  //��ȥ�Ѿ�д���˵��ֽ���
			if(NumByteToWrite>256)pageremain=256; //һ�ο���д��256���ֽ�
			else pageremain=NumByteToWrite; 	  //����256���ֽ���
		}
	};	    
} 
/************************************************************************************************
 * ����   : дSPI Flash
 * ����   : ���ݴ洢�� ��ʼд��ĵ�ַ  Ҫд������ֽ���
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/ 
uint8_t W25Q64_BUFFER[4096];		 
void W25Q64_Write(u8* pBuffer,u32 WriteAddr,u16 NumByteToWrite)   
{ 
	uint32_t secpos;
	uint16_t secoff;
	uint16_t secremain;	   
 	uint16_t i;    
	uint8_t * W25Q64_BUF;	  
  W25Q64_BUF=W25Q64_BUFFER;	     
 	secpos=WriteAddr/4096;//������ַ  
	secoff=WriteAddr%4096;//�������ڵ�ƫ��
	secremain=4096-secoff;//����ʣ��ռ��С   
 	//printf("ad:%X,nb:%X\r\n",WriteAddr,NumByteToWrite);//������
 	if(NumByteToWrite<=secremain)secremain=NumByteToWrite;//������4096���ֽ�
	while(1) 
	{	
		W25Q64_Read(W25Q64_BUF,secpos*4096,4096);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(W25Q64_BUF[secoff+i]!=0XFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			W25Q64_Erase_Sector(secpos);//�����������
			for(i=0;i<secremain;i++)	   //����
			{
				W25Q64_BUF[i+secoff]=pBuffer[i];	  
			}
			W25Q64_Write_NoCheck(W25Q64_BUF,secpos*4096,4096);//д����������  

		}else W25Q64_Write_NoCheck(pBuffer,WriteAddr,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumByteToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;//������ַ��1
			secoff=0;//ƫ��λ��Ϊ0 	 
			pBuffer+=secremain;  //ָ��ƫ��
			WriteAddr+=secremain;//д��ַƫ��	   
		  NumByteToWrite-=secremain;				//�ֽ����ݼ�
			if(NumByteToWrite>4096)secremain=4096;	//��һ����������д����
			else secremain=NumByteToWrite;			//��һ����������д����
		}	 
	};	 
}
/************************************************************************************************
 * ����   : ��������оƬ
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/ 
void W25Q64_Erase_Chip(void)   
{      	
  W25Q64_Write_Enable();                  //SET WEL 
	W25Q64_Wait_Busy();   
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_ChipErase);        //����Ƭ��������  
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
	W25Q64_Wait_Busy();   				   //�ȴ�оƬ��������
}  
/************************************************************************************************
 * ����   : ����һ������
 * ����   : ������ַ������ʵ���������ã�
 * ����   : ��
 * ˵��   : ����һ����������ʱ��150ms
 *************************************************************************************************/ 
void W25Q64_Erase_Sector(uint32_t Dst_Addr)   
{  
	//����falsh�������,������   
 //	printf("fe:%x\r\n",Dst_Addr); 
 	Dst_Addr*=4096;
	W25Q64_Write_Enable();                  //SET WEL 	 
	W25Q64_Wait_Busy();   
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_SectorErase);      //������������ָ�� 
	SPI1_ReadWriteByte((u8)((Dst_Addr)>>16));  //����24bit��ַ    
	SPI1_ReadWriteByte((u8)((Dst_Addr)>>8));   
	SPI1_ReadWriteByte((u8)Dst_Addr);  
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
	W25Q64_Wait_Busy();   				   //�ȴ��������
	  
}  
/************************************************************************************************
 * ����   : �ȴ�����
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/ 
void W25Q64_Wait_Busy(void)   
{   
	while((W25Q64_ReadSR()&0x01)==0x01);   // �ȴ�BUSYλ���
}  
/************************************************************************************************
 * ����   : �������ģʽ
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/ 
void W25Q64_PowerDown(void)   
{ 
	W25Q64_CS_L;                            //ʹ������   
	SPI1_ReadWriteByte(W25X_PowerDown);        //���͵�������  
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
	delay_us(3);                               //�ȴ�TPD  
}   
/************************************************************************************************
 * ����   : ����
 * ����   : ��
 * ����   : ��
 * ˵��   : ��
 *************************************************************************************************/ 
void W25Q64_WAKEUP(void)   
{  
  W25Q64_CS_L;                            //ʹ������   
  SPI1_ReadWriteByte(W25X_ReleasePowerDown);   //  send W25X_PowerDown command 0xAB    
	W25Q64_CS_H;                            //ȡ��Ƭѡ     	      
  delay_us(3);                               //�ȴ�TRES1
}   
