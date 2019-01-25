/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for Relay

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "HwAPI.h"

#include "delay.h"


//
HwAPI_Status_t HwAPI_Relay_Set( NRelay_t nRelay )
{
    extern QueueHandle_t xQueue_HwRelay_Rx;
    HwRelayQueueData_t hwRelayQueueData;

    hwRelayQueueData.stateHwRelay = HW_RELAY_SET;
    hwRelayQueueData.nRelay = nRelay;

    xQueueSend( xQueue_HwRelay_Rx, &hwRelayQueueData, NULL );
    delay_ms( 10 );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_Relay_Clear( NRelay_t nRelay )
{
    extern QueueHandle_t xQueue_HwRelay_Rx;
    HwRelayQueueData_t hwRelayQueueData;

    hwRelayQueueData.stateHwRelay = HW_RELAY_CLEAR;
    hwRelayQueueData.nRelay = nRelay;

    xQueueSend( xQueue_HwRelay_Rx, &hwRelayQueueData, NULL );
    delay_ms( 10 );
    
	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_Relay_ClearAll( void )
{
    extern QueueHandle_t xQueue_HwRelay_Rx;
    HwRelayQueueData_t hwRelayQueueData;

    hwRelayQueueData.stateHwRelay = HW_RELAY_CLEAR_ALL;

    xQueueSend( xQueue_HwRelay_Rx, &hwRelayQueueData, NULL );
    delay_ms( 10 );
    
    return HW_API_OK;
}

//
void HwAPI_Relay_Run( void )
{
    extern TaskHandle_t xTask_HwRelay;
    extern QueueHandle_t xQueue_HwRelay_Rx;
    
    xQueue_HwRelay_Rx = xQueueCreate( 5, sizeof( HwRelayQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwRelay,
                                "Task - HwRelay",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwRelay ) ) { /* some error action */ }	
}


//
HwAPI_BootStatus_t HwAPI_Relay_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwRelay;
    
    return bootStatus_HwRelay;
}


/* End of file */
