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
SDCardDetectStatus_t HwAPI_SDCardDetect_GetStatus( void )
{
    HwSDCardDetectQueueData_t hwSDCardDetectQueueData;
   
    hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_GET;
    
    xQueueSend( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL );
    xQueueReceive( xQueue_HwSDCardDetect_Tx, &hwSDCardDetectQueueData, portMAX_DELAY );

    return 	hwSDCardDetectQueueData.sdCardDetectStatus;
}
/* End of file */
