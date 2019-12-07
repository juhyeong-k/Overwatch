/**
  *******************************************************************************
	*	@file   functions_for_OVERWATCH.c
	* @date   2017.AUGUST.16
  *	@brief	This file includes functions for OVERWATCH project.
	* 				
	===============================================================================
	* @attention
	*		System_GetFlagStatus wasn't verified! Check before use.
  */

/**
	*	@brief	Checks whether the specified System flag is set or not.
	*					If some flag was set, it will return 1.
	*	@param	System_Flags are defined at settings_for_OVERWATCH.h
	*/
short System_GetFlagStatus(uint32_t System_FLAG)
{
	if((System_status & System_FLAG) != System_FLAG)	{
		return 0;
	}
	else	{
		return 1;
	}
}
void sec_to_min(char* time, int* min, int* sec)
{
	*min = atoi(time)/60;
	*sec = atoi(time)%60;
}
int get_String_size(char* String)
{
	int size = 0;
	for (short i = 0; String[i]; i++)
	{
		size++;
	}
	return size;
}
/* BCD to Decimal */
uint8_t bcd_to_decimal(uint8_t bcd)
{
	return (bcd >> 4)*10 + (bcd&0x0F);
}
/* Decimal to BCD */
uint8_t decimal_to_bcd(uint8_t decimal)
{
	return ( ((decimal/10)<<4) | (decimal%10) );
}
int bin_to_dec(uint8_t bin)
{
    int decimalNumber = 0, i = 0, remainder;
    while (bin!=0)
    {
        remainder = bin%10;
        bin /= 10;
        decimalNumber += remainder*pow(2,i);
        ++i;
    }
    return decimalNumber;
}
void MutexAcquire(osMutexId_t mutex_id)
{
	osStatus_t status;
	while(1)
	{
		osMutexAcquire(mutex_id,0);
		if(status == osOK)	break;
		osDelay(100);
	}
}
