/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw to boot for all enabled hardware modules

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "tm_stm32f4_disco.h"

#include "HwAPI.h"

#include "delay.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

HwBootData_t hwBootData = { HW_BOOT_IDLE, "" }; 


// Declare private functions

// Declare private variables
static char tempString[ 100 ] = {""};

void vTask_HwBoot( void *pvParameters )
{
#if 1
    // run hardware tasks
    if ( HwAPI_Terminal_Run() == HW_TASK_BOOT_RUN )
    {
        hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
        HwAPI_Terminal_SendMessage( "HwTerminal task run\n" );
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
        
#if 0   // HwSystemTime
//        vTaskDelay(500);
        if ( HwAPI_SystemTime_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwSystemTime task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwSystemTime task boot error\n" );
        }
#endif
#if 0   // HwStatusLED
//        vTaskDelay(500);
        if ( HwAPI_StatusLED_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwStatusLED task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwStatusLED task boot error\n" );
        }
#endif
#if 0   // HwSDCardLED
//        vTaskDelay(500);
        if ( HwAPI_SDCardLED_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwSDCardLED task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwSDCardLED task boot error\n" );
        }
#endif
#if 0   // HwFatFs
//        vTaskDelay(500);
        if ( HwAPI_FatFs_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwFatFs task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwFatFs task boot error\n" );
        }
#endif
#if 0   // HwSDCardDetect
//        vTaskDelay(500);
        if ( HwAPI_SDCardDetect_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task boot error\n" );
        }
#endif
#if 0   // HwRelay
//        vTaskDelay(500);
        if ( HwAPI_Relay_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwRelay task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwRelay task boot error\n" );
        }
#endif
#if 0   // HwVoltageSource
//        vTaskDelay(500);
        if ( HwAPI_VoltageSource_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwVoltageSource task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwVoltageSource task boot error\n" );
        }
#endif
#if 0   // HwDAQ_ADC
//        vTaskDelay(500);
        if ( HwAPI_DAQ_ADC_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task boot error\n" );
        }
#endif
#if 0   // HwDAQ_Frequency
//        vTaskDelay(500);
        if ( HwAPI_DAQ_Frequency_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task boot error\n" );
        }
#endif
#if 1   // HwRunButton
//        vTaskDelay(500);
        if ( HwAPI_RunButton_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootData.hwBootStatus = HW_BOOT_SUCCESS;
            HwAPI_Terminal_SendMessage( "HwRunButton task run\n" );
            sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
            HwAPI_Terminal_SendMessage( "***********   LoggerBox   UF113.887   " SYSTEM_VERSION "   ***********\n" );
        }
        else
        {
            hwBootData.hwBootStatus = HW_BOOT_ERROR;
            HwAPI_Terminal_SendMessage( "HwRunButton task boot error\n" );
        }
    }
    else
    {
        hwBootData.hwBootStatus = HW_BOOT_ERROR;
        HwAPI_Terminal_SendMessage( "HwTerminal task boot error\n" );
    }
#endif
#endif

    while ( 1 )
    {

    }
}
/* End of file */
