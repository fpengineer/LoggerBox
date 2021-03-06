/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Set System Time

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_rtc.h"
#include "Config.h"
#include "SystemTime.h"

#include "TS_queue.h"

static char tempString[150] = {""}; 

void vTask_SystemTime( void *pvParameters )
{
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_SystemTimeIn;
    extern QueueHandle_t xQueue_SystemTimeOut;
    SystemTimeQueueData_t SystemTimeQueueData;
    TM_RTC_Time_t datatime;    

	if (!TM_RTC_Init(TM_RTC_ClockSource_External)) {
		/* RTC was first time initialized */
		/* Do your stuff here */
		/* eg. set default time */

	}

    TM_RTC_GetDateTime(&datatime, TM_RTC_Format_BIN);
    sprintf(tempString, "Current system time - %02d.%02d.%02d %02d:%02d:%02d\r\n",
                        datatime.date,
                        datatime.month,
                        datatime.year,
                        datatime.hours,
                        datatime.minutes,
                        datatime.seconds);
    xQueueSend( xQueue_Terminal, &tempString, NULL );

	while( 1 )
	{
        xQueueReceive( xQueue_SystemTimeIn, &SystemTimeQueueData, portMAX_DELAY );
        switch (SystemTimeQueueData.stateSystemTime)
        {
            case SYSTEM_TIME_SET:
                TM_RTC_SetDateTime(&SystemTimeQueueData.datatime, TM_RTC_Format_BIN);
                break;
        
            case SYSTEM_TIME_GET:
                TM_RTC_GetDateTime(&SystemTimeQueueData.datatime, TM_RTC_Format_BIN);
                xQueueSend( xQueue_SystemTimeOut, &SystemTimeQueueData, NULL );
                break;
        
            default:
                break;
        }
	}
}

/* End of file */
