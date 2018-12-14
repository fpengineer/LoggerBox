/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Measure X

*******************************************************************************************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "TS_queue.h"
#include "TS_task.h"

#include "HwAPI.h"

#include "defines.h"

//static char tempString[250] = {""}; 

void vTask_MeasureX( void *pvParameters )
{
    extern QueueHandle_t xQueue_MeasureX_Rx;
    MeasureXQueueData_t measureXQueueData;

    while ( 1 )
	{
        xQueueReceive( xQueue_MeasureX_Rx, &measurePlannerQueueData, portMAX_DELAY );

        switch ( measureXQueueData.stateMeasureX )
        {
            case MEASURE_X_INIT:
                {
                    
                }
                break;
                
            case MEASURE_X_RUN:
                {
                    
                }
                break;
                
            case MEASURE_X_TACT:
                {
                    
                }
                break;
                
            case MEASURE_X_STOP:
                {
                    
                }
                break;
                
            case MEASURE_X_IDLE:
                {
                    
                }
                break;
                
            default:
                break;
                
        }
    }
}
/* End of file */
