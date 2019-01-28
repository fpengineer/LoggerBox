/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for SD card LED

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "HwAPI.h"


//
HwAPI_Status_t HwAPI_SDCardLED_On( void )
{
    extern QueueHandle_t xQueue_HwSDCardLED_Rx;
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;

    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_ON;

    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_SDCardLED_Off( void )
{
    extern QueueHandle_t xQueue_HwSDCardLED_Rx;
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;

    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_OFF;

    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_SDCardLED_Flash( uint16_t delay_ms )
{
    extern QueueHandle_t xQueue_HwSDCardLED_Rx;
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;

    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_FLASH;
    hwSDCardLEDQueueData.delay_ms = delay_ms;
    
    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_BootStatus_t HwAPI_SDCardLED_Run( void )
{
    extern TaskHandle_t xTask_HwSDCardLED;
    extern QueueHandle_t xQueue_HwSDCardLED_Rx;
    extern volatile HwAPI_BootStatus_t bootStatus_HwSDCardLED;
    
    xQueue_HwSDCardLED_Rx = xQueueCreate( 5, sizeof( HwSDCardLEDQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwSDCardLED,
                                "Task - HwSDCardLED",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSDCardLED ) ) { /* some error action */ }	

    while ( bootStatus_HwSDCardLED == HW_TASK_BOOT_IDLE ){;}
    
    if ( bootStatus_HwSDCardLED == HW_TASK_BOOT_PENDING )
    {
        bootStatus_HwSDCardLED = HW_TASK_BOOT_RUN;
    }
    
    return bootStatus_HwSDCardLED;
}

/* End of file */
