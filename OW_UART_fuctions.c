	/**
  ******************************************************************************
  * @file    uart_fuctions_for_OVERWATCH.c 
  * @author  Gachon Univ. TEAM TAKEOUT. Juhyeong Kim.
  * @version V1.1.0
  * @date    12-July-2017
  * @brief   UART fuctions for OVERWATCH project.
	*
	*	
	*
	*	USART_Send(USART_TypeDef* USARTx, char data)
	*	USART_String_Send(USART_TypeDef* USARTx, char *str)
	*
	*	USART_Receive(USART_TypeDef* USARTx)
	*	USART_String_Receive(USART_TypeDef* USARTx, char *buffer)
	*
	*	USART_CR_LF(USART_TypeDef* USARTx)
	*
  ******************************************************************************
  */
 
/*Transmit 1byte data */
void USART_Send(USART_TypeDef* USARTx, char data)
{
	while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)));
	USART_SendData(USARTx, data);
}

/*Transmit String data. This fuction needs null character in the data */
void USART_String_Send(USART_TypeDef* USARTx, char *str) 
{
		while(*str != 0)
		{
			while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)));
			USART_SendData(USARTx, *str);
			str++;
		}
}

/*Receive 1byte data */
char USART_Receive(USART_TypeDef* USARTx)
{
	while(!(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)));
	return USART_ReceiveData(USARTx);
}

/*Receive String data. This fuction needs null character in the data */
void USART_String_Receive(USART_TypeDef* USARTx, char *buffer)
{
		while(!(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)));
		while((*buffer = USART_ReceiveData(USARTx))!= '\0' )
		{
			buffer++;
			while(!(USART_GetFlagStatus(USARTx, USART_FLAG_RXNE)));
		}
}

/*Transmit Carriage return and Line feed */
void USART_CR_LF(USART_TypeDef* USARTx)
{
		while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)));
		USART_SendData(USARTx, '\r');
		while(!(USART_GetFlagStatus(USARTx, USART_FLAG_TXE)));
		USART_SendData(USARTx, '\n');
}
