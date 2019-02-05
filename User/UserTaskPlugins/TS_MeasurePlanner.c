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

typedef enum {
    MEASURE_STOP,
    MEASURE_RUN
} MeasureStatus_t;

// Declare private functions

// Declare private variables
//static char tempString[450] = {""}; 
static MeasureStatus_t measureStatus = MEASURE_STOP;
    
void vTask_MeasurePlanner( void *pvParameters )
{
    extern QueueHandle_t xQueue_MeasurePlanner_Rx;
    MeasurePlannerQueueData_t measurePlannerQueueData;

    HwBootData_t hwBootData = { HW_BOOT_IDLE, "" };
    
    while ( 1 )
	{
        xQueueReceive( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, portMAX_DELAY );

        switch ( measurePlannerQueueData.stateMeasurePlanner )
        {
            case MEASURE_PLANNER_INIT:
            {
                while ( hwBootData.hwBootStatus == HW_BOOT_IN_PROGRESS ||
                        hwBootData.hwBootStatus == HW_BOOT_IDLE )
                {
                    hwBootData = HwAPI_Boot_GetStatus();
                }
                    
                if ( hwBootData.hwBootStatus == HW_BOOT_SUCCESS )
                {
                    // Start measure plugin loader
                }
                else
                {
                    // Error!
                    // Hardware boot failed
                }
                break;
            }
                
            case MEASURE_PLANNER_GET_TYPE:
            {
                  
                break;
            }
                
            case MEASURE_PLANNER_RUN_MEASURE_TASK:
            {
                    
                break;
            }
                
            case MEASURE_PLANNER_STOP_MEASURE_TASK:
            {
                    
                break;
            }
                
            case MEASURE_PLANNER_IDLE:
            {
                    
                break;
            }
                
            default:
                break;
        }
    }
}


// SD card event callback
void SDCardDetect_Event( SDCardDetectStatus_t sdCardDetectStatus )
{
    switch ( sdCardDetectStatus )
    {
        case SD_CARD_INSERT:
        {    
            // Get configuration info
            // Load measure plugin
            break;
        }
    
        case SD_CARD_REMOVE:
        {
            // Stop measure if it is already run
            // Unload measure plugin
            // Set system to defaul state
            break;
    	}
        
        default:
            break;
    }
    
}


// Run button event callback
void RunButton_Event( RunButtonStatus_t runButtonStatus )
{
    switch ( runButtonStatus )
    {
        case MEASURE_STOP:
        {    
            // Send run command to measure plugin
            break;
        }
    
        case MEASURE_RUN:
        {
            // Send stop command to measure plugin
            // Set system to default state
            break;
    	}
        
        default:
            break;
    }
    
}
/* End of file */
