//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//

//TFT��ʾ���ļ�
#include "my_TFT.h"
#include "text.h"	

/* ˽�ж���ṹ�� --------------------------------------------------------------------------------*/
typedef struct
{
  __IO uint16_t LCD_REG;
  __IO uint16_t LCD_RAM;
} LCD_TypeDef;
/* Note: LCD /CS is NE3 - Bank 3 of NOR/SRAM Bank 1~4 */
#define LCD_BASE           ((uint32_t)(0x60000000))
#define LCD                ((LCD_TypeDef *) LCD_BASE)





void TFT_Init(void)
{  
	TFT_LCD_Init();	
	font_init();  //����ֿ�
	LCD_Clear(BLACK);//����	
	TextColor = WHITE;
	BackColor = BLACK;
		
}




//����
//x,y:����
//POINT_COLOR:�˵����ɫ
//=========================================================================
void LCD_DrawPoints(u16 x,u16 y)
{
PutPixel(x,y);
}
//=========================================================================



//����
//x1,y1:�������
//x2,y2:�յ�����
//=========================================================================
void LCD_DrawLines(u16 x1, u16 y1, u16 x2, u16 y2)
{
	
LCD_DrawuniLine(x1, y1,x2,y2);
}
//=========================================================================


//��ָ����������䵥����ɫ
//(sx,sy),(ex,ey):�����ζԽ�����,�����СΪ:(ex-sx+1)*(ey-sy+1)   
//color:Ҫ������ɫ
//=========================================================================
void LCD_Fill(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{	
	uint32_t x,y;
	u16 temp=TextColor;
	TextColor=color;
	for(y=y1;y<y2;y++)
	{
		LCD_SetCursor(x1,y);			
		LCD_WriteRAM_Prepare();
		
		for(x=x1;x<x2;x++)
		LCD->LCD_RAM =color;
	}
	TextColor=temp;
}
//=========================================================================


//��ʾ�ַ���
//x y ��ʼ����
//*p:�ַ�����ʼ��ַ	
//=========================================================================
void LCD_ShowString(u16 x,u16 y,u8 *p)
{
LCD_DisplayStringLine(y,x,p);
}
//=========================================================================



//x,y:�������
//digit:����λ��
//num:��ֵ(0~4294967295).
//size:�����С  12/16/24/90(Ԥ��λ����ʱ����ʵ��)
//=========================================================================
void LCD_ShowNum(u16 x,u16 y,double num,u8 digit,u8 size)
{
	u8 ch_inte[50]={0};
	int i=0,_0=0;
	u32 integer=(u32)num,temp=integer,len_inte=0,temp0=temp,digit0=digit;
	double temp01=num;
	digit++;
	temp01*=10;
	temp0*=10;
	while((--digit0)&&(u32)(temp01-temp0)==0)
	{	
		_0++;
		temp01*=10;
		temp0*=10; 
	}
	
	while(digit--)
	num*=10,temp*=10;
	temp=integer*10;
	while(temp/=10) len_inte++;
	
	if(len_inte==0){Show_String(x,y,"0",size);x=x+size/2;}
	
	len_inte--;
	  
	temp=len_inte;
	for(i=len_inte;i>=0;i--) ch_inte[i]='0'+integer%10,integer/=10;
	 
	len_inte=temp+1;
	Show_String(x,y,ch_inte,size);
	
	
	
}
//=========================================================================



//��ʵ��Բ��
//(x,y):���ĵ�
//size:Բ��ĵĴ�С
//=========================================================================
void LCD_Big_Point(u16 x,u16 y,u16 size,u16 color)
{
	u16 temp=TextColor;
	TextColor=color;
	if (x<=size) x=size+1;
	for(;size>0;size--)
	LCD_DrawCircle(x,y,size);
	TextColor=temp;
}
//=========================================================================




//��ʵ�ľ���
//x,y,xi,yi �����ĸ���
//=========================================================================
void LCD_Big_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{	
	u16 temp=TextColor;
	TextColor=color;
	for(;x2>=x1;x2--)
	LCD_DrawLines(x2,y1,x2,y2);
	TextColor=temp;
}
//=========================================================================


//�����ľ���
//x,y,xi,yi �����ĸ���
//=========================================================================
void Draw_Rect(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 tc=TextColor;
	TextColor=color;
	LCD_DrawLines(x1,y1,x2,y1);
	LCD_DrawLines(x1,y2,x2,y2);
	LCD_DrawLines(x2,y1,x2,y2);
	LCD_DrawLines(x1,y1,x1,y2);
	TextColor=tc;
}
//=========================================================================




//��������
//mode �Ƿ���д�߿� 1д   0��д
//=========================================================================
void Creat_Coord(u16 x1,u16 y1,u16 x2,u16 y2,float density,u8 mode)
{
	u16 x=0,y=0;					
	density=(density+1)/10;
	if(mode==1)	      			
	{LCD_Fill(x1,y1,x2,y2,BLACK);}	//д�߿�		
												
	LCD_Fill(x1+density*5,y1+density*5,x2-density*5,y2-density*5,WHITE); //д����						
	
	//��С��
	for(x=x1;x<x2;x+=10*density)													
	for(y=y1;y<y2;y+=10*density)							
	{LCD_Big_Point(x,y,1,GRAY);}		
																			
	//�����
	for(x=x1;x<x2;x+=50*density)													
	for(y=y1;y<y2;y+=50*density)							
	{LCD_Big_Point(x,y,2,BLACK);}		
		
	//�����ұ߿��
	for(y=y1+10*density;y<y2;y+=10*density)							
	{
	LCD_Big_Rect(x1+density*5,y,x1+density*8,y+density,BLACK);//��
	LCD_Big_Rect(x2-density*8,y,x2-density*5,y+density,BLACK);//��
	}
	//�����±߿��
	for(x=x1+10*density;x<x2;x+=10*density)							
	{
	LCD_Big_Rect(x,y1+density*5,x+density,y1+density*8,BLACK);//��
	LCD_Big_Rect(x,y2-density*5,x+density,y2-density*8,BLACK);//��
	}
	
	
	
	
}
//=========================================================================



//��ʾͼƬ
//RGB565  16λ�����ʾ
//���ɷ���
//��ͷ����
//=========================================================================
void Show_Picture0(u16 x1,u16 y1,const u8 *pic)
{	
	u16 x,y,p_color;
	u16 len_x=(pic[2]<<8)|pic[3];
	u16 len_y=(pic[4]<<8)|pic[5];
	
	for(y=0;y<len_y;y++)
	for(x=0;x<len_x*2;x+=2)
	{
	p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2];
	LCD_SetCursor(x/2+x1,y+y1);//���ù��λ�� 
    LCD_WriteRAM_Prepare(); 
    LCD_WriteRAM(p_color);
	
	}
	
}
//=========================================================================



//��ʾͼƬ
//RGB565  16λ�����ʾ
//�ɷ���
//��ͷ����
//=========================================================================
void Show_Picture1(u16 x1,u16 y1,u16 x2,u16 y2,const u8 *pic)
{	
	u16 x,y,p_color;
	float density_x,density_y;
	u16 len_x=(pic[2]<<8)|pic[3];
	u16 len_y=(pic[4]<<8)|pic[5];
	
	density_x=(float)(x2-x1)/len_x; 
	density_y=(float)(y2-y1)/len_y; 
	
	for(y=0;y<len_y;y++) 
	for(x=0;x<len_x*2;x+=2) 
	{ 
	p_color=pic[x+y*len_x*2]*16*16+pic[(x+1)+y*len_x*2]; 
	LCD_SetCursor((x/2)*density_x+x1,y*density_y+y1);//���ù��λ�� 
    LCD_WriteRAM_Prepare(); 
    LCD_WriteRAM(p_color); 
	
		
		
	}
	
}

//=========================================================================



//=========================================================================
void  Show_String(uint16_t x,uint16_t y,u8*str,u8 size)
{

// Show_Str(y,x,str,size);
	
	
}

 

//=========================================================================
//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}		

void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp,tem[10];
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				tem[0]='0';
				if(mode&0X80)Show_String(x+(size/2)*t,y,tem,size);  
				else Show_String(x+(size/2)*t,y," ",size);  
 				continue;
			}else enshow=1; 
		 	 
		}
		tem[0]=temp+'0';
	 	Show_String(x+(size/2)*t,y,tem,size); 
	}
} 
//��ʾ����,��λΪ0
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С 12/16/24
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_Show0Num(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp,tem[10];
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				
				Show_String(x+(size/2)*t,y,"0",size);
				continue;
			}else enshow=1; 
		 	 
		}
		if(temp <= 9) tem[0]=temp+'0'; 
	 	Show_String(x+(size/2)*t,y,tem,size); 
	}
} 



//��ʾС��
//x,y:�������
//digit:����λ��
//size:�����С  12/16/24
void LCD_ShowDecim(u16 x,u16 y,double num,u8 digit,u8 len,u8 size)//���� ����.����
{ 
	
	volatile unsigned long int digitnum=LCD_Pow(10,digit);                              
	volatile unsigned long int numd=(u32)(num*digitnum);     	                   
	volatile unsigned long int temp;                                               
	len=len-digit-1;
	temp=numd/digitnum;
	LCD_ShowxNum(x,y,temp,len,size,1);//��ʾ��������
	temp=(unsigned long int)(numd-((double)(numd/digitnum)*digitnum));
	Show_String(x+len*(size/2),y,".",size);
	LCD_Show0Num(x+(len+1)*(size/2),y,temp,digit,size);//��ʾС������
	

} 





//*****************************************(C) COPYRIGHT 2015 WindRises**************************************//
