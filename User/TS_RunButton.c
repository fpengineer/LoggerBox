/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - RunButton

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_task.h"
#include "TS_queue.h"

//#include "stm32f4xx.h"
//#include "defines.h"
//#include "tm_stm32f4_gpio.h"

#include "EXT_Signal.h"

enum measureState {RUN_MODE, STOP_MODE}; 

void vTask_RunButton( void *pvParameters )
{
    extern QueueHandle_t xQueue_Terminal;
    extern volatile uint32_t runButtonFlag;
    extern QueueHandle_t xQueue_MainMeasure;
    MainMeasureQueueData_t mainMeasureQueueData = {MEASURE_STOP};
    enum measureState measureState = STOP_MODE; 
    extern uint32_t measureEnableFlag;
    
    InitRunButton();

	while (1)
	{
        while(!runButtonFlag)
        {
            vTaskDelay(50);
        }
        
//        xQueueSend( xQueue_Terminal, "Run button pressed\r\n", NULL );

        switch((int32_t)measureState)
        {
            case STOP_MODE:
                mainMeasureQueueData.stateMainMeasure = MEASURE_RUN;
                xQueueReset(xQueue_MainMeasure);
                xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                vTaskDelay(1200);
                if (measureEnableFlag)
                {
                    measureState = RUN_MODE; 
                }
                break;

            case RUN_MODE:
                measureState = STOP_MODE; 
                mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                xQueueReset(xQueue_MainMeasure);
                xQueueSendToFront( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                break;
            
            default:
                break;
        }

        vTaskDelay(200);
        runButtonFlag = 0;
    }
}


/* End of file */
