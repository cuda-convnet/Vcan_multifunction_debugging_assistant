#pragma once
#include "ebox.h"
class UartVscan
{
	uint8_t cmd;
	Uart *uart;	
public:
	UartVscan(Uart *uartX);
	//��ʼ��
	void begin(uint32_t baud_rate, uint8_t data_bit, uint8_t parity, float stop_bit, uint8_t _use_dma);
	void begin(uint32_t baud_rate, uint8_t _use_dma /*= 1*/);

	//���ͻҶ�ͼ��
	void sendGreyImage(uint8_t* imgaddr, uint32_t width,uint32_t height);

	//����ccd
	void sendCCD(uint8_t  *ccdaddr,int ccdsize);
	void sendCCD(uint8_t  *ccdaddr, uint8_t *ccdaddr2,int ccdsize);


	//����ʾ����
	template<typename T>
	T sendOscilloscope(T x)
	{
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		union
		{
			T f;
			uint8_t c[sizeof(f)];
		}dataBuf;
		dataBuf.f = x;
		for (int i = 0; i < sizeof(x); i++)
			uart->write(dataBuf.c[i]);
		uart->write(~cmd);
		uart->write(cmd);
	}

	template<typename T>
	T sendOscilloscope(T *y,int n)
	{
		cmd = 3;
		uart->write(cmd);
		uart->write(~cmd);
		union
		{
			T f;
			uint8_t c[sizeof(f)];
		}dataBuf;
		for (int m = 0; m < n; m++)
		{
			dataBuf.f = y[m];
			for (int i = 0; i < sizeof(dataBuf.f); i++)
				uart->write(dataBuf.c[i]);
		}
		uart->write(~cmd);
		uart->write(cmd);
	}
};