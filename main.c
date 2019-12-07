/*----------------------------------------------------------------------------
 * CMSIS-RTOS 'main' function template
 *---------------------------------------------------------------------------*/
 /*	
  *	thread 선언을 app_main 바깥에서 해보자
	* app_main 마지막을 비워두지 말자
	* 메모리 관련 고민도 해보자
	*/
#include "RTE_Components.h"
#include  CMSIS_device_header
#include "cmsis_os2.h"
#include "string.h"

#ifdef RTE_Compiler_EventRecorder
#include "EventRecorder.h"
#endif
char local_SG;
osMutexId_t System_status_using;
osMutexId_t System_info_using;
osMutexId_t System_time_using;
osMutexId_t System_Wifi_using;
static uint32_t System_status;
#include <OW_settings.h>
static Struct_Time			System_time;
static Struct_Settings	System_settings;
static Struct_Info 			System_info;
#include <OW_Init.c>

const osMutexAttr_t Thread_Mutex_attr = {
  "myThreadMutex1",     // human readable mutex name
  osMutexRobust,       // attr_bits
  NULL,                // memory for control block   
  NULL                 // size for control block
};
const osThreadAttr_t app_main_attr = {
  .priority = osPriorityRealtime1           //Set initial thread priority to high   
};
/*----------------------------------------------------------------------------
 * Application main thread
 *---------------------------------------------------------------------------*/
void time_sync(void *argument)	{
	while(1)
	{
		osMutexAcquire(System_time_using,osWaitForever);
		DS1307_Parsing(&System_time);
		osMutexRelease(System_time_using);
		
		osDelay(5000);
		lcd(&System_time, &System_info, &System_settings);
	}
}
void Air(void *argument)	{
	Air_Id = osThreadGetId();
	while(1)
	{
		osMutexAcquire(System_Wifi_using,osWaitForever);
		AT_CIPCLOSE();
		osDelay(3000);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status |= Air_FLAG;
		osMutexRelease(System_status_using);
		
		Air_request(&System_settings);
		Air_parsing(&System_info);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status &= (~Air_FLAG);
		osMutexRelease(System_status_using);
		
		osDelay(4000);
		
		osMutexRelease(System_Wifi_using);
		osDelay(60000);
	}
}
void Forecast(void *argument) {
	Forecast_Id = osThreadGetId();
	while(1)
	{
		osMutexAcquire(System_Wifi_using,osWaitForever);
		AT_CIPCLOSE();
		osDelay(3000);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status |= Forecast_FLAG;
		osMutexRelease(System_status_using);
		
		osMutexAcquire(System_time_using,osWaitForever);
		Forecast_request(&System_time, &System_settings);
		Forecast_parsing(&System_info);
		osMutexRelease(System_time_using);
			
		osMutexAcquire(System_status_using,osWaitForever);
		System_status &= (~Forecast_FLAG);
		osMutexRelease(System_status_using);
		
		osDelay(4000);
		
		osMutexRelease(System_Wifi_using);
		osDelay(60000);
	}
}
void G_Bus(void *argument) {
	G_Bus_Id = osThreadGetId();
	while(1)
	{
		osMutexAcquire(System_Wifi_using,osWaitForever);
		AT_CIPCLOSE();
		osDelay(3000);
		
		osMutexAcquire(System_status_using,osWaitForever);		
		System_status |= G_Bus_FLAG;
		osMutexRelease(System_status_using);
		
		osMutexAcquire(System_info_using,osWaitForever);
		G_Bus_request(&System_settings);
		G_Bus_parsing(&System_info);
		osMutexRelease(System_info_using);
			
		osMutexAcquire(System_status_using,osWaitForever);
		System_status &= (~G_Bus_FLAG);
		osMutexRelease(System_status_using);
		
		osDelay(4000);
		osMutexRelease(System_Wifi_using);
	}
}
void S_Bus(void *argument) {
	S_Bus_Id = osThreadGetId();
	while(1)
	{
		osMutexAcquire(System_Wifi_using,osWaitForever);
		AT_CIPCLOSE();
		osDelay(3000);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status |= S_Bus_FLAG;
		osMutexRelease(System_status_using);
		
		osMutexAcquire(System_info_using,osWaitForever);
		S_Bus_request(&System_settings);
		S_Bus_parsing(&System_info);
		osMutexRelease(System_info_using);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status &= (~S_Bus_FLAG);
		osMutexRelease(System_status_using);
		osDelay(4000);
		osMutexRelease(System_Wifi_using);
	}
}
void S_Metro(void *argument)	{
	S_Metro_Id = osThreadGetId();
	while(1)
	{
		osMutexAcquire(System_Wifi_using,osWaitForever);
		AT_CIPCLOSE();
		osDelay(3000);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status |= S_Metro_FLAG;
		osMutexRelease(System_status_using);
		
		osMutexAcquire(System_info_using,osWaitForever);
		S_Metro_request(&System_settings);
		S_Metro_parsing(&System_settings, &System_info);
		osMutexRelease(System_info_using);
		
		osMutexAcquire(System_status_using,osWaitForever);
		System_status &= (~S_Metro_FLAG);
		osMutexRelease(System_status_using);
		
		osDelay(4000);
		osMutexRelease(System_Wifi_using);
	}
}
void app_main(void *argument)	{
	
	osThreadNew(Air, NULL, &app_main_attr);
	osThreadNew(Forecast, NULL, &app_main_attr);
	if(local_SG == 'G')	osThreadNew(G_Bus, NULL, &app_main_attr);
	else 								osThreadNew(S_Bus, NULL, &app_main_attr);
	osThreadNew(S_Metro, NULL, &app_main_attr);
	osThreadId_t id;
	osStatus_t status;
  id = osThreadGetId();
	osThreadSetPriority (id, osPriorityRealtime2);
	while(1)
	{
		/* Air */
		osMutexAcquire(System_status_using,osWaitForever);
		if(System_GetFlagStatus(Air_FLAG))	{
			osMutexRelease(System_status_using);
			osDelay(8000);
			osMutexAcquire(System_status_using,osWaitForever);
			if(System_GetFlagStatus(Air_FLAG))	{
				System_status &= (~Air_FLAG);
				osMutexRelease(System_status_using);
				USART_String_Send(USART2,"\r\nWARNING! Air function has a problem.... \r\nWARNING! Program reboot.\r\n\r\n");
				osThreadTerminate(Air_Id);
				WIFI_destroyer();
				AT_CIPCLOSE();
				Air_Id = NULL_Id;
				osThreadNew(Air, NULL, &app_main_attr);
			}
			else	osMutexRelease(System_status_using);
		}
		else	osMutexRelease(System_status_using);
		/* Forecast */
		osMutexAcquire(System_status_using,osWaitForever);
		if(System_GetFlagStatus(Forecast_FLAG))	{
			osMutexRelease(System_status_using);
			osDelay(8000);
			osMutexAcquire(System_status_using,osWaitForever);
			if(System_GetFlagStatus(Forecast_FLAG))	{
				System_status &= (~Forecast_FLAG);
				osMutexRelease(System_status_using);
				USART_String_Send(USART2,"\r\nWARNING! Forecast function has a problem.... \r\nWARNING! Program reboot.\r\n\r\n");
				osThreadTerminate(Forecast_Id);
				WIFI_destroyer();
				AT_CIPCLOSE();
				Forecast_Id = NULL_Id;
				osThreadNew(Forecast, NULL, &app_main_attr);
			}
			else	osMutexRelease(System_status_using);
		}
		else	osMutexRelease(System_status_using);
		/* G_Bus */
		osMutexAcquire(System_status_using,osWaitForever);
		if(System_GetFlagStatus(G_Bus_FLAG))	{
			osMutexRelease(System_status_using);
			osDelay(8000);
			osMutexAcquire(System_status_using,osWaitForever);
			if(System_GetFlagStatus(G_Bus_FLAG))	{
				System_status &= (~G_Bus_FLAG);
				osMutexRelease(System_status_using);
				USART_String_Send(USART2,"\r\nWARNING! G_Bus function has a problem.... \r\nWARNING! Program reboot.\r\n\r\n");
				osThreadTerminate(G_Bus_Id);
				WIFI_destroyer();
				AT_CIPCLOSE();
				G_Bus_Id = NULL_Id;
				osThreadNew(G_Bus, NULL, &app_main_attr);
				}
			else	osMutexRelease(System_status_using);
		}
		else	osMutexRelease(System_status_using);
		/* S_Bus */
		osMutexAcquire(System_status_using,osWaitForever);
		if(System_GetFlagStatus(S_Bus_FLAG))	{
			osMutexRelease(System_status_using);
			osDelay(8000);
			osMutexAcquire(System_status_using,osWaitForever);
			if(System_GetFlagStatus(S_Bus_FLAG))	{
				System_status &= (~S_Bus_FLAG);
				osMutexRelease(System_status_using);
				USART_String_Send(USART2,"\r\nWARNING! S_Bus function has a problem.... \r\nWARNING! Program reboot.\r\n\r\n");
				osThreadTerminate(S_Bus_Id);
				WIFI_destroyer();
				AT_CIPCLOSE();
				S_Bus_Id = NULL_Id;
				osThreadNew(S_Bus, NULL, &app_main_attr);
			}
			else	osMutexRelease(System_status_using);
		}
		else	osMutexRelease(System_status_using);
		/* S_Metro */
		osMutexAcquire(System_status_using,osWaitForever);
		if(System_GetFlagStatus(S_Metro_FLAG))	{
			osMutexRelease(System_status_using);
			osDelay(8000);
			osMutexAcquire(System_status_using,osWaitForever);
			if(System_GetFlagStatus(S_Metro_FLAG))	{
				System_status &= (~S_Metro_FLAG);
				osMutexRelease(System_status_using);
				USART_String_Send(USART2,"\r\nWARNING! S_Metro function has a problem.... \r\nWARNING! Program reboot.\r\n\r\n");
				osThreadTerminate(S_Metro_Id);
				WIFI_destroyer();
				AT_CIPCLOSE();
				S_Metro_Id = NULL_Id;
				osThreadNew(S_Metro, NULL, &app_main_attr);
			}
			else	osMutexRelease(System_status_using);
		}
		else	osMutexRelease(System_status_using);
		Display(&System_info, &System_time);
		osDelay(5000);
	}
}
int main (void) {
 
  // System Initialization
  SystemCoreClockUpdate();
#ifdef RTE_Compiler_EventRecorder
  // Initialize and start Event Recorder
  EventRecorderInitialize(EventRecordError, 1U);
#endif
	
	GPIO_Settings_for_OVERWATCH();
	I2C1_Settings_for_OVERWATCH();
	
	char buffer[200];
	char readbuffer[200];

	USART_String_Send(USART2, "\r\n+++++System start!+++++\r\n");
	
	if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3))
	{
		Bluetooth_settings_receive(buffer);
		I2C_Write(I2C1, ADDR_24LC02, 0, buffer, sizeof(buffer));
		I2C_Read(I2C1, ADDR_24LC02, 0, readbuffer, sizeof(readbuffer));
	}

	EEPROM_Read(&System_settings);
	
	local_SG = System_settings.SG[0];
	//OW_Init(&System_settings);
	Wifi_init(&System_settings);
	S_Station_Ord_getter(&System_settings);
	AT_CIPCLOSE();
	while(1)
	{
		if(USART_Receive(USART3) == 'n')
			if(USART_Receive(USART3) == 'k')			break;
	}
	GMT_request();
	GMT_parsing(&System_time);
	AT_CIPCLOSE();
	while(1)
	{
		if(USART_Receive(USART3) == 'n')
			if(USART_Receive(USART3) == 'k')			break;
	}
	DS1307_Init(&System_time);
	
	osKernelInitialize();                 // Initialize CMSIS-RTOS
	
	System_status_using = osMutexNew(&Thread_Mutex_attr);
	System_info_using = osMutexNew(&Thread_Mutex_attr);
	System_time_using = osMutexNew(&Thread_Mutex_attr);
	System_Wifi_using = osMutexNew(&Thread_Mutex_attr);
	
	osThreadNew(app_main, NULL, NULL);
	osThreadNew(time_sync, NULL, &app_main_attr);
	
  osKernelStart();                      // Start thread execution
  for (;;) {}
}
