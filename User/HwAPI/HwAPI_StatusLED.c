/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for Status LED

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
HwAPI_Status_t HwAPI_StatusLED_On( void )
{
    extern QueueHandle_t xQueue_HwStatusLED_Rx;
    HwStatusLEDQueueData_t hwStatusLEDQueueData;

    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_ON;

    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_StatusLED_Off( void )
{
    extern QueueHandle_t xQueue_HwStatusLED_Rx;
    HwStatusLEDQueueData_t hwStatusLEDQueueData;

    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_OFF;

    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_StatusLED_Flash( uint16_t delay_ms )
{
    extern QueueHandle_t xQueue_HwStatusLED_Rx;
    HwStatusLEDQueueData_t hwStatusLEDQueueData;

    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_FLASH;
    hwStatusLEDQueueData.delay_ms = delay_ms;
    
    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL );

	return HW_API_OK;
}


//
void HwAPI_StatusLED_Run( void )
{
    extern TaskHandle_t xTask_HwStatusLED;
    extern QueueHandle_t xQueue_HwStatusLED_Rx;
    
    xQueue_HwStatusLED_Rx = xQueueCreate( 5, sizeof( HwStatusLEDQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwStatusLED,
                                "Task - HwStatusLED",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwStatusLED ) ) { /* some error action */ }	
}


//
HwAPI_BootStatus_t HwAPI_StatusLED_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwStatusLED;
    
    return bootStatus_HwStatusLED;
}


/* End of file */
