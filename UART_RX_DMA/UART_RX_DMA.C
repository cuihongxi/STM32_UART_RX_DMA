#include "UART_RX_DMA.H"

/**
		���ò�����DMA
*/
void UartRX_Start(UART_HandleTypeDef* huart, DMA_HandleTypeDef* hdma_usart_rx, DMA_rxStr* dmaStr)
{
	dmaStr->length = RXBUF_LEN;	
	dmaStr->callback_IDLE = UsartInIT_IDLE;
	dmaStr->huart = huart;
	dmaStr->hdma_usart_rx = hdma_usart_rx;

	HAL_UART_Receive_DMA(dmaStr->huart, dmaStr->buf, dmaStr->length);
	__HAL_UART_ENABLE_IT(dmaStr->huart, UART_IT_IDLE);						// �������н����ж� 
	__HAL_UART_CLEAR_IDLEFLAG(dmaStr->huart); 								// ������ж�

}

//DMA�����жϺ���
void DMAInUART_IDLE(DMA_rxStr* pRx_str)
{
	if (__HAL_UART_GET_FLAG(pRx_str->huart, UART_FLAG_IDLE)) //IDLE�жϡ���ע��IDLE�жϱ�־������Ƕ�һ��USART_SR�Ĵ��������Ŷ�һ��USART_DR�Ĵ���
	{

		if (pRx_str->hdma_usart_rx->Instance->CNDTR <= pRx_str->length)
		{
			pRx_str->num = pRx_str->length - pRx_str->hdma_usart_rx->Instance->CNDTR;
			HAL_UART_AbortReceive(pRx_str->huart);				// huart->RxState = HAL_UART_STATE_READY����HAL_DMA_Abort(hdma_usart_rx)
			pRx_str->hdma_usart_rx->Instance->CNDTR = pRx_str->length;	// ����Ĵ���ֻ����ͨ��������(DMA_CCRx��EN=0)ʱд��  
		
		}

		__HAL_UART_CLEAR_IDLEFLAG(pRx_str->huart);
		HAL_UART_Receive_DMA(pRx_str->huart, pRx_str->buf, pRx_str->length);
	}

}
/* ���ڽ����ж��е��õĺ��� */
void UsartInIT_IDLE(DMA_rxStr* pRx_str)
{
	DMAInUART_IDLE(pRx_str);
}