/* for parsing, you need arsId */
void S_Station_Ord_getter(Struct_Settings* System_settings)
{
	char temp;
	char local_rtNm[7];
	sprintf(local_rtNm,"%s",System_settings->rtNm);
	int rtNm_size = get_String_size(System_settings->rtNm);
	
	char length[5];
	int length_int = 187 + get_String_size(System_settings->S_arsId);
	sprintf(length, "%d", length_int);
	
	Server_Link("ws.bus.go.kr");
	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	
	/* Caution! Endless loop! */
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3, "GET /api/rest/stationinfo/getStationByUid?serviceKey=oKkRSmbYF6oWEeqgrxSkahZvUmDbY5AOESsWfRK87khxbjutCbvfrBcVHAJOUKP0W3ldMEEyM6Qn%2F1Dyz8zVKg%3D%3D&arsId=");
	USART_String_Send(USART3, System_settings->S_arsId);
	USART_String_Send(USART3, " HTTP/1.1\r\nHost: ws.bus.go.kr\r\n\r\n");

	while(1)
	{	
		if(USART_Receive(USART3)==local_rtNm[0])
			if(USART_Receive(USART3)==local_rtNm[1] | (local_rtNm[1] == 0))
				if(USART_Receive(USART3)==local_rtNm[2] | (local_rtNm[2] == 0))
					if(USART_Receive(USART3)==local_rtNm[3] | (local_rtNm[3] == 0))
						if(USART_Receive(USART3)==local_rtNm[4] | (local_rtNm[4] == 0))	break;
	}
	while(1)
	{
		if(USART_Receive(USART3)=='s')
			if(USART_Receive(USART3)=='t')
				if(USART_Receive(USART3)=='a')
					if(USART_Receive(USART3)=='O')
						if(USART_Receive(USART3)=='r')
							if(USART_Receive(USART3)=='d')
								if(USART_Receive(USART3)=='>')	{
									System_settings->S_Station_Ord[0] = USART_Receive(USART3);
									temp = USART_Receive(USART3);
									if(temp != '<')	System_settings->S_Station_Ord[1] = temp;
									temp = USART_Receive(USART3);
									if(temp != '<')	System_settings->S_Station_Ord[2] = temp;
									temp = USART_Receive(USART3);
									if(temp != '<')	System_settings->S_Station_Ord[3] = temp;
									break;
								}
	}
	while(1)
	{
		if(USART_Receive(USART3) == 'R')
			if(USART_Receive(USART3) == 'e')
				if(USART_Receive(USART3) == 's')
					if(USART_Receive(USART3) == 'u')
						if(USART_Receive(USART3) == 'l')
							if(USART_Receive(USART3) == 't')
								if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART2, "\r\nAPI : S_Station_Ord_getter");
	USART_String_Send(USART2, "\r\nstaOrd : ");
	USART_String_Send(USART2, System_settings->S_Station_Ord);
	USART_String_Send(USART2, "\r\n");
}
void S_Bus_request(Struct_Settings* System_settings)
{
	char length[5];
	int length_int = 200 + get_String_size(System_settings->S_Station_ID)
		+ get_String_size(System_settings->S_Route_ID) + get_String_size(System_settings->S_Station_Ord);
	sprintf(length, "%d", length_int);
	
	/*Server_Link has a endless while loop. If Server_Link didn't work correctly, program will stop. */
	Server_Link("ws.bus.go.kr");

	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	
	/* Caution! Endless loop! */
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3, "GET /api/rest/arrive/getArrInfoByRoute?ServiceKey=oKkRSmbYF6oWEeqgrxSkahZvUmDbY5AOESsWfRK87khxbjutCbvfrBcVHAJOUKP0W3ldMEEyM6Qn%2F1Dyz8zVKg%3D%3D&stId=");
	USART_String_Send(USART3, System_settings->S_Station_ID);
	USART_String_Send(USART3, "&busRouteId=");
	USART_String_Send(USART3, System_settings->S_Route_ID);
	USART_String_Send(USART3, "&ord=");
	USART_String_Send(USART3, System_settings->S_Station_Ord);
	USART_String_Send(USART3, " HTTP/1.1\r\nHost: ws.bus.go.kr\r\n\r\n");
}
void S_Bus_parsing(Struct_Info* System_info)
{
	char temp;
	short i;
	char traTime1[7];
	char traTime2[7];
	while(1)
	{
		if(USART_Receive(USART3) == '[')	{
			temp = USART_Receive(USART3);
			if(temp < 58)	System_info->arrmsg1[0] = temp;
			else	System_info->arrmsg1[0] = '.';
			temp = USART_Receive(USART3);
			if(temp < 58)	System_info->arrmsg1[1] = temp;
			break;
		}
	}
	while(1)
	{
		if(USART_Receive(USART3) == '[')	{
			temp = USART_Receive(USART3);
			if(temp < 58)	System_info->arrmsg2[0] = temp;
			else	System_info->arrmsg2[0] = '.';
			temp = USART_Receive(USART3);
			if(temp < 58)	System_info->arrmsg2[1] = temp;
			break;
		}
	}
	while(1)
	{
		if(USART_Receive(USART3) == 'r')
			if(USART_Receive(USART3) == 'a')
				if(USART_Receive(USART3) == 'T')
					if(USART_Receive(USART3) == 'i')
						if(USART_Receive(USART3) == 'm')
							if(USART_Receive(USART3) == 'e')
								if(USART_Receive(USART3) == '1')
									if(USART_Receive(USART3) == '>')	{
										i = 0;
										while(1)
										{
											temp = USART_Receive(USART3);
											if(temp != '<')	{traTime1[i] = temp;	i++;}
											else	break;
										}
										break;
									}
	}
	while(1)
	{
		if(USART_Receive(USART3) == 'r')
			if(USART_Receive(USART3) == 'a')
				if(USART_Receive(USART3) == 'T')
					if(USART_Receive(USART3) == 'i')
						if(USART_Receive(USART3) == 'm')
							if(USART_Receive(USART3) == 'e')
								if(USART_Receive(USART3) == '2')
									if(USART_Receive(USART3) == '>')	{
										i = 0;
										while(1)
										{
											temp = USART_Receive(USART3);
											if(temp != '<')	{traTime2[i] = temp; i++;}
											else	break;
										}
										break;
									}
	}
	
	short local_traTime_min = atoi(traTime1)/60;
	short local_traTime_sec = atoi(traTime1)%60;
	sprintf(System_info->traTime1_min,"%d",local_traTime_min);
	sprintf(System_info->traTime1_sec,"%d",local_traTime_sec);
	
	local_traTime_min = atoi(traTime2)/60;
	local_traTime_sec = atoi(traTime2)%60;
	sprintf(System_info->traTime2_min,"%d",local_traTime_min);
	sprintf(System_info->traTime2_sec,"%d",local_traTime_sec);
	
	USART_String_Send(USART2, "\r\nAPI : S_Bus");
	USART_String_Send(USART2, "\r\narrmsg1 : ");
	USART_String_Send(USART2, System_info->arrmsg1);
	USART_String_Send(USART2, "\r\narrmsg2 : ");
	USART_String_Send(USART2, System_info->arrmsg2);
	USART_String_Send(USART2, "\r\ntraTime1_min : ");
	USART_String_Send(USART2, System_info->traTime1_min);
	USART_String_Send(USART2, "\r\ntraTime1_sec : ");
	USART_String_Send(USART2, System_info->traTime1_sec);
	USART_String_Send(USART2, "\r\ntraTime2_min : ");
	USART_String_Send(USART2, System_info->traTime2_min);
	USART_String_Send(USART2, "\r\ntraTime2_sec : ");
	USART_String_Send(USART2, System_info->traTime2_sec);
	USART_String_Send(USART2, "\r\n\r\n");
}
