/**********************************************************************************************
 *   �� �� ����
 *
 *   ����ƽ̨��������STM32������
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�
 **********************************************************************************************/
#ifndef __PS2_H
#define __PS2_H

/* ���� --------------------------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "delay.h"
/* ˽�к� ------------------------------------------------------------------------------------*/

/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/* �������� ----------------------------------------------------------------------------------*/
void PS2_Keyboard_Init(void);
void PS2_ReadKeyCodon(volatile uint8_t* Key_Num);

/**********************************************************************************************
 *   �� �� ����Key_State.h
 *
 *   ����ƽ̨��������STM32������
 *
 *   ��    �ߣ��� ��
 *
 *   ��    �ڣ�2015.7.17
 **********************************************************************************************/


/* ���� --------------------------------------------------------------------------------------*/
#include "stm32f4xx.h"
#include "PS2.h"
/* ˽�к� ------------------------------------------------------------------------------------*/
#define Key_Num_0  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_0) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_1  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_1) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_2  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_2) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_3  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_3) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_4  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_4) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_5  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_5) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_6  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_6) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_7  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_7) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_8  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_8) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Num_9  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_9) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Enter  			((Key_FSM_PS2.Key_Code_Bef == Key_Code_Enter) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Add    			((Key_FSM_PS2.Key_Code_Bef == Key_Code_Add) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Minus       ((Key_FSM_PS2.Key_Code_Bef == Key_Code_Minus) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Ride       	((Key_FSM_PS2.Key_Code_Bef == Key_Code_Ride) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Div    			((Key_FSM_PS2.Key_Code_Bef == Key_Code_Div) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_NumLock			((Key_FSM_PS2.Key_Code_Bef == Key_Code_NumLock) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Point       ((Key_FSM_PS2.Key_Code_Bef == Key_Code_Point) && (Key_FSM_PS2.Key_Mode == 1))
#define Key_Back        ((Key_FSM_PS2.Key_Code_Bef == Key_Code_Back) && (Key_FSM_PS2.Key_Mode == 1))


#define Key_Code_0  				0x70
#define Key_Code_1  				0x69
#define Key_Code_2  				0x72
#define Key_Code_3  				0x7a
#define Key_Code_4  				0x6b
#define Key_Code_5  				0x73
#define Key_Code_6  				0x74
#define Key_Code_7  				0x6c
#define Key_Code_8  				0x75
#define Key_Code_9  				0x7d
#define Key_Code_Enter  		0xE0
#define Key_Code_Add        0x79
#define Key_Code_Minus      0x7b
#define Key_Code_Ride       0x7c
#define Key_Code_Div        0x4a
#define Key_Code_NumLock    0x77
#define Key_Code_Point      0x71
#define Key_Code_Back       0x66

/* ˽�нṹ�� --------------------------------------------------------------------------------*/

/**********************************************************************************************
 *�ṹ������__KEY_StateMachine	
 *
 *��		Ա��
 *					volatile uint16_t State_Flag  	��¼����״̬��־λ
 *					volatile uint16_t Key_Mode    	�ش�����ģʽ 
 *˵    ����	��0�� �ް���   ��1�������̰���   ��2������������     ��3��������������		
 *					volatile uint8_t KeyCode_Pre		��¼��ǰ����IO״̬
 *  				volatile uint8_t KeyCode_Bef		��¼ǰһ�ΰ���IO��״̬
 *					volatile uint16_t Key_Count     ��������������������					
 *
 *˵		������״̬��֧��16�������������ⰴ�����ʹ�ã�ֻ�����ж��尴��״̬����
 *********************************************************************************************/
typedef struct 
{
	volatile uint16_t State_Flag;       //״̬��״̬��־
	volatile uint8_t  Key_Code_Pre;     //��ǰ����
	volatile uint8_t  Key_Code_Bef;     //ǰһ�μ���
	volatile uint16_t Key_Mode;         //����ģʽ
	volatile uint16_t Key_Count;        //����������
	volatile uint16_t Key_Filt;         //PS2�����˲�
}__KEY_StateMachine;
extern __KEY_StateMachine  Key_FSM_PS2;
/* �������� ----------------------------------------------------------------------------------*/
void Key_StateSweep(__KEY_StateMachine *Key_FSM);


/* �ļ����� ----------------------------------------------------------------------------------*/



#endif

/* �ļ����� ----------------------------------------------------------------------------------*/


