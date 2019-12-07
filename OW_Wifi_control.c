/**
  ******************************************************************************
	*	@file		Wifi_control functions.c
	*	@date		2017.AUGUST.16
	* @brief	functions for WIFI control. This file is made for esp-8266 sparkfun dev board.
	*					I don't know about the version of firmware.
	* 				
	===============================================================================
	*	@attention
	*		AT_RST, ATE0, AT_CWMODE, AP_Link, Server_Link, AT_CIPSEND have endless while loop.
	*		If there is any problem, program will be stop.
	*				-> USE System_GetFlagStatus function in the functions_for_OVERWATCH.c file.
	*		! check_IPD() is not finished.
	*/

void AT_RST()
{
	System_status |= AT_RST_FLAG;
	USART_String_Send(USART3, "AT+RST\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == 'd')
			if(USART_Receive(USART3) == 'y')	break;
	}
	System_status &= (~AT_RST_FLAG);
}
void ATE0()
{
	USART_String_Send(USART3, "ATE0\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == 'O')
			if(USART_Receive(USART3) == 'K')	break;
	}
}
void AT_CWMODE()
{
	System_status |= AT_CWMODE_FLAG;
	USART_String_Send(USART3, "AT+CWMODE=3\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == 'g')
			if(USART_Receive(USART3) == 'e')	break;
	}
	System_status &= (~AT_CWMODE_FLAG);
}
/*
 * function for AP Link, Server Link.
 * Status 0 = Good, 1 = Wrong
 */
void AP_Link(char* SSID, char* PASSWORD)
{
	System_status |= AP_Link_FLAG;
	USART_String_Send(USART3, "AT+CWJAP=\"");
	USART_String_Send(USART3, SSID);
	USART_String_Send(USART3, "\",\"");
	USART_String_Send(USART3, PASSWORD);
	USART_String_Send(USART3, "\"\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == 'O')
			if(USART_Receive(USART3) == 'K')	break;
	}
	System_status &= (~AP_Link_FLAG);
}
void Server_Link(char* Server_IP)
{
	USART_String_Send(USART3, "AT+CIPSTART=\"TCP\",\"");
	USART_String_Send(USART3, Server_IP);
	USART_String_Send(USART3, "\",");
	USART_String_Send(USART3, "80");
	USART_String_Send(USART3, "\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == 'e')
			if(USART_Receive(USART3) == 'd')	break;
	}
}
void AT_CIPSEND(char* length)
{
	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
}
void AT_CIPCLOSE()
{
	USART_String_Send(USART3, "AT+CIPCLOSE\r\n");
}
void wait_CIPCLOSE()
{
	while(1)
	{
		if(USART_Receive(USART3) == 'U')	{
			if(USART_Receive(USART3) == 'n')
				if(USART_Receive(USART3) == 'l')
					if(USART_Receive(USART3) == 'i')
						if(USART_Receive(USART3) == 'n')
							if(USART_Receive(USART3) == 'k')	break;
		}
	}
}
void wait_response_end()
{
	while(1)
	{
		if(USART_Receive(USART3) == '/')	{
			if(USART_Receive(USART3) == 'r')
				if(USART_Receive(USART3) == 'e')
					if(USART_Receive(USART3) == 's')
						if(USART_Receive(USART3) == 'p')
							if(USART_Receive(USART3) == 'o')
								if(USART_Receive(USART3) == 'n')
									if(USART_Receive(USART3) == 's')
										if(USART_Receive(USART3) == 'e')
											if(USART_Receive(USART3) == '>')	break;
		}
	}
}
void Wifi_init(Struct_Settings* System_settings)
{
	AT_RST();
	ATE0();
	AT_CWMODE();
	AP_Link(System_settings->SSID,System_settings->PASSWORD);
	USART_String_Send(USART2, "\r\nWIFI_Init_Complete\r\n");
}
void remove_IPD()
{
	if(USART_Receive(USART3) == ' ')
		if(USART_Receive(USART3) == 'O')
			if(USART_Receive(USART3) == 'K')
				if(USART_Receive(USART3) == ' ')
					if(USART_Receive(USART3) == '+')
						if(USART_Receive(USART3) == 'I')
							if(USART_Receive(USART3) == 'P')
								if(USART_Receive(USART3) == 'D')
									if(USART_Receive(USART3) == ',')
										if(USART_Receive(USART3) == '1')
										{
											if(USART_Receive(USART3) == '0')
												if(USART_Receive(USART3) == '2')
													if(USART_Receive(USART3) == '4')
														if(USART_Receive(USART3) == ':');
										}
										else
										{
											USART_Receive(USART3);	USART_Receive(USART3);	USART_Receive(USART3);
										}
}
void WIFI_destroyer()
{
	for(short i = 0; i < 50; i++)
	{
		USART_Send(USART3, '0');
	}
}
