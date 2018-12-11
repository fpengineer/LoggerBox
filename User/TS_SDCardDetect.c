/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - SD card detect

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


void vTask_SDCardDetect( void *pvParameters )
{
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_FatFsIn;
    extern QueueHandle_t xQueue_MainMeasure;
    FatFsQueueData_t FatFsQueueData;
    MainMeasureQueueData_t mainMeasureQueueData = {MEASURE_STOP};
    extern volatile uint32_t cardInsertState;
    uint32_t prev_cardInsertState = 0;

    InitSDCardDetect();
    if (cardInsertState)
    {
        FatFsQueueData.stateFatFs = FATFS_INIT_SD_CARD;
        xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL );
        xQueueSend( xQueue_Terminal, "SD Card detected!\r\n", NULL );
    }
    else
    {
        xQueueSend( xQueue_Terminal, "SD Card not found!\r\n", NULL );
        xQueueSend( xQueue_Terminal, "Please insert SD Card.\r\n", NULL );
    }
    prev_cardInsertState = cardInsertState;

	while (1)
	{
        if (cardInsertState)
        {
            if (!prev_cardInsertState)
            {
                prev_cardInsertState = cardInsertState;
                FatFsQueueData.stateFatFs = FATFS_INIT_SD_CARD;
                xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL );
                xQueueSend( xQueue_Terminal, "SD Card detected!\r\n", NULL );
                vTaskDelay(200);
            }
        }
        else
        {
            if (prev_cardInsertState)
            {
                prev_cardInsertState = cardInsertState;
                FatFsQueueData.stateFatFs = FATFS_DEINIT_SD_CARD;
                xQueueSendToFront( xQueue_FatFsIn, &FatFsQueueData, NULL );
                mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                xQueueSendToFront( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                xQueueSend( xQueue_Terminal, "SD Card removed!\r\n", NULL );
                vTaskDelay(200);
            }
        }
        
        vTaskDelay(50);
    }
}


/* End of file */
