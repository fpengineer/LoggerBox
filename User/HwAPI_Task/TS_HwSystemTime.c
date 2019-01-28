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

#include "HwAPI.h"

TaskHandle_t xTask_HwSystemTime;
QueueHandle_t xQueue_HwSystemTime_Rx;
QueueHandle_t xQueue_HwSystemTime_Tx;
volatile HwAPI_BootStatus_t bootStatus_HwSystemTime = HW_TASK_BOOT_IDLE;


//static char tempString[150] = {""}; 

void vTask_HwSystemTime( void *pvParameters )
{
    HwSystemTimeQueueData_t hwSystemTimeQueueData;

	hwSystemTimeQueueData.stateHwSystemTime = HW_SYSTEM_TIME_INIT;
    xQueueSend( xQueue_HwSystemTime_Rx, &hwSystemTimeQueueData, NULL ); 
    
    while( 1 )
	{
        xQueueReceive( xQueue_HwSystemTime_Rx, &hwSystemTimeQueueData, portMAX_DELAY );
        switch ( hwSystemTimeQueueData.stateHwSystemTime )
        {
            case HW_SYSTEM_TIME_INIT:
            {
                if ( !TM_RTC_Init( TM_RTC_ClockSource_External ) ) {
                    /* RTC was first time initialized */
                    /* Do your stuff here */
                    /* eg. set default time */
                }
                bootStatus_HwSystemTime = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_SYSTEM_TIME_SET:
            {
                TM_RTC_SetDateTime( &hwSystemTimeQueueData.datatime, TM_RTC_Format_BIN );
                break;
            }
            
            case HW_SYSTEM_TIME_GET:
            {            
                TM_RTC_GetDateTime( &hwSystemTimeQueueData.datatime, TM_RTC_Format_BIN );
                xQueueSend( xQueue_HwSystemTime_Tx, &hwSystemTimeQueueData, NULL );
                break;
            }
            
            case HW_SYSTEM_TIME_IDLE:
                break;
        
            default:
                break;
        }
	}
}

/* End of file */
