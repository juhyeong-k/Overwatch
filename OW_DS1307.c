/**
  *	Functions for DS1307.
  *	This file uses I2C1, PB6 and PB7.
	*	SCL on PB6 and SDA on PB7
  *	To prevent functions using I2C1 at the same time, functions must include System_Flag system.
  *
	*	@brief
	*		To Initialize by GMT information,
	*			1. GMT_request()
	*			2. GMT_parsing(&System_time)
	*			3. DS1307_Init(&System_time)
	*
  * ===============================================================================
	* @attention
  *		Check!! System_Flag system wasn't verified. Confirm before use.
	*		Time_struct was used twice.	1. GMT_parsing(write) 2. DS1307_Init(read)
	*		CIPCLOSE is really fast. Caution.
  */
void DS1307_Init(Struct_Time* System_time)
{
	while(System_GetFlagStatus(I2C_using_FLAG));
	System_status |= I2C_using_FLAG;
	
	I2C_start(I2C1, 0x68<<1, I2C_Direction_Transmitter);
	
	I2C_write(I2C1, 0);
	
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->Seconds)));
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->Minutes)));
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->Hours)));
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->WeekDay)));
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->Date)));
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->Month)));
	I2C_write(I2C1, decimal_to_bcd(atoi(System_time->Year)));
	
	I2C_stop(I2C1);
	System_status &= (~I2C_using_FLAG);
}
void DS1307_User_Init(uint8_t Seconds,uint8_t Minutes,uint8_t Hours,uint8_t WeekDay,uint8_t Date,uint8_t Month,uint8_t Year)
{
	while(System_GetFlagStatus(I2C_using_FLAG));
	System_status |= I2C_using_FLAG;
	
	uint8_t data[] = {Seconds,Minutes,Hours,WeekDay,Date,Month,Year};	// 2017.01.01 00:00:00
	
	I2C_start(I2C1, 0x68<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0);
	
	for(short i = 0; i < 7; i++)
	{
		I2C_write(I2C1, decimal_to_bcd(data[i]));
	}
	I2C_stop(I2C1);
	
	osDelay(1000);
	
	System_status &= (~I2C_using_FLAG);
}
void DS1307_Parsing(Struct_Time* System_time)
{
	I2C_start(I2C1, 0x68<<1, I2C_Direction_Transmitter);
	I2C_write(I2C1, 0);
	I2C_stop(I2C1);
	
	I2C_start(I2C1, 0x68<<1, I2C_Direction_Receiver);
	sprintf(System_time->Seconds, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	sprintf(System_time->Minutes, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	sprintf(System_time->Hours, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	sprintf(System_time->WeekDay, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	sprintf(System_time->Date, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	sprintf(System_time->Month, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	sprintf(System_time->Year, "%d", bcd_to_decimal(I2C_read_ack(I2C1)));
	I2C_stop(I2C1);

	USART_String_Send(USART2, "20");
	USART_String_Send(USART2, System_time->Year);
	USART_String_Send(USART2, ".");
	USART_String_Send(USART2, System_time->Month);
	USART_String_Send(USART2, ".");
	USART_String_Send(USART2, System_time->Date);
	USART_String_Send(USART2, " ");
	USART_String_Send(USART2, System_time->Hours);
	USART_String_Send(USART2, ":");
	USART_String_Send(USART2, System_time->Minutes);
	USART_String_Send(USART2, ":");
	USART_String_Send(USART2, System_time->Seconds);
	USART_String_Send(USART2, ", ");
	USART_String_Send(USART2, System_time->WeekDay);
	USART_String_Send(USART2, "\r\n");
}
