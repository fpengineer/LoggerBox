/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Measure Planner

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

void vTask_MeasurePlanner( void *pvParameters )
{
    extern QueueHandle_t xQueue_MeasurePlanner_Rx;
    MeasurePlannerQueueData_t measurePlannerQueueData;

    while ( 1 )
	{
        xQueueReceive( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, portMAX_DELAY );

        switch ( measurePlannerQueueData.stateMeasurePlanner )
        {
            case MEASURE_PLANNER_INIT:
                {
                    
                }
                break;
                
            case MEASURE_PLANNER_GET_TYPE:
                {
                    
                }
                break;
                
            case MEASURE_PLANNER_RUN_MEASURE_TASK:
                {
                    
                }
                break;
                
            case MEASURE_PLANNER_STOP_MEASURE_TASK:
                {
                    
                }
                break;
                
            case MEASURE_PLANNER_IDLE:
                {
                    
                }
                break;
                
            default:
                break;
                
        }
    }
}


void SDCardDetect_Event( SDCardDetectStatus_t sdCardDetectStatus )
{
    switch ( sdCardDetectStatus )
    {
        case SD_CARD_INSERT:
        {    
            // Run sd card insert handler
            break;
        }
    
        case SD_CARD_REMOVE:
        {
            break;
    	}
        
        default:
            break;
    }
    
}
/* End of file */
