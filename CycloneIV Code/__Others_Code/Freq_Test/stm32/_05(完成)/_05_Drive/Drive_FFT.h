#ifndef __FFT_H__
#define __FFT_H__
#include "OS_StartFile.h"

#ifndef PI
#define PI 3.1415926535897932384626433832795028841971f 
#endif

typedef struct complex //��������
{
    float real;       //ʵ��
    float imag;       //�鲿
} complex;
  

void FFT_Exchange(u16 *Buff,u16 Lenth);
void FFT_Exchange_Measuring(void);

#endif




