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




// Declare private functions

// Declare private variables
static char tempString[ 100 ] = {""};

void vTask_HwBoot( void *pvParameters )
{
//int32_t i = 0;
    #if 1
    // run hardware tasks
    if ( HwAPI_Terminal_Run() == HW_TASK_BOOT_RUN )
    {
        HwAPI_Terminal_SendMessage( "HwTerminal task run\n" );

        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
        
#if 0   // HwSystemTime
//        vTaskDelay(500);
        if ( HwAPI_SystemTime_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwSystemTime task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwSystemTime task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwStatusLED
//        vTaskDelay(500);
        if ( HwAPI_StatusLED_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwStatusLED task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwStatusLED task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwSDCardLED
//        vTaskDelay(500);
        if ( HwAPI_SDCardLED_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwSDCardLED task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwSDCardLED task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwFatFs
//        vTaskDelay(500);
        if ( HwAPI_FatFs_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwFatFs task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwFatFs task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );

/*
        for ( i = 0; i < 10; i++ )
        {
            sprintf( tempString, "message %d\n", i );
            HwAPI_Terminal_SendMessage( tempString );
        }
*/
#endif
#if 0
        // HwSDCardDetect
//        vTaskDelay(500);
        if ( HwAPI_SDCardDetect_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
//TM_DISCO_LedOn( LED_GREEN );
#endif
#if 0   // HwRelay
//        vTaskDelay(500);
        if ( HwAPI_Relay_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwRelay task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwRelay task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwVoltageSource
//        vTaskDelay(500);
        if ( HwAPI_VoltageSource_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwVoltageSource task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwVoltageSource task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwDAQ_ADC
//        vTaskDelay(500);
        if ( HwAPI_DAQ_ADC_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwDAQ_Frequency
//        vTaskDelay(500);
        if ( HwAPI_DAQ_Frequency_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
#if 0   // HwRunButton
//        vTaskDelay(500);
        if ( HwAPI_RunButton_Run() == HW_TASK_BOOT_RUN )
        {
            HwAPI_Terminal_SendMessage( "HwRunButton task run\n" );
        }
        else
        {
            HwAPI_Terminal_SendMessage( "HwRunButton task boot error\n" );
        }
        sprintf( tempString, "free mem: %dB\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
/*        
        // Strictly follow boot sequence!!!

        if ( HwAPI_SystemTime_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_StatusLED_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_SDCardLED_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_FatFs_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_SDCardDetect_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_Relay_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_VoltageSource_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_DAQ_ADC_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_DAQ_Frequency_Run() == HW_TASK_BOOT_RUN &&
             HwAPI_RunButton_Run() == HW_TASK_BOOT_RUN )
        {
#if 1       // MeasurePlanner
            if( pdTRUE != xTaskCreate(  vTask_MeasurePlanner,
                                        "Task - Measure Planner",
                                        configMINIMAL_STACK_SIZE,
                                        NULL,
                                        tskIDLE_PRIORITY + 1,
                                        &xTask_MeasurePlanner )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
                                
            HwAPI_Terminal_SendMessage( "***********   LoggerBox   UF113.887   " SYSTEM_VERSION "   ***********\n" );
        }
*/

    }
    else
    {
        HwAPI_Terminal_SendMessage( "HwTerminal task boot error\n" );
    }
#endif


    while ( 1 )
    {

    }
}
/* End of file */
