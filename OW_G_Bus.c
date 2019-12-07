/**
  ******************************************************************************
  * @file			OW_G_Bus.c
  * @author		Gachon Univ. TEAM TAKEOUT. Juhyeong Kim.
  * @version	V1.0.0
  * @date			12-July-2017
  * @brief		G_Bus_request(&System_settings);
	*						G_Bus_parsing(&System_info);
	*						wait_response_end();
	*						AT_CIPCLOSE();
	*
  ===============================================================================
	*	@attention
	*		
  */
void G_Bus_request(Struct_Settings* System_settings)
{
	char length[5];
	int length_int = 195 + get_String_size(System_settings->G_Station_ID) + get_String_size(System_settings->G_Route_ID);
	sprintf(length, "%d", length_int);
	
	/*Server_Link has a endless while loop. If Server_Link didn't work correctly, program will stop. */
	Server_Link("openapi.gbis.go.kr");

	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	
	/* Caution! Endless loop! */
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3, "GET /ws/rest/busarrivalservice?serviceKey=oKkRSmbYF6oWEeqgrxSkahZvUmDbY5AOESsWfRK87khxbjutCbvfrBcVHAJOUKP0W3ldMEEyM6Qn%2F1Dyz8zVKg%3D%3D&stationId=");
	USART_String_Send(USART3, System_settings->G_Station_ID);
	USART_String_Send(USART3, "&routeId=");
	USART_String_Send(USART3, System_settings->G_Route_ID);
	USART_String_Send(USART3, " HTTP/1.1\r\nHost: openapi.gbis.go.kr\r\n\r\n");
}
void G_Bus_parsing(Struct_Info* System_info)
{
	char temp;
		while(1)
		{
			if(USART_Receive(USART3) == 'o')
				if(USART_Receive(USART3) == 'n')
					if(USART_Receive(USART3) == 'N')
						if(USART_Receive(USART3) == 'o')
							if(USART_Receive(USART3) == '1')
								if(USART_Receive(USART3) == '>')
								{
									temp = USART_Receive(USART3);
									if(temp != '<')	System_info->locationNo1[0] = temp;
									temp = USART_Receive(USART3);
									if(temp != '<')	System_info->locationNo1[1] = temp;
									break;
								}
		}
		while(1)
		{
			if(USART_Receive(USART3) == 'o')
				if(USART_Receive(USART3) == 'n')
					if(USART_Receive(USART3) == 'N')
						if(USART_Receive(USART3) == 'o')
							if(USART_Receive(USART3) == '2')
								if(USART_Receive(USART3) == '>')
								{
									temp = USART_Receive(USART3);
									if(temp != '<')	System_info->locationNo2[0] = temp;
									temp = USART_Receive(USART3);
									if(temp != '<')	System_info->locationNo2[1] = temp;
									break;
								}
		}
		while(1)
		{
			if(USART_Receive(USART3) == 't')
				if(USART_Receive(USART3) == 'T')
					if(USART_Receive(USART3) == 'i')
						if(USART_Receive(USART3) == 'm')
							if(USART_Receive(USART3) == 'e')
								if(USART_Receive(USART3) == '1')
									if(USART_Receive(USART3) == '>')
									{
										temp = USART_Receive(USART3);
										if(temp != '<')	System_info->predictTime1[0] = temp;
										temp = USART_Receive(USART3);
										if(temp != '<')	System_info->predictTime1[1] = temp;
										break;
									}
		}
		while(1)
		{
			if(USART_Receive(USART3) == 't')
				if(USART_Receive(USART3) == 'T')
					if(USART_Receive(USART3) == 'i')
						if(USART_Receive(USART3) == 'm')
							if(USART_Receive(USART3) == 'e')
								if(USART_Receive(USART3) == '2')
									if(USART_Receive(USART3) == '>')
									{
										temp = USART_Receive(USART3);
										if(temp != '<')	System_info->predictTime2[0] = temp;
										temp = USART_Receive(USART3);
										if(temp != '<')	System_info->predictTime2[1] = temp;
										break;
									}
		}
	USART_String_Send(USART2, "\r\nAPI : G_Bus\r\n");
	USART_String_Send(USART2, "locationNo1 : ");
	USART_String_Send(USART2, System_info->locationNo1);
	USART_String_Send(USART2, "\r\nlocationNo2 : ");
	USART_String_Send(USART2, System_info->locationNo2);
	USART_String_Send(USART2, "\r\npredictTime1 : ");
	USART_String_Send(USART2, System_info->predictTime1);
	USART_String_Send(USART2, "\r\npredictTime2 : ");
	USART_String_Send(USART2, System_info->predictTime2);
	USART_String_Send(USART2, "\r\n\r\n");
}
