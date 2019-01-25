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


// Declare private variables
static const float sourceRanges[] = {
    NSOURCE1_RANGE,
    NSOURCE2_RANGE,
    NSOURCE3_RANGE,
    NSOURCE4_RANGE
};

static const CalibrationData_t calibrationData[] = {
    { NSOURCE1_CALIBRATION_SLOPE, NSOURCE1_CALIBRATION_OFFSET },
    { NSOURCE2_CALIBRATION_SLOPE, NSOURCE2_CALIBRATION_OFFSET },
    { NSOURCE3_CALIBRATION_SLOPE, NSOURCE3_CALIBRATION_OFFSET },
    { NSOURCE4_CALIBRATION_SLOPE, NSOURCE4_CALIBRATION_OFFSET }
};


//
HwAPI_Status_t HwAPI_VoltageSource_Set( NSource_t nSource, float value )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;
    
    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_SET;
    hwVoltageSourceQueueData.nSource = nSource;
    hwVoltageSourceQueueData.valueDAC = CalculateDAC( value * calibrationData[ nSource ].slope + calibrationData[ nSource ].offset, 
                                                      sourceRanges[ nSource ],
                                                      AD56X0_OPERATION_MODE_NORMAL );

    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_VoltageSource_Clear( NSource_t nSource )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;

    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_CLEAR;
    hwVoltageSourceQueueData.nSource = nSource;

    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL );

	return HW_API_OK;
}


//
HwAPI_Status_t HwAPI_VoltageSource_ClearAll( void )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;

    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_CLEAR_ALL;
    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL );

	return HW_API_OK;
}
/* End of file */
