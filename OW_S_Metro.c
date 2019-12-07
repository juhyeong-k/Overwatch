/*
 *	S_Metro_receive function
 *	Station_name should be encoded in utf-8
 */
void S_Metro_request(Struct_Settings* System_settings)
{
	char length[5];
	int length_int = 121 + get_String_size(System_settings->M_Station_NM);
	sprintf(length, "%d", length_int);
	
	/*Server_Link has a endless while loop. If Server_Link didn't work correctly, program will stop. */
	Server_Link("swopenapi.seoul.go.kr");

	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	
	/* Caution! Endless loop! */
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3, "GET /api/subway/56695751706a756835374f6d466755/xml/realtimeStationArrival/0/10/");
	USART_String_Send(USART3, System_settings->M_Station_NM);
	USART_String_Send(USART3, " HTTP/1.1\r\nHost: swopenapi.seoul.go.kr\r\n\r\n\r\n");
}
/*
 * 상행 : 0xEC 0x83 0x81 0xED 0x96 0x89				0
 * 하행 : 0xED 0x95 0x98 0xED 0x96 0x89				1
 * 내선 : 0xEB 0x82 0xB4 0xEC 0x84 0xA0				1
 * 외선 : 0xEC 0x99 0xB8 0xEC 0x84 0xA0				0
 */
void S_Metro_parsing(Struct_Settings* System_settings, Struct_Info* System_info)
{
	char temp;
	char local_updnLine = System_settings->M_updnLine[0];
	while(1)
	{
		if(USART_Receive(USART3) == 'w')
			if(USART_Receive(USART3) == 'a')
				if(USART_Receive(USART3) == 'y')
					if(USART_Receive(USART3) == 'I')
						if(USART_Receive(USART3) == 'd')
							if(USART_Receive(USART3) == '>')
								if(USART_Receive(USART3) == System_settings->M_subwayId[0])
								if(USART_Receive(USART3) == System_settings->M_subwayId[1])
								if(USART_Receive(USART3) == System_settings->M_subwayId[2])
								if(USART_Receive(USART3) == System_settings->M_subwayId[3])	break;
	}
	while(1)
	{
		if(USART_Receive(USART3) == 'o')
			if(USART_Receive(USART3) == 'r')
				if(USART_Receive(USART3) == 'd')
					if(USART_Receive(USART3) == 'k')
						if(USART_Receive(USART3) == 'e')
							if(USART_Receive(USART3) == 'y')
								if(USART_Receive(USART3) == '>')
									if(USART_Receive(USART3) == local_updnLine)	break;
	}
	
	temp = USART_Receive(USART3);
	System_info->remain[0] = USART_Receive(USART3);
	System_info->remain[1] = USART_Receive(USART3);
	System_info->remain[2] = USART_Receive(USART3);
	
	while(1)
	{
		if(USART_Receive(USART3) == 'r')
			if(USART_Receive(USART3) == 'v')
				if(USART_Receive(USART3) == 'l')
					if(USART_Receive(USART3) == 'D')
						if(USART_Receive(USART3) == 't')
							if(USART_Receive(USART3) == '>')
							{
								short index = 0;
								while(1)
								{
									temp = USART_Receive(USART3);
									if(temp != '<')	{System_info->barvlDt[index] = temp; index++;}
									else break;
								}
								break;
							}
	}
	USART_String_Send(USART2, "\r\nAPI : S_Metro");
	USART_String_Send(USART2, "\r\narr prediced time : ");
	USART_String_Send(USART2, System_info->barvlDt);
	USART_String_Send(USART2, "\r\narr remain : ");
	USART_String_Send(USART2, System_info->remain);
	USART_String_Send(USART2, "\r\n\r\n");
}
