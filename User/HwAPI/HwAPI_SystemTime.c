/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for System Time

*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_queue.h"

#include "HwAPI.h"

void HwAPI_SystemTime_Get( TM_RTC_Time_t *datatime )
{
    extern QueueHandle_t xQueue_HwSystemTime_Rx;
    extern QueueHandle_t xQueue_HwSystemTime_Tx;
    HwSystemTimeQueueData_t HwSystemTimeQueueData;

    HwSystemTimeQueueData.stateHwSystemTime = HW_SYSTEM_TIME_GET;
    xQueueSend( xQueue_HwSystemTime_Rx, &HwSystemTimeQueueData, NULL );
    xQueueReceive( xQueue_HwSystemTime_Tx, &HwSystemTimeQueueData, portMAX_DELAY );

    *datatime = HwSystemTimeQueueData.datatime;
}



/* End of file */
