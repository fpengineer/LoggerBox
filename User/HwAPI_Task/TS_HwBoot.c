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
    HwBootStatus_t hwBootStatus_Terminal = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_SystemTime = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_StatusLED = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_SDCardLED = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_FatFs = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_SDCardDetect = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_Relay = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_VoltageSource = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_DAQ_ADC = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_DAQ_Frequency = HW_BOOT_IDLE;
    HwBootStatus_t hwBootStatus_RunButton = HW_BOOT_IDLE;

    hwBootData.hwBootStatus = HW_BOOT_IN_PROGRESS;
    
#if 1
    // run hardware tasks
    if ( HwAPI_Terminal_Run() == HW_TASK_BOOT_RUN )
    {
        hwBootStatus_Terminal = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
        sprintf( tempString, "HwTerminal task run - free mem: %d B\n", xPortGetFreeHeapSize() );
        HwAPI_Terminal_SendMessage( tempString );
#endif
       
#if 1   // HwSystemTime
//        vTaskDelay(500);
        if ( HwAPI_SystemTime_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_SystemTime = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwSystemTime task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_SystemTime = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwSystemTime task boot error\n" );
#endif
        }
#endif
#if 1   // HwStatusLED
//        vTaskDelay(500);
        if ( HwAPI_StatusLED_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_StatusLED = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwStatusLED task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_StatusLED = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwStatusLED task boot error\n" );
#endif
        }
#endif
#if 1   // HwSDCardLED
//        vTaskDelay(500);
        if ( HwAPI_SDCardLED_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_SDCardLED = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwSDCardLED task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_SDCardLED = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwSDCardLED task boot error\n" );
#endif
        }
#endif
#if 1   // HwFatFs
//        vTaskDelay(500);
        if ( HwAPI_FatFs_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_FatFs = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwFatFs task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_FatFs = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwFatFs task boot error\n" );
#endif
        }
#endif
#if 1   // HwSDCardDetect
//        vTaskDelay(500);
        if ( HwAPI_SDCardDetect_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_SDCardDetect = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwSDCardDetect task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_SDCardDetect = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task boot error\n" );
#endif
        }
#endif
#if 1   // HwRelay
//        vTaskDelay(500);
        if ( HwAPI_Relay_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_Relay = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwRelay task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_Relay = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwRelay task boot error\n" );
#endif
        }
#endif
#if 1   // HwVoltageSource
//        vTaskDelay(500);
        if ( HwAPI_VoltageSource_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_VoltageSource = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwVoltageSource task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_VoltageSource = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwVoltageSource task boot error\n" );
#endif
        }
#endif
#if 1   // HwDAQ_ADC
//        vTaskDelay(500);
        if ( HwAPI_DAQ_ADC_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_DAQ_ADC = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwDAQ_ADC task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_DAQ_ADC = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task boot error\n" );
#endif
        }
#endif
#if 1   // HwDAQ_Frequency
//        vTaskDelay(500);
        if ( HwAPI_DAQ_Frequency_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_DAQ_Frequency = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwDAQ_Frequency task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_DAQ_Frequency = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task boot error\n" );
#endif
        }
#endif
#if 1   // HwRunButton
//        vTaskDelay(500);
        if ( HwAPI_RunButton_Run() == HW_TASK_BOOT_RUN )
        {
            hwBootStatus_RunButton = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
            sprintf( tempString, "HwRunButton task run - free mem: %dB\n", xPortGetFreeHeapSize() );
            HwAPI_Terminal_SendMessage( tempString );
#endif
        }
        else
        {
            hwBootStatus_RunButton = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "HwRunButton task boot error\n" );
#endif
        }
#endif
    }
    else
    {
        hwBootStatus_Terminal = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
        HwAPI_Terminal_SendMessage( "HwTerminal task boot error\n" );
#endif
    }
#endif
    
    if ( hwBootStatus_Terminal == HW_BOOT_SUCCESS &&
         hwBootStatus_SystemTime == HW_BOOT_SUCCESS &&
         hwBootStatus_StatusLED == HW_BOOT_SUCCESS &&
         hwBootStatus_SDCardLED == HW_BOOT_SUCCESS &&
         hwBootStatus_FatFs == HW_BOOT_SUCCESS &&
         hwBootStatus_SDCardDetect == HW_BOOT_SUCCESS &&
         hwBootStatus_Relay == HW_BOOT_SUCCESS &&
         hwBootStatus_VoltageSource == HW_BOOT_SUCCESS &&
         hwBootStatus_DAQ_ADC == HW_BOOT_SUCCESS &&
         hwBootStatus_DAQ_Frequency == HW_BOOT_SUCCESS &&
         hwBootStatus_RunButton == HW_BOOT_SUCCESS )
    {
        hwBootData.hwBootStatus = HW_BOOT_SUCCESS;
#ifdef HWAPI_BOOT_DEBUG_INFO
        HwAPI_Terminal_SendMessage( "HwBoot task complete\n" );
#endif
    }
    else if ( hwBootStatus_Terminal == HW_BOOT_ERROR ||
              hwBootStatus_SystemTime == HW_BOOT_ERROR ||
              hwBootStatus_StatusLED == HW_BOOT_ERROR ||
              hwBootStatus_SDCardLED == HW_BOOT_ERROR ||
              hwBootStatus_FatFs == HW_BOOT_ERROR ||
              hwBootStatus_SDCardDetect == HW_BOOT_ERROR ||
              hwBootStatus_Relay == HW_BOOT_ERROR ||
              hwBootStatus_VoltageSource == HW_BOOT_ERROR ||
              hwBootStatus_DAQ_ADC == HW_BOOT_ERROR ||
              hwBootStatus_DAQ_Frequency == HW_BOOT_ERROR ||
              hwBootStatus_RunButton == HW_BOOT_ERROR )
    {
        hwBootData.hwBootStatus = HW_BOOT_ERROR;
#ifdef HWAPI_BOOT_DEBUG_INFO
        HwAPI_Terminal_SendMessage( "HwBoot task result: HW_BOOT_ERROR\n" );
#endif
    }
    else
    {
        hwBootData.hwBootStatus = HW_BOOT_IDLE;
#ifdef HWAPI_BOOT_DEBUG_INFO
        HwAPI_Terminal_SendMessage( "HwBoot tast result: HW_BOOT_IDLE \n" );
#endif
    }

    while ( 1 )
    {

    }
}
/* End of file */
