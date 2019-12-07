/**
  *	Functions for Forecast API.
  *
	*	@brief
	*		SecndSrtpdFrcstInfoService2/ForecastSpaceData	동네예보조회
	*
	*		Forecast_request(&System_time, &System_settings);
	*		Forecast_parsing(&System_info);
	*		wait_response_end();
	*		AT_CIPCLOSE();
  * ===============================================================================
	* @attention
  *		Before using, use DS1307_Parsing(&System_time) function.
	*		Maybe base_time is not accurate. About 10 minutes. Refer to Forecast file for details.
	*		base_date is not accurate. Before 02:00, base_time must be -1.
	*		base_month doesn't have "0"
	*		Forecast_parsing function use 3 endless loop.
  */
void Forecast_request(Struct_Time* System_time, Struct_Settings* System_settings)
{
	char length[5];
	char base_time[5];
	char year[5];
	char month[3];
	char date[3];
	
	sprintf(year,"%s%s","20",System_time->Year);
	sprintf(month,"%s",System_time->Month);
	sprintf(date,"%s",System_time->Date);
	if(atoi(month) < 10)	sprintf(month,"%c%c",'0',month[0]);
	if(atoi(date) < 10)	sprintf(date,"%c%c",'0',date[0]);
	switch((atoi(System_time->Hours)+1)/3)
	{
		case 0 : sprintf(base_time, "%s", "2300");	break;
		case 1 : sprintf(base_time, "%s", "0200");	break;
		case 2 : sprintf(base_time, "%s", "0500");	break;
		case 3 : sprintf(base_time, "%s", "0800");	break;
		case 4 : sprintf(base_time, "%s", "1100");	break;
		case 5 : sprintf(base_time, "%s", "1400");	break;
		case 6 : sprintf(base_time, "%s", "1700");	break;
		case 7 : sprintf(base_time, "%s", "2000");	break;
		case 8 : sprintf(base_time, "%s", "2300");	break;
		default : sprintf(base_time, "%s", "0200");	break;
	}
	int length_int = 244 + get_String_size(System_settings->nx) + get_String_size(System_settings->ny);
	sprintf(length, "%d", length_int);
	
	/*Server_Link has a endless while loop. If Server_Link didn't work correctly, program will stop. */
	Server_Link("newsky2.kma.go.kr");
	USART_String_Send(USART3, "AT+CIPSEND=");
	USART_String_Send(USART3, length);
	USART_String_Send(USART3, "\r\n");
	/* Caution! Endless loop! */
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3, "GET /service/SecndSrtpdFrcstInfoService2/ForecastSpaceData?ServiceKey=oKkRSmbYF6oWEeqgrxSkahZvUmDbY5AOESsWfRK87khxbjutCbvfrBcVHAJOUKP0W3ldMEEyM6Qn%2F1Dyz8zVKg%3D%3D&base_date=");
	USART_String_Send(USART3, year);
	USART_String_Send(USART3, month);
	USART_String_Send(USART3, date);
	USART_String_Send(USART3, "&base_time=");
	USART_String_Send(USART3, base_time);
	USART_String_Send(USART3, "&nx=");
	USART_String_Send(USART3, System_settings->nx);
	USART_String_Send(USART3, "&ny=");
	USART_String_Send(USART3, System_settings->ny);
	USART_String_Send(USART3, " HTTP/1.1\r\nHost: newsky2.kma.go.kr\r\n\r\n");
}
void Forecast_parsing(Struct_Info* System_info)
{
	char temp;
	while(1)
	{
		if(USART_Receive(USART3) == 'P')	{
			if(USART_Receive(USART3) == 'O')
				if(USART_Receive(USART3) == 'P')	{
					while(1)
					{
						if(USART_Receive(USART3) == 'f')
							if(USART_Receive(USART3) == 'c')
								if(USART_Receive(USART3) == 's')
									if(USART_Receive(USART3) == 't')
										if(USART_Receive(USART3) == 'V')
											if(USART_Receive(USART3) == 'a')
												if(USART_Receive(USART3) == 'l')
													if(USART_Receive(USART3) == 'u')
														if(USART_Receive(USART3) == 'e')
															if(USART_Receive(USART3) == '>')	{
																temp = USART_Receive(USART3);
																if(temp != '<')	System_info->POP[0] = temp;
																temp = USART_Receive(USART3);
																if(temp != '<')	System_info->POP[1] = temp;
																break;
															}
					}
				break;
				}
			}
		}
	while(1)
	{
		if(USART_Receive(USART3) == 'P')	{
			if(USART_Receive(USART3) == 'T')
				if(USART_Receive(USART3) == 'Y')	{
					while(1)
					{
						if(USART_Receive(USART3) == 'f')
							if(USART_Receive(USART3) == 'c')
								if(USART_Receive(USART3) == 's')
									if(USART_Receive(USART3) == 't')
										if(USART_Receive(USART3) == 'V')
											if(USART_Receive(USART3) == 'a')
												if(USART_Receive(USART3) == 'l')
													if(USART_Receive(USART3) == 'u')
														if(USART_Receive(USART3) == 'e')
															if(USART_Receive(USART3) == '>')
															{
																*System_info->PTY = USART_Receive(USART3);
																break;
															}
					}
				break;
			 }
		}
	}
	while(1)
	{
		if(USART_Receive(USART3) == 'S')	{
			if(USART_Receive(USART3) == 'K')
				if(USART_Receive(USART3) == 'Y')	{
					while(1)
					{
						if(USART_Receive(USART3) == 'f')
							if(USART_Receive(USART3) == 'c')
								if(USART_Receive(USART3) == 's')
									if(USART_Receive(USART3) == 't')
										if(USART_Receive(USART3) == 'V')
											if(USART_Receive(USART3) == 'a')
												if(USART_Receive(USART3) == 'l')
													if(USART_Receive(USART3) == 'u')
														if(USART_Receive(USART3) == 'e')
															if(USART_Receive(USART3) == '>')
															{
																*System_info->SKY = USART_Receive(USART3);
																break;
															}
					}
				break;
			 }
		}
	}
	while(1)
	{
		if(USART_Receive(USART3) == 'T')	{
			if(USART_Receive(USART3) == '3')
				if(USART_Receive(USART3) == 'H')	{
					while(1)
					{
						if(USART_Receive(USART3) == 'f')
							if(USART_Receive(USART3) == 'c')
								if(USART_Receive(USART3) == 's')
									if(USART_Receive(USART3) == 't')
										if(USART_Receive(USART3) == 'V')
											if(USART_Receive(USART3) == 'a')
												if(USART_Receive(USART3) == 'l')
													if(USART_Receive(USART3) == 'u')
														if(USART_Receive(USART3) == 'e')
															if(USART_Receive(USART3) == '>')
															{
																temp = USART_Receive(USART3);
																if(temp != '<')	System_info->T3H[0] = temp;
																temp = USART_Receive(USART3);
																if(temp != '<')	System_info->T3H[1] = temp;
																temp = USART_Receive(USART3);
																if(temp != '<')	System_info->T3H[2] = temp;
																break;
															}
					}
				break;
			 }
		}
	}
	USART_String_Send(USART2, "\r\nAPI : Forecast");
	USART_String_Send(USART2, "\r\nPOP : ");
	USART_String_Send(USART2, System_info->POP);
	USART_String_Send(USART2, "\r\nPTY : ");
	USART_Send(USART2, *System_info->PTY);
	USART_String_Send(USART2, "\r\nSKY : ");
	USART_Send(USART2, *System_info->SKY);
	USART_String_Send(USART2, "\r\nT3H : ");
	USART_String_Send(USART2, System_info->T3H);
	USART_String_Send(USART2, "\r\n\r\n");
}
