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
SDCardDetectStatus_t HwAPI_SDCardDetect_GetStatus( void )
{
    extern QueueHandle_t xQueue_HwSDCardDetect_Rx;
    extern QueueHandle_t xQueue_HwSDCardDetect_Tx;
    HwSDCardDetectQueueData_t hwSDCardDetectQueueData;
   
    hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_GET;
    
    xQueueSend( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL );
    xQueueReceive( xQueue_HwSDCardDetect_Tx, &hwSDCardDetectQueueData, portMAX_DELAY );

    return 	hwSDCardDetectQueueData.sdCardDetectStatus;
}

//
HwAPI_BootStatus_t HwAPI_SDCardDetect_Run( void )
{
    extern TaskHandle_t xTask_HwSDCardDetect;
    extern QueueHandle_t xQueue_HwSDCardDetect_Rx;
    extern QueueHandle_t xQueue_HwSDCardDetect_Tx;
    extern HwAPI_BootStatus_t bootStatus_HwSDCardDetect;
    
    xQueue_HwSDCardDetect_Rx = xQueueCreate( 5, sizeof( HwSDCardDetectQueueData_t ) );
    xQueue_HwSDCardDetect_Tx = xQueueCreate( 5, sizeof( HwSDCardDetectQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwSDCardDetect,
                                "Task - HwSDCardDetect",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSDCardDetect ) ) { /* some error action */ }	

    while ( bootStatus_HwSDCardDetect == HW_TASK_BOOT_IDLE ){;}
    
    if ( bootStatus_HwSDCardDetect == HW_TASK_BOOT_PENDING )
    {
        bootStatus_HwSDCardDetect = HW_TASK_BOOT_RUN;
    }
    
    return bootStatus_HwSDCardDetect;
}


//
HwAPI_BootStatus_t HwAPI_SDCardDetect_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwSDCardDetect;
    
    return bootStatus_HwSDCardDetect;
}



/* End of file */
