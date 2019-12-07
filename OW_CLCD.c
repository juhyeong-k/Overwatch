//0~7 DATA, 8 RS,  9 R/W, 10 E. Command

#define RS_PIN                ((uint16_t)0x2000)  /* Pin 13 selected */
#define RW_PIN                ((uint16_t)0x4000)  /* Pin 14 selected */
#define E_PIN                 ((uint16_t)0x8000)  /* Pin 15 selected */

#define COMMAND_CLEAR_DISPLAY		0x01							//	00000001
#define COMMAND_8_BIT_MODE			0x38							//	00111000
#define COMMAND_4_BIT_MODE			0x28

#define COMMAND_DISPLAY_ON_OFF_BIT	2
#define COMMAND_CURSOR_ON_OFF_BIT	1
#define COMMAND_BLINK_ON_OFF_BIT	0

void LCD_pulse_enable(void)
{
	GPIO_SetBits(GPIOA, E_PIN);
	osDelay(3);
	GPIO_ResetBits(GPIOA, E_PIN);
	osDelay(3);
}
void LCD_write_data(uint8_t data)
{
	GPIO_SetBits(GPIOA, RS_PIN);
	GPIO_ResetBits(GPIOA, 255);
	GPIO_SetBits(GPIOA, data);
	LCD_pulse_enable();
	osDelay(3);
}
void LCD_write_command(uint8_t command)
{
	GPIO_ResetBits(GPIOA, RS_PIN);
	GPIO_ResetBits(GPIOA, 255);
	GPIO_SetBits(GPIOA, command);
	LCD_pulse_enable();
	osDelay(3);
}
void LCD_clear()
{
	LCD_write_command(COMMAND_CLEAR_DISPLAY);
	osDelay(3);
}
void LCD_init()
{
	osDelay(100);
	
	GPIO_ResetBits(GPIOA, RW_PIN);
	
	LCD_write_command(COMMAND_8_BIT_MODE);
	LCD_write_command(COMMAND_8_BIT_MODE);
	uint8_t command = 0x08 | (1 << COMMAND_DISPLAY_ON_OFF_BIT);
	LCD_write_command(command);
	
	LCD_clear();
	
	LCD_write_command(0x06);
}
void LCD_write_string(char* string)
{
	uint8_t i;
	for(i = 0; string[i]; i++)
	LCD_write_data(string[i]);
}
void LCD_goto_XY(uint8_t row, uint8_t col)
{
	col %= 16;
	row %= 2;
	
	uint8_t address = (0x40 * row) + col;
	uint8_t command = 0x80 + address;
	
	LCD_write_command(command);
}
void LCD_goto_addr(uint8_t address)
{
	uint8_t command = 0x80 + address;
	LCD_write_command(command);
}
void lcd(Struct_Time* System_time, Struct_Info* System_info, Struct_Settings* System_settings)
{
	LCD_init();
	
	LCD_goto_addr(0x00);
	LCD_write_string("20");
	LCD_write_string(System_time->Year);
	LCD_write_data('.');
	LCD_write_string(System_time->Month);
	LCD_write_data('.');
	LCD_write_string(System_time->Date);
	LCD_write_data(' ');
	LCD_write_string(System_time->Hours);
	LCD_write_data(':');
	LCD_write_string(System_time->Minutes);
	
	LCD_goto_addr(0x0F);
	LCD_write_string(System_info->T3H);
	LCD_write_data(39);
	LCD_write_data('C');
	
	LCD_goto_addr(0x40);
	LCD_write_string("Rain   ");
	LCD_write_string(System_info->POP);
	LCD_write_data('%');
	
	LCD_goto_addr(0x4F);
	LCD_write_data(42);
	LCD_write_string(System_info->PM10_grade);
	LCD_write_string("/");
	LCD_write_string(System_info->PM25_grade);
	
	LCD_goto_addr(0x14);
	LCD_write_string("Bus    ");
	if(System_settings->SG[0] == 'G')	LCD_write_string(System_info->locationNo1);
	else															LCD_write_string(System_info->arrmsg1);
	
	LCD_goto_addr(0x54);
	int local_remain = atoi(System_info->remain);
	char remain_c[4];
	sprintf(remain_c, "%d", local_remain);
	LCD_write_string("Metro  ");
	LCD_write_string(remain_c);
	
	LCD_goto_addr(0x5F);
	LCD_write_string("OVERWATCH");
}
