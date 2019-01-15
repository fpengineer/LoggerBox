/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for DAQ Frequency

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


static const CalibrationData_t calibrationData = { FREQ_CALIBRATION_SLOPE, FREQ_CALIBRATION_OFFSET };

//
HwAPI_StatusTypeDef HwAPI_DAQ_Frequency_GetSingle( NChannelFreq_t nChannel, FreqPWMData_t *valueFreq )
{
    HwDAQ_FrequencyQueueData_t hwDAQ_FrequencyQueueData;
        
    hwDAQ_FrequencyQueueData.stateHwDAQ_Frequency = HW_DAQ_FREQUENCY_GET_SINGLE;

    xQueueSend( xQueue_HwDAQ_Frequency_Rx, &hwDAQ_FrequencyQueueData, NULL );
    xQueueReceive( xQueue_HwDAQ_Frequency_Tx, &hwDAQ_FrequencyQueueData, portMAX_DELAY );
    
    valueFreq->frequency_kHz = hwDAQ_FrequencyQueueData.freqPWMData.frequency_kHz * calibrationData.slope + calibrationData.offset;
    valueFreq->pulseHigh_ns = hwDAQ_FrequencyQueueData.freqPWMData.pulseHigh_ns;    // Need to add calibration
    valueFreq->pulseLow_ns = hwDAQ_FrequencyQueueData.freqPWMData.pulseLow_ns;      // Need to add calibration 
    
	return HW_API_OK;
}


//
HwAPI_StatusTypeDef HwAPI_DAQ_Frequency_GetAveraged( NChannelFreq_t nChannel, FreqPWMData_t *valueFreq, int32_t numberAverages )
{
    HwDAQ_FrequencyQueueData_t hwDAQ_FrequencyQueueData;
        
    hwDAQ_FrequencyQueueData.stateHwDAQ_Frequency = HW_DAQ_FREQUENCY_GET_AVERAGED;
    hwDAQ_FrequencyQueueData.numberAverages = numberAverages;
    
    xQueueSend( xQueue_HwDAQ_Frequency_Rx, &hwDAQ_FrequencyQueueData, NULL );
    xQueueReceive( xQueue_HwDAQ_Frequency_Tx, &hwDAQ_FrequencyQueueData, portMAX_DELAY );
    
    valueFreq->frequency_kHz = hwDAQ_FrequencyQueueData.freqPWMData.frequency_kHz;
    valueFreq->pulseHigh_ns = hwDAQ_FrequencyQueueData.freqPWMData.pulseHigh_ns;
    valueFreq->pulseLow_ns = hwDAQ_FrequencyQueueData.freqPWMData.pulseLow_ns;
    
	return HW_API_OK;
}
    
/* End of file */
