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

#include "TS_HwQueue.h"

#include "HwAPI.h"

#include "delay.h"


//
HwAPI_Status_t HwAPI_Relay_Set( NRelay_t nRelay )
{
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
    HwRelayQueueData_t hwRelayQueueData;

    hwRelayQueueData.stateHwRelay = HW_RELAY_CLEAR_ALL;

    xQueueSend( xQueue_HwRelay_Rx, &hwRelayQueueData, NULL );
    delay_ms( 10 );
    
    return HW_API_OK;
}


/* End of file */
