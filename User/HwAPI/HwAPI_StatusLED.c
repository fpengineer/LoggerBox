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

#include "TS_HwQueue.h"

#include "HwAPI.h"


//
HwAPI_StatusTypeDef HwAPI_StatusLED_On( void )
{
    HwStatusLEDQueueData_t hwStatusLEDQueueData;

    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_ON;

    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_StatusTypeDef HwAPI_StatusLED_Off( void )
{
    HwStatusLEDQueueData_t hwStatusLEDQueueData;

    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_OFF;

    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_StatusTypeDef HwAPI_StatusLED_Flash( uint16_t delay_ms )
{
    HwStatusLEDQueueData_t hwStatusLEDQueueData;

    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_FLASH;
    hwStatusLEDQueueData.delay_ms = delay_ms;
    
    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL );

	return HW_API_OK;
}
/* End of file */
