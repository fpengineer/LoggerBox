/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for Voltage Source

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
#include "AD56x0.h"


static const float sourceRanges[] = {
    NSOURCE1_RANGE,
    NSOURCE2_RANGE,
    NSOURCE3_RANGE,
    NSOURCE4_RANGE
};


//
HwAPI_StatusTypeDef HwAPI_VoltageSource_Set( NSource_t nSource, float value )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;

    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_SET;
    hwVoltageSourceQueueData.nSource = nSource;
    hwVoltageSourceQueueData.valueDAC = CalculateDAC( value, 
                                                      sourceRanges[ nSource ],
                                                      AD56X0_OPERATION_MODE_NORMAL );

    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_StatusTypeDef HwAPI_VoltageSource_Clear( NSource_t nSource )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;

    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_CLEAR;
    hwVoltageSourceQueueData.nSource = nSource;

    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_StatusTypeDef HwAPI_VoltageSource_ClearAll( void )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;

    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_CLEAR_ALL;
    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL );

	return HW_API_OK;
}
/* End of file */