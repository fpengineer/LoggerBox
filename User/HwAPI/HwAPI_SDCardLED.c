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

#include "TS_HwQueue.h"

#include "HwAPI.h"


//
HwAPI_Status_t HwAPI_SDCardLED_On( void )
{
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;

    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_ON;

    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_SDCardLED_Off( void )
{
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;

    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_OFF;

    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_SDCardLED_Flash( uint16_t delay_ms )
{
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;

    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_FLASH;
    hwSDCardLEDQueueData.delay_ms = delay_ms;
    
    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL );

	return HW_API_OK;
}
/* End of file */
