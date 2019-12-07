
//write delay!!!!!!!
//When program initializing
void EEPROM_Write(char* str)
{	
	//Write
	I2C_Write(I2C1, ADDR_24LC02, 0, str, sizeof(str));
}
//When program running
void EEPROM_Read(Struct_Settings* System_settings)
{
	int i =0;
	char buffer[200];
	I2C_Read(I2C1, ADDR_24LC02, 0, buffer, sizeof(buffer));
	char* result;
	result = strtok(buffer,"/");
	while(result != NULL)
	{
		switch(i)
		{
			case	0		:	sprintf(System_settings->SSID,"%s",result);					USART_String_Send(USART2, result);	break;
			case	1		:	sprintf(System_settings->PASSWORD,"%s",result);			USART_String_Send(USART2, result);	break;
			case	2		:	sprintf(System_settings->A_Station_NM,"%s",result);	USART_String_Send(USART2, result);	break;
			case	3		:	sprintf(System_settings->nx,"%s",result);						USART_String_Send(USART2, result);	break;
			case	4		:	sprintf(System_settings->ny,"%s",result);						USART_String_Send(USART2, result);	break;
			case	5		:	sprintf(System_settings->G_Station_ID,"%s",result);	USART_String_Send(USART2, result);	break;
			case	6		:	sprintf(System_settings->G_Route_ID,"%s",result);		USART_String_Send(USART2, result);	break;
			case	7		:	sprintf(System_settings->S_arsId,"%s",result);			USART_String_Send(USART2, result);	break;
			case	8		:	sprintf(System_settings->rtNm,"%s",result);					USART_String_Send(USART2, result);	break;
			case	9		:	sprintf(System_settings->S_Station_ID,"%s",result);	USART_String_Send(USART2, result);	break;
			case	10	:	sprintf(System_settings->S_Route_ID,"%s",result);		USART_String_Send(USART2, result);	break;
			case	11	:	sprintf(System_settings->M_Station_NM,"%s",result);	USART_String_Send(USART2, result);	break;
			case	12	:	sprintf(System_settings->M_subwayId,"%s",result);		USART_String_Send(USART2, result);	break;
			case	13	:	sprintf(System_settings->M_updnLine,"%s",result);		USART_String_Send(USART2, result);	break;
			case	14	:	sprintf(System_settings->SG,"%s",result);						USART_String_Send(USART2, result);	break;
			default 	:	break;
		}
		i++;
		result = strtok(NULL,"/");
		if(i == 15)	break;
	}
	USART_String_Send(USART2, "!!\r\n");
}
void EEPROM_Reset()
{
	I2C_start(I2C1, 0xA0, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0);
	I2C_write(I2C1, 0x01);
	for(int i =0; i < 180; i++)
	{
		I2C_write(I2C1, 0);
	}
	I2C_stop(I2C1);
	I2C_AcknowledgePolling(I2C1,0xA0);
	osDelay(1000);
}

/*
//write
	char temp[4];
	
	I2C_start(I2C1, 0xA0, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0);
	I2C_write(I2C1, 0x01);
	I2C_write(I2C1, 'H');
	I2C_write(I2C1, 'i');
	I2C_write(I2C1, '!');
	I2C_stop(I2C1);
	I2C_AcknowledgePolling(I2C1,0xA0);
	I2C_delay(1000);


	//read
	I2C_start(I2C1, 0xA0, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0);
	I2C_write(I2C1, 0x01);
	I2C_stop(I2C1);
	
	I2C_start(I2C1, 0xA0, I2C_Direction_Receiver);
	temp[0] = I2C_read_ack(I2C1);
	temp[1] = I2C_read_ack(I2C1);
	temp[2] = I2C_read_ack(I2C1);
	I2C_stop(I2C1);
	USART_String_Send(USART2, temp);
	*/

