void Bluetooth_settings_receive(char* str)
{
	char temp;
	short i = 0;
	while(1)
	{
		temp = USART_Receive(UART5);
		if(temp != '.')	str[i] = temp;
		else						break;
		i++;
	}
}
