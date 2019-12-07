/**
  ******************************************************************************
  * @file			OW_Air.c
  * @author		Gachon Univ. TEAM TAKEOUT. Juhyeong Kim.
  * @version	V1.0.0
  * @date			12-July-2017
  * @brief		Air_request(&System_settings);
	*						Air_parsing(&System_info);
	*						wait_CIPCLOSE();
	*
  ===============================================================================
	*	@attention
	*		MAKE FLAG SYSTEM! This file has endless loops.
	*		Using order : Air request -> PM10 parsing -> Air request -> PM25 parsing
	*									or
	*									Air request -> Air parsing. But the Air parsing fuction has two endless loop.
  */
void Air_request(Struct_Settings* System_settings)
{
	int length_int = 262 + get_String_size(System_settings->A_Station_NM);
	char length[4];
	sprintf(length, "%d", length_int);
	
	/*Server_Link has a endless while loop. If Server_Link didn't work correctly, program will stop. */
	Server_Link("openapi.airkorea.or.kr");
	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	
	/* Caution! Endless loop! */
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3,"GET /openapi/services/rest/ArpltnInforInqireSvc/getMsrstnAcctoRltmMesureDnsty?ServiceKey=oKkRSmbYF6oWEeqgrxSkahZvUmDbY5AOESsWfRK87khxbjutCbvfrBcVHAJOUKP0W3ldMEEyM6Qn%2F1Dyz8zVKg%3D%3D&stationName=");
	USART_String_Send(USART3,System_settings->A_Station_NM);
	USART_String_Send(USART3,"&dataTerm=daily&ver=1.3 HTTP/1.1\r\nHost: openapi.airkorea.or.kr\r\n\r\n");
}
void Air_parsing(Struct_Info* System_info)
{
	while(1)
	{
		if(USART_Receive(USART3) == '1')	{
			if(USART_Receive(USART3) == '0')
				if(USART_Receive(USART3) == 'G')
					if(USART_Receive(USART3) == 'r')
						if(USART_Receive(USART3) == 'a')
							if(USART_Receive(USART3) == 'd')
								if(USART_Receive(USART3) == 'e')
									if(USART_Receive(USART3) == '1')
										if(USART_Receive(USART3) == 'h')
											if(USART_Receive(USART3) == '>')	{System_info->PM10_grade[0] = USART_Receive(USART3); break;}
		}
	}
	while(1)
	{
		if(USART_Receive(USART3) == '2')	{
			if(USART_Receive(USART3) == '5')
				if(USART_Receive(USART3) == 'G')
					if(USART_Receive(USART3) == 'r')
						if(USART_Receive(USART3) == 'a')
							if(USART_Receive(USART3) == 'd')
								if(USART_Receive(USART3) == 'e')
									if(USART_Receive(USART3) == '1')
										if(USART_Receive(USART3) == 'h')
											if(USART_Receive(USART3) == '>')	{System_info->PM25_grade[0] = USART_Receive(USART3);break;}
		}
	}
	USART_String_Send(USART2, "\r\nAPI : Air");
	USART_String_Send(USART2, "\r\nPM10 grade : ");
	USART_String_Send(USART2, System_info->PM10_grade);
	USART_String_Send(USART2, "\r\nPM25 grade : ");
	USART_String_Send(USART2, System_info->PM25_grade);
	USART_String_Send(USART2, "\r\n\r\n");
}
