/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for System Time

*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_queue.h"
#include "TS_HwQueue.h"

#include "HwAPI.h"

//
void HwAPI_SystemTime_Set( TM_RTC_Time_t datatime )
{
    HwSystemTimeQueueData_t hwSystemTimeQueueData;

    // Send to TS_HwSystemTime new time value to set
    hwSystemTimeQueueData.stateHwSystemTime = HW_SYSTEM_TIME_SET;
    hwSystemTimeQueueData.datatime = datatime;
    xQueueSend( xQueue_HwSystemTime_Rx, &hwSystemTimeQueueData, NULL );
}


//
void HwAPI_SystemTime_Get( char *timeString )
{
    HwSystemTimeQueueData_t hwSystemTimeQueueData;

    // get current system time from TS_HwSystemTime
    hwSystemTimeQueueData.stateHwSystemTime = HW_SYSTEM_TIME_GET;
    xQueueSend( xQueue_HwSystemTime_Rx, &hwSystemTimeQueueData, NULL );
    xQueueReceive( xQueue_HwSystemTime_Tx, &hwSystemTimeQueueData, portMAX_DELAY );

    // convert received system time to string
    sprintf( timeString, "%02d.%02d.%04d %02d:%02d:%02d",
                        hwSystemTimeQueueData.datatime.date,
                        hwSystemTimeQueueData.datatime.month,
                        hwSystemTimeQueueData.datatime.year + 2000,
                        hwSystemTimeQueueData.datatime.hours,
                        hwSystemTimeQueueData.datatime.minutes,
                        hwSystemTimeQueueData.datatime.seconds );
}


//
void HwAPI_SystemTime_ProcessConfig( int32_t *flagUpdateSystemTime, char *timeString )
{
//    HwFatFsQueueData_t hwFatFsQueueData;
    HwSystemTimeQueueData_t hwSystemTimeQueueData;
//    cfgSystemTime_t cfgSystemTime;
    char stringSystemTime[ 30 ] = "";
    
    // read config values for time from "config.ini" file
    // prototype HwAPI_FatFs_GetConfigKey( int keyType, char *sectionName, char *keyName, char *fileName, void *value );
    HwAPI_FatFs_GetKeyINI( INI_KEY_INT, "SystemTime", "UpdateSystemTime", "config.ini", flagUpdateSystemTime );
    HwAPI_FatFs_GetKeyINI( INI_KEY_STRING, "SystemTime", "SystemTimeString", "config.ini", stringSystemTime );


    // check system time update enable flag
    if ( *flagUpdateSystemTime == UPDATE_SYSTEM_TIME_ENABLE )
    {
        // update system time with new value
        hwSystemTimeQueueData.datatime.day = 1;
        hwSystemTimeQueueData.datatime.date = atoi( stringSystemTime );
        hwSystemTimeQueueData.datatime.month = atoi( stringSystemTime + 3 );
        hwSystemTimeQueueData.datatime.year = atoi( stringSystemTime + 6 ) - 2000;
        hwSystemTimeQueueData.datatime.hours = atoi( stringSystemTime + 10 );
        hwSystemTimeQueueData.datatime.minutes = atoi( stringSystemTime + 14 );
        hwSystemTimeQueueData.datatime.seconds = atoi( stringSystemTime + 17 );

        hwSystemTimeQueueData.stateHwSystemTime = HW_SYSTEM_TIME_SET;
        xQueueSend( xQueue_HwSystemTime_Rx, &hwSystemTimeQueueData, NULL );
        
        // disable system time enable flag in "config.ini" file
        *flagUpdateSystemTime = UPDATE_SYSTEM_TIME_DISABLE;
        HwAPI_FatFs_PutKeyINI( INI_KEY_INT, "SystemTime", "UpdateSystemTime", "config.ini", flagUpdateSystemTime );
        *flagUpdateSystemTime = UPDATE_SYSTEM_TIME_ENABLE;
    }
    else
    {
        *flagUpdateSystemTime = UPDATE_SYSTEM_TIME_DISABLE;
    }

    // get current system time from TS_HwSystemTime
    hwSystemTimeQueueData.stateHwSystemTime = HW_SYSTEM_TIME_GET;
    xQueueSend( xQueue_HwSystemTime_Rx, &hwSystemTimeQueueData, NULL );
    xQueueReceive( xQueue_HwSystemTime_Tx, &hwSystemTimeQueueData, portMAX_DELAY );

    // convert received system time to string
    sprintf( timeString, "%02d.%02d.%04d %02d:%02d:%02d",
                        hwSystemTimeQueueData.datatime.date,
                        hwSystemTimeQueueData.datatime.month,
                        hwSystemTimeQueueData.datatime.year + 2000,
                        hwSystemTimeQueueData.datatime.hours,
                        hwSystemTimeQueueData.datatime.minutes,
                        hwSystemTimeQueueData.datatime.seconds );

}




void HwAPI_SystemTime_SendToTerminal( char *timeString )
{
    
    
}



/* End of file */
