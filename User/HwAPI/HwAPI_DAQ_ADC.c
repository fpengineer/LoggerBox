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
#include "AD747x.h"


//static NChannelADC_t nChannelBuffer = ADC_CHANNEL_1;
static NSourceADC_t nSourceBuffer = ADC_SOURCE_1;

static const CalibrationData_t calibrationData[] = {
    { SRC1_CALIBRATION_SLOPE, SRC1_CALIBRATION_OFFSET },
    { SRC2_CALIBRATION_SLOPE, SRC2_CALIBRATION_OFFSET },
    { SRC3_CALIBRATION_SLOPE, SRC3_CALIBRATION_OFFSET },
    { SRC4_CALIBRATION_SLOPE, SRC4_CALIBRATION_OFFSET },
    { SRC5_CALIBRATION_SLOPE, SRC5_CALIBRATION_OFFSET },
    { SRC6_CALIBRATION_SLOPE, SRC6_CALIBRATION_OFFSET },
    { SRC7_CALIBRATION_SLOPE, SRC7_CALIBRATION_OFFSET },
    { SRC8_CALIBRATION_SLOPE, SRC8_CALIBRATION_OFFSET }
};
   

// This function should be called earlier than HwAPI_DAQ_ADC_GetSingle and HwAPI_DAQ_ADC_GetAveraged
HwAPI_Status_t HwAPI_DAQ_ADC_SelectInput( NChannelADC_t nChannel, NSourceADC_t nSource )
{
    extern QueueHandle_t xQueue_HwDAQ_ADC_Rx;
    HwDAQ_ADCQueueData_t hwDAQ_ADCQueueData;
        
    hwDAQ_ADCQueueData.stateHwDAQ_ADC = HW_DAQ_ADC_SELECT_INPUT;
    hwDAQ_ADCQueueData.nChannelADC = nChannel;
    hwDAQ_ADCQueueData.nSourceADC = nSource;
//    nChannelBuffer = nChannel;
    nSourceBuffer = nSource;

    xQueueSend( xQueue_HwDAQ_ADC_Rx, &hwDAQ_ADCQueueData, NULL );
    vTaskDelay( 5 );
    
	return HW_API_OK;
}

//
HwAPI_Status_t HwAPI_DAQ_ADC_GetSingle( float *valueADC, float range )
{
    extern QueueHandle_t xQueue_HwDAQ_ADC_Rx;
    extern QueueHandle_t xQueue_HwDAQ_ADC_Tx;
    HwDAQ_ADCQueueData_t hwDAQ_ADCQueueData;
        
    hwDAQ_ADCQueueData.stateHwDAQ_ADC = HW_DAQ_ADC_GET_SINGLE;

    xQueueSend( xQueue_HwDAQ_ADC_Rx, &hwDAQ_ADCQueueData, NULL );
    xQueueReceive( xQueue_HwDAQ_ADC_Tx, &hwDAQ_ADCQueueData, portMAX_DELAY );
    
    *valueADC = CalculateADC_AD747x( hwDAQ_ADCQueueData.valueADC, range ) * calibrationData[ nSourceBuffer ].slope + calibrationData[ nSourceBuffer ].offset;

	return HW_API_OK;
}

//
HwAPI_Status_t HwAPI_DAQ_ADC_GetAveraged( float *valueADC, float range, int32_t numberAverages )
{
    extern QueueHandle_t xQueue_HwDAQ_ADC_Rx;
    extern QueueHandle_t xQueue_HwDAQ_ADC_Tx;
    HwDAQ_ADCQueueData_t hwDAQ_ADCQueueData;
        
    hwDAQ_ADCQueueData.stateHwDAQ_ADC = HW_DAQ_ADC_GET_AVERAGED;
    hwDAQ_ADCQueueData.numberAverages = numberAverages;

    xQueueSend( xQueue_HwDAQ_ADC_Rx, &hwDAQ_ADCQueueData, NULL );
    xQueueReceive( xQueue_HwDAQ_ADC_Tx, &hwDAQ_ADCQueueData, portMAX_DELAY );
    
    *valueADC = CalculateADC_AD747x( hwDAQ_ADCQueueData.valueADC, range ) * calibrationData[ nSourceBuffer ].slope + calibrationData[ nSourceBuffer ].offset;
    
	return HW_API_OK;
}

//
void HwAPI_DAQ_ADC_Run( void )
{
    extern TaskHandle_t xTask_HwDAQ_ADC;
    extern QueueHandle_t xQueue_HwDAQ_ADC_Rx;
    extern QueueHandle_t xQueue_HwDAQ_ADC_Tx;
    
    xQueue_HwDAQ_ADC_Rx = xQueueCreate( 5, sizeof( HwDAQ_ADCQueueData_t ) );
    xQueue_HwDAQ_ADC_Tx = xQueueCreate( 5, sizeof( HwDAQ_ADCQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwDAQ_ADC,
                                "Task - HwDAQ_ADC",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwDAQ_ADC ) ) { /* some error action */ }	
}


//
HwAPI_BootStatus_t HwAPI_DAQ_ADC_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwDAQ_ADC;
    
    return bootStatus_HwDAQ_ADC;
}


/* End of file */
