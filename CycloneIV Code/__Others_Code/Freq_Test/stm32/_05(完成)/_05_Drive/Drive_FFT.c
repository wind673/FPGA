#include "math.h"
#include "Drive_FFT.h"

#define SWAP(a,b)  tempr=(a);(a)=(b);(b)=tempr

void conjugate_complex(u16 n, complex in[], complex out[])
{
    int i = 0;
    for(i = 0; i < n; i++)
    {
        out[i].imag = -in[i].imag;
        out[i].real = in[i].real;
    }
}

void c_abs(complex f[], float out[], u16 n)
{
    int i = 0;
    float t;
    for(i = 0; i < n; i++)
    {
        t = f[i].real * f[i].real + f[i].imag * f[i].imag;
        out[i] = sqrt(t);
    }
}


void c_plus(complex a, complex b, complex *c)
{
    c->real = a.real + b.real;
    c->imag = a.imag + b.imag;
}

void c_sub(complex a, complex b, complex *c)
{
    c->real = a.real - b.real;
    c->imag = a.imag - b.imag;
}

void c_mul(complex a, complex b, complex *c)
{
    c->real = a.real * b.real - a.imag * b.imag;
    c->imag = a.real * b.imag + a.imag * b.real;
}

void c_div(complex a, complex b, complex *c)
{
    c->real = (a.real * b.real + a.imag * b.imag) / (b.real * b.real + b.imag * b.imag);
    c->imag = (a.imag * b.real - a.real * b.imag) / (b.real * b.real + b.imag * b.imag);
}


void Wn_i(u16 n, u16 i, complex *Wn, char flag)
{
    Wn->real = cos(2 * PI * i / n);
    if(flag == 1)
        Wn->imag = -sin(2 * PI * i / n);
    else if(flag == 0)
        Wn->imag = -sin(2 * PI * i / n);
}

//����Ҷ�仯
void fft(u16 N, complex f[])
{
    complex t, wn; //�м����
    int i, j, k, m, n, l, r, M;
    int la, lb, lc;
    /*----����ֽ�ļ���M=log2(N)----*/
    for(i = N, M = 1; (i = i / 2) != 1; M++);
    /*----���յ�λ����������ԭ�ź�----*/
    for(i = 1, j = N / 2; i <= N - 2; i++)
    {
        if(i < j)
        {
            t = f[j];
            f[j] = f[i];
            f[i] = t;
        }
        k = N / 2;
        while(k <= j)
        {
            j = j - k;
            k = k / 2;
        }
        j = j + k;
    }

    /*----FFT�㷨----*/
    for(m = 1; m <= M; m++)
    {
        la = pow(2, m); //la=2^m�����m��ÿ�����������ڵ���
        lb = la / 2; //lb�����m��ÿ�������������ε�Ԫ��
        //ͬʱ��Ҳ��ʾÿ�����ε�Ԫ���½ڵ�֮��ľ���
        /*----��������----*/
        for(l = 1; l <= lb; l++)
        {
            r = (l - 1) * pow(2, M - m);
            for(n = l - 1; n < N - 1; n = n + la) //����ÿ�����飬��������ΪN/la
            {
                lc = n + lb; //n,lc�ֱ����һ�����ε�Ԫ���ϡ��½ڵ���
                Wn_i(N, r, &wn, 1); //wn=Wnr
                c_mul(f[lc], wn, &t); //t = f[lc] * wn��������
                c_sub(f[n], t, &(f[lc])); //f[lc] = f[n] - f[lc] * Wnr
                c_plus(f[n], t, &(f[n])); //f[n] = f[n] + f[lc] * Wnr
            }
        }
    }
}

//����Ҷ��任
void ifft(u16 N, complex f[])
{
    int i = 0;
    conjugate_complex(N, f, f);
    fft(N, f);
    conjugate_complex(N, f, f);
    for(i = 0; i < N; i++)
    {
        f[i].imag = (f[i].imag) / N;
        f[i].real = (f[i].real) / N;
    }
}



void FFT_Exchange(u16 *Buff,u16 Lenth)
{
	u16 i = 0; 
	complex ComplexBuff[ADC1_DMA2_LENTH];
	for(i = 0;i < Lenth;i ++)
	{
		ComplexBuff[i].imag = 0;
		ComplexBuff[i].real = Buff[i];  
	}
	
	fft(Lenth,ComplexBuff);
	
	for(i = 0;i < Lenth;i ++)
	{ 
		Buff[i] = sqrt(ComplexBuff[i].imag*ComplexBuff[i].imag + ComplexBuff[i].real*ComplexBuff[i].real)/500;
	} 
}
 

void FFT_Exchange_Measuring(void)
{
	u16 i = 0; 
	complex ComplexBuff[MEASURING_ADC_LENTH];
	
	for(i = 0;i < MEASURING_ADC_LENTH;i ++)
	{
		ComplexBuff[i].imag = 0.0f;
		ComplexBuff[i].real = Measuring.FFT_Buff[i];   
	}
	
	fft(MEASURING_ADC_LENTH,ComplexBuff);
	
	for(i = 0;i < MEASURING_ADC_LENTH;i ++)
	{ 
		Measuring.FFT_Buff[i] = sqrt(ComplexBuff[i].imag*ComplexBuff[i].imag + ComplexBuff[i].real*ComplexBuff[i].real);
	} 
	 
}










