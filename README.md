﻿	2019年8月3日16:32:09
	串口接收DMA
	
	使用方法：
						1. 定义变量： DMA_rxStr rxStr 
						2. 调用 UartRX_Start 函数，配置串口句柄，DMA句柄；DMA空闲接收中断开启
						3. it.c 文件中，将函数 UsartInIT_IDLE(DMA_rxStr* pRx_str) 放入串口中断 global interrupt 中，
						   并包含头文件传入参数
						4. 主函数做处理 ，如果 rxStr.num 不为 0 ，则说明接收到数据，长度为rxStr.num，对数据进行处理，并清空rxStr.num
