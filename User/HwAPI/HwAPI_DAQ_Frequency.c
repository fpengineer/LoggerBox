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

#include "HwAPI.h"


static const CalibrationData_t calibrationData = { FREQ_CALIBRATION_SLOPE, FREQ_CALIBRATION_OFFSET };

//
HwAPI_Status_t HwAPI_DAQ_Frequency_GetSingle( NChannelFreq_t nChannel, FreqPWMData_t *valueFreq )
{
    extern QueueHandle_t xQueue_HwDAQ_Frequency_Rx;
    extern QueueHandle_t xQueue_HwDAQ_Frequency_Tx;
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
HwAPI_Status_t HwAPI_DAQ_Frequency_GetAveraged( NChannelFreq_t nChannel, FreqPWMData_t *valueFreq, int32_t numberAverages )
{
    extern QueueHandle_t xQueue_HwDAQ_Frequency_Rx;
    extern QueueHandle_t xQueue_HwDAQ_Frequency_Tx;
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
    

//
HwAPI_BootStatus_t HwAPI_DAQ_Frequency_Run( void )
{
    extern TaskHandle_t xTask_HwDAQ_Frequency;
    extern QueueHandle_t xQueue_HwDAQ_Frequency_Rx;
    extern QueueHandle_t xQueue_HwDAQ_Frequency_Tx;
    extern HwAPI_BootStatus_t bootStatus_HwDAQ_Frequency;
    
    xQueue_HwDAQ_Frequency_Rx = xQueueCreate( 5, sizeof( HwDAQ_FrequencyQueueData_t ) );
    xQueue_HwDAQ_Frequency_Tx = xQueueCreate( 5, sizeof( HwDAQ_FrequencyQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwDAQ_Frequency,
                                "Task - HwDAQ_Frequency",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwDAQ_Frequency ) ) { /* some error action */ }	

    while ( bootStatus_HwDAQ_Frequency == HW_TASK_BOOT_IDLE ){;}
    
    if ( bootStatus_HwDAQ_Frequency == HW_TASK_BOOT_PENDING )
    {
        bootStatus_HwDAQ_Frequency = HW_TASK_BOOT_RUN;
    }
    
    return bootStatus_HwDAQ_Frequency;
}

/* End of file */
