/**
	2019年8月3日16:32:09
	串口接收DMA
	
	使用方法：
						1. 定义变量： DMA_rxStr rxStr 
						2. 调用 UartRX_Start 函数，配置串口句柄，DMA句柄；DMA空闲接收中断开启
						3. it.c 文件中，将函数 UsartInIT_IDLE(DMA_rxStr* pRx_str) 放入串口中断 global interrupt 中，
						   并包含头文件传入参数
						4. 主函数做处理 ，如果 rxStr.num 不为 0 ，则说明接收到数据，长度为rxStr.num，对数据进行处理，并清空rxStr.num
						
*/

#ifndef _UART_RX_DMA_H
#define	_UART_RX_DMA_H

#include "stm32f1xx_hal.h"					

#define RXBUF_LEN 	100						// 接收缓存长度

//DMA接收结构体
typedef struct dma_rxstr{
	uint8_t 	buf[RXBUF_LEN];									// 接收缓存	, 注：如果有动态内存分配，这里最好进行动态分配
	uint32_t	length;													// 保存接收缓存的总长度
	uint32_t 	num;														// 已接收的长度
	UART_HandleTypeDef* huart;								// 串口句柄
	DMA_HandleTypeDef* hdma_usart_rx;					// DMA接收句柄
	void(*callback_IDLE)(struct dma_rxstr *);	// 放入串口中断中的回调函数
}DMA_rxStr;



/*
	函数
*/

void UartRX_Start(UART_HandleTypeDef* huart, DMA_HandleTypeDef* hdma_usart_rx, DMA_rxStr* dmaStr);	//配置并启动DMA
void UsartInIT_IDLE(DMA_rxStr* pRx_str);	//放入中断中的函数			

#endif
