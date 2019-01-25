/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for SD card detection

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
RunButtonStatus_t HwAPI_RunButton_GetStatus( void )
{
    extern QueueHandle_t xQueue_HwRunButton_Rx;
    extern QueueHandle_t xQueue_HwRunButton_Tx;
    HwRunButtonQueueData_t hwRunButtonQueueData;
   
    hwRunButtonQueueData.stateHwRunButton = HW_RUN_BUTTON_GET;
    
    xQueueSend( xQueue_HwRunButton_Rx, &hwRunButtonQueueData, NULL );
    xQueueReceive( xQueue_HwRunButton_Tx, &hwRunButtonQueueData, portMAX_DELAY );

    return hwRunButtonQueueData.runButtonStatus;
}


//
void HwAPI_RunButton_Run( void )
{
    extern TaskHandle_t xTask_HwRunButton;
    extern QueueHandle_t xQueue_HwRunButton_Rx;
    extern QueueHandle_t xQueue_HwRunButton_Tx;
    
    xQueue_HwRunButton_Rx = xQueueCreate( 5, sizeof( HwRunButtonQueueData_t ) );
    xQueue_HwRunButton_Tx = xQueueCreate( 5, sizeof( HwRunButtonQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwRunButton,
                                "Task - HwRunButton",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwRunButton ) ) { /* some error action */ }	
}


//
HwAPI_BootStatus_t HwAPI_RunButton_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwRunButton;
    
    return bootStatus_HwRunButton;
}


/* End of file */
