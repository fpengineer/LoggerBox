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

#include "TS_HwQueue.h"

#include "HwAPI.h"


//
RunButtonStatus_t HwAPI_RunButton_GetStatus( void )
{
    HwRunButtonQueueData_t hwRunButtonQueueData;
   
    hwRunButtonQueueData.stateHwRunButton = HW_RUN_BUTTON_GET;
    
    xQueueSend( xQueue_HwRunButton_Rx, &hwRunButtonQueueData, NULL );
    xQueueReceive( xQueue_HwRunButton_Tx, &hwRunButtonQueueData, portMAX_DELAY );

    return hwRunButtonQueueData.runButtonStatus;
}
/* End of file */
