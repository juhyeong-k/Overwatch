/**
  ******************************************************************************
  * @file			OW_G_Bus.c
  * @author		Gachon Univ. TEAM TAKEOUT. Juhyeong Kim.
  * @version	V1.0.0
  * @date			12-July-2017
  * @brief		GMT_request();
	*						wait_CIPCLOSE();
	*
  ===============================================================================
	*	@attention
	*		
  */
void GMT_request()
{
	Server_Link("www.google.com");
	USART_String_Send(USART3, "AT+CIPSEND=7\r\n");
	while(1)
	{
		if(USART_Receive(USART3) == '>')	break;
	}
	USART_String_Send(USART3, "GET\r\n\r\n");
}
//Date: \Fri, 18 Aug 2017 15:11:45 GMT
void GMT_parsing(Struct_Time* System_time)
{
	char time_string[25];
	while(1)
	{
		if(USART_Receive(USART3) == 'D')
			if(USART_Receive(USART3) == 'a')
				if(USART_Receive(USART3) == 't')
					if(USART_Receive(USART3) == 'e')
					{
						USART_Receive(USART3);
						USART_Receive(USART3);
						for(short i = 0; i < 26; i++)
						{
							time_string[i] = USART_Receive(USART3);
						}
						break;
					}
	}
	
	//Parsing WeekDay
	switch(time_string[1])
	{
		case 117 : if(time_string[2] == 'n')			{*System_time->WeekDay = '0';	break;}
							else if(time_string[2] == 'e')	{*System_time->WeekDay = '2';	break;}
							else														{*System_time->WeekDay = '9';	break;}
		case 111 : *System_time->WeekDay = '1';	break;
		case 101 : *System_time->WeekDay = '3';	break;
		case 104 : *System_time->WeekDay = '4';	break;
		case 114 : *System_time->WeekDay = '5';	break;
		case 97 : *System_time->WeekDay = '6';	break;
		default : *System_time->WeekDay = '9';	break;
	}
	
	//Parsing Date
	System_time->Date[0] = time_string[5];
	System_time->Date[1] = time_string[6];
	
	//Parsing Month
	switch(time_string[10])
	{
		case 110 : if(time_string[9] == 'a')			{*System_time->WeekDay = '1';	break;}
							 else if(time_string[9] == 'u')	{*System_time->WeekDay = '6';	break;}
							 else														{sprintf(System_time->Month, "%d", 13);	break;}
		case 98 : *System_time->Month = '2';	break;
		case 114 : if(time_string[9] == 'a')			{*System_time->WeekDay = '3';	break;}
							 else if(time_string[9] == 'p')	{*System_time->WeekDay = '4';	break;}
							 else														{sprintf(System_time->Month, "%d", 13);	break;}
		case 121 : *System_time->Month = '5';	break;
		case 108 : *System_time->Month = '7';	break;
		case 103 : sprintf(System_time->Month, "%d", 8);	break;
		case 112 : sprintf(System_time->Month, "%d", 9);	break;
		case 116 : sprintf(System_time->Month, "%d", 10);	break;
		case 118 : sprintf(System_time->Month, "%d", 11);	break;
		case 99 : sprintf(System_time->Month, "%d", 12);	break;
		default : sprintf(System_time->Month, "%d", 13);	break;
	}
	//Parsing Year
	System_time->Year[0] = time_string[14];
	System_time->Year[1] = time_string[15];
	//Parsing Hour
	System_time->Hours[0] = time_string[17];
	System_time->Hours[1] = time_string[18];
	//Parsing Minutes
	System_time->Minutes[0] = time_string[20];
	System_time->Minutes[1] = time_string[21];
	//Parsing Seconds
	System_time->Seconds[0] = time_string[23];
	System_time->Seconds[1] = time_string[24];
	if(atoi(System_time->Hours)<15) sprintf(System_time->Hours, "%d", atoi(System_time->Hours)+9);
	//Date: \Fri, 18 Aug 2017 15:11:45 GMT
	else
	{
		sprintf(System_time->Hours, "%d", atoi(System_time->Hours)-15);
		
		if(*System_time->WeekDay == 54)	*System_time->WeekDay = '0';
		else	*System_time->WeekDay += 1;
		
		short month_flag;
		switch(atoi(System_time->Month))
		{
			case 1 : month_flag = 1; break;
			case 2 : month_flag = 3; break;
			case 3 : month_flag = 1; break;
			case 4 : month_flag = 2; break;
			case 5 : month_flag = 1; break;
			case 6 : month_flag = 2; break;
			case 7 : month_flag = 1; break;
			case 8 : month_flag = 1; break;
			case 9 : month_flag = 2; break;
			case 10 : month_flag = 1; break;
			case 11 : month_flag = 2; break;
			case 12 : month_flag = 0; break;
			default : month_flag = 4; break;
		}
		if(month_flag == 0)
		{
			if(atoi(System_time->Date) == 31)	
			{
				*System_time->Date = '0';
				sprintf(System_time->Date, "%d", atoi(System_time->Date) + 1);
			}
			else	sprintf(System_time->Year, "%d", atoi(System_time->Year) + 1);
		}
		if(month_flag == 1)
		{
			if(atoi(System_time->Date) == 31)	*System_time->Date = '0';
			else	sprintf(System_time->Date, "%d", atoi(System_time->Date) + 1);
		}
		else if(month_flag == 2)
		{
			if(atoi(System_time->Date) == 30)	*System_time->Date = '0';
			else	sprintf(System_time->Date, "%d", atoi(System_time->Date) + 1);
		}
		else if(month_flag == 3)
		{
			if(atoi(System_time->Date) == 28)	*System_time->Date = '0';
			else	sprintf(System_time->Date, "%d", atoi(System_time->Date) + 1);
		}
		else;
	}
	while(1)
	{
		if(USART_Receive(USART3)=='<')
			if(USART_Receive(USART3)=='/')
				if(USART_Receive(USART3)=='H')
					if(USART_Receive(USART3)=='T')
						if(USART_Receive(USART3)=='M')
							if(USART_Receive(USART3)=='L')
								if(USART_Receive(USART3)=='>')	break;
	}
	USART_String_Send(USART2, "\r\nAPI : GMT");
	USART_String_Send(USART2, "\r\nSeconds : ");
	USART_String_Send(USART2, System_time->Seconds);
	USART_String_Send(USART2, "\r\nMinutes : ");
	USART_String_Send(USART2, System_time->Minutes);
	USART_String_Send(USART2, "\r\nHours : ");
	USART_String_Send(USART2, System_time->Hours);
	USART_String_Send(USART2, "\r\nWeekDay : ");
	USART_String_Send(USART2, System_time->WeekDay);
	USART_String_Send(USART2, "\r\nDate : ");
	USART_String_Send(USART2, System_time->Date);
	USART_String_Send(USART2, "\r\nMonth : ");
	USART_String_Send(USART2, System_time->Month);
	USART_String_Send(USART2, "\r\nYear : ");
	USART_String_Send(USART2, System_time->Year);
	USART_String_Send(USART2, "\r\n\r\n");
}
