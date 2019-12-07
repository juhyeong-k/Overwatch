/**
  ******************************************************************************
  * @file    OW_settings.h
  * @author  Juhyeong Kim, Gachon University.
  * @version V1.0.0
  * @date    20-August-2017
  * @brief   Flag defines and System structs for OVERWATCH project.
	*					 Define System_Flags. 
	*					 It will be use for "System_GetFlagStatus(uint8_t System_FLAG)" function in the OW_functions.c
  ******************************************************************************  
  * @attention
  *
  */
#define Air_function_use												(uint8_t)0x01
#define Forecast_function_use										(uint8_t)0x02
#define G_Bus_function_use											(uint8_t)0x04
#define	S_Bus_function_use											(uint8_t)0x08
#define	S_Metro_function_use										(uint8_t)0x10

#define I2C_using_FLAG                   	    	(uint32_t)0x02
#define Time_struct_using_FLAG            	   	(uint32_t)0x04
#define WIFI_using_FLAG													(uint32_t)0x08
#define AT_RST_FLAG															(uint32_t)0x10
#define AT_CWMODE_FLAG													(uint32_t)0x20
#define AP_Link_FLAG														(uint32_t)0x40
#define Air_FLAG																(uint32_t)0x80
#define Forecast_FLAG														(uint32_t)0x100
#define G_Bus_FLAG															(uint32_t)0x200
#define S_Bus_FLAG															(uint32_t)0x400
#define S_Metro_FLAG														(uint32_t)0x800

/** @attention
	*		Before use System_settings, check the size of members.
	*/
/*System_settings*/
typedef struct
{
	/*Function select*/
	
	
	/*Wifi*/
	char SSID[14];
	char PASSWORD[12];
	
	/*Forecast*/
	char nx[4];
	char ny[4];
	
	/*S_Metro*/
	char M_Station_NM[30];	//utf8 인코딩
	char M_subwayId[5];				//i.e 2호선 1002
	char M_updnLine[2];
	
	/*S_Bus*/
	char S_arsId[7];
	char rtNm[6];
	char S_Station_ID[10];
	char S_Route_ID[10];
	char S_Station_Ord[5];
	
	/*G_Bus*/
	char G_Station_ID[10];
	char G_Route_ID[10];
	
	/*A_Station_NM*/
	char A_Station_NM[30];
	
	/*SG*/
	char SG[2];
}Struct_Settings;

 /*	System_time*/
typedef struct
{
	uint8_t Seconds[3];
	uint8_t Minutes[3];
	uint8_t Hours[3];
	uint8_t WeekDay[2];
	uint8_t Date[3];
	uint8_t Month[3];
	uint8_t Year[3];
}Struct_Time;

 /*	System_info*/
typedef struct
{
 /*	Air	*/
	char PM10_grade[2];
	char PM25_grade[2];
	
 /*	Forecast
	*	POP : rainfall probability. %
	*	PTY : precipitation form. none 0 / rain 1 / rain and snow 2 / snow 3 
	*	SKY : Sky condition. clear 1 / slightly covered 2 / cloudy 3 / very cloudy 4
	* T3H : 3 hours temperature.
	*/
	char POP[3];
	char PTY[2];
	char SKY[2];
	char T3H[4];
	
 /*	G_Bus
	*	locationNo1  : location information of first bus. (A few stops before)
	*	locationNo2  : location information of second bus.(A few stops before)
	*	predictTime1 : Estimated time of first arrival
	*	predictTime2 : Estimated time of second arrival
	*/
	char locationNo1[3];
	char locationNo2[3];
	char predictTime1[3];
	char predictTime2[3];
	
 /*	S_Bus
	*	arrmsg1  : location information of first bus. (A few stops before)
	*	arrmsg2  : location information of second bus.(A few stops before)
	*	traTime1 : Estimated time of first arrival
	*	traTime2 : Estimated time of second arrival	
	*/
	char arrmsg1[3];
	char arrmsg2[3];
	char traTime1_min[3];
	char traTime1_sec[3];
	char traTime2_min[3];
	char traTime2_sec[3];
	
 /* S_Metro
	*	barvlDt		:	Estimated time of first arrival (seconds)
	*/
	char remain[4];
	char barvlDt[4];
}Struct_Info;

#include <OW_functions.c>
#include <OW_UART_fuctions.c>
#include <OW_settings.c>
#include <OW_Wifi_control.c>
#include <OW_I2C_functions.c>
#include <OW_DS1307.c>
#include <OW_GMT.c>
#include <OW_Forecast.c>
#include <OW_S_Metro.c>
#include <OW_S_Bus.c>
#include <OW_G_Bus.c>
#include <OW_Air.c>
#include <OW_Interface.c>
#include <24C02.c>
#include <OW_AT24C256.c>
#include <OW_Display.c>
#include <OW_Bluetooth.c>
#include <OW_CLCD.c>

osThreadId_t NULL_Id;
osThreadId_t Air_Id;
osThreadId_t Forecast_Id;
osThreadId_t G_Bus_Id;
osThreadId_t S_Bus_Id;
osThreadId_t S_Metro_Id;
static osThreadId_t time_sync_Id;
