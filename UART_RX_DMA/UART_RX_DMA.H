/**
	2019��8��3��16:32:09
	���ڽ���DMA
	
	ʹ�÷�����
						1. ��������� DMA_rxStr rxStr 
						2. ���� UartRX_Start ���������ô��ھ����DMA�����DMA���н����жϿ���
						3. it.c �ļ��У������� UsartInIT_IDLE(DMA_rxStr* pRx_str) ���봮���ж� global interrupt �У�
						   ������ͷ�ļ��������
						4. ������������ ����� rxStr.num ��Ϊ 0 ����˵�����յ����ݣ�����ΪrxStr.num�������ݽ��д����������rxStr.num
						
*/

#ifndef _UART_RX_DMA_H
#define	_UART_RX_DMA_H

#include "stm32f1xx_hal.h"					

#define RXBUF_LEN 	100						// ���ջ��泤��

//DMA���սṹ��
typedef struct dma_rxstr{
	uint8_t 	buf[RXBUF_LEN];									// ���ջ���	, ע������ж�̬�ڴ���䣬������ý��ж�̬����
	uint32_t	length;													// ������ջ�����ܳ���
	uint32_t 	num;														// �ѽ��յĳ���
	UART_HandleTypeDef* huart;								// ���ھ��
	DMA_HandleTypeDef* hdma_usart_rx;					// DMA���վ��
	void(*callback_IDLE)(struct dma_rxstr *);	// ���봮���ж��еĻص�����
}DMA_rxStr;



/*
	����
*/

void UartRX_Start(UART_HandleTypeDef* huart, DMA_HandleTypeDef* hdma_usart_rx, DMA_rxStr* dmaStr);	//���ò�����DMA
void UsartInIT_IDLE(DMA_rxStr* pRx_str);	//�����ж��еĺ���			

#endif