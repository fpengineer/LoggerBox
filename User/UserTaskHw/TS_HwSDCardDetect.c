/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw SD Card Detect

*******************************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_exti.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HwAPI.h"
#include "TS_HwQueue.h"
#include "TS_task.h"


// Declare private functions
static void InitGPIO_SDCardDetect( void );
/* Create 2 callback functions for custom timers */
static void ContactBounceTimer_Task(void* UserParameters);



//static char tempString[450] = {""}; 


/* Pointers to custom timers */
static TM_DELAY_Timer_t* CustomTimer;


void vTask_HwSDCardDetect( void *pvParameters )
{
    HwSDCardDetectQueueData_t hwSDCardDetectQueueData;
    SDCardDetectStatus_t sdCardDetectStatus = SD_CARD_REMOVE;
    
    hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_INIT;            
    xQueueSend( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL ); 
    
    while (1)
    {
        xQueueReceive( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, portMAX_DELAY );

        switch ( hwSDCardDetectQueueData.stateHwSDCardDetect )
        {
            case HW_SDCARD_DETECT_INIT:
            {
                // Init gpio for sd card detction signal
                InitGPIO_SDCardDetect();

                if ( !TM_GPIO_GetInputPinValue( SDCARD_DETECT_PORT, SDCARD_DETECT_PIN ) )
                {
                    sdCardDetectStatus = SD_CARD_INSERT;
                    HwAPI_FatFs_InitSDCard();
                }
                break;
            }

            case HW_SDCARD_DETECT_GET:
            {
                hwSDCardDetectQueueData.sdCardDetectStatus = sdCardDetectStatus;
                xQueueSend( xQueue_HwSDCardDetect_Tx, &hwSDCardDetectQueueData, NULL );
                break;
            }

            case HW_SDCARD_DETECT_INSERT:
            {
                sdCardDetectStatus = SD_CARD_INSERT;
                HwAPI_FatFs_InitSDCard();
                break;
            }

            case HW_SDCARD_DETECT_REMOVE:
            {
                sdCardDetectStatus = SD_CARD_REMOVE;
                HwAPI_FatFs_DeinitSDCard();
                break;
            }

            case HW_SDCARD_DETECT_IDLE:
                break;

            default:
                break;
        }
    }
}






//*************************************************
//
// Private function
//
// Initialize GPIO for SD card inserting detection
//
//*************************************************
static void InitGPIO_SDCardDetect( void )
{
	CustomTimer = TM_DELAY_TimerCreate( 70, 0, 0, ContactBounceTimer_Task, NULL );

    TM_EXTI_Attach( SDCARD_DETECT_PORT,
                    SDCARD_DETECT_PIN, 
                    TM_EXTI_Trigger_Rising_Falling );

    if ( !TM_GPIO_GetInputPinValue( SDCARD_DETECT_PORT, SDCARD_DETECT_PIN ) )
    {
        TM_DISCO_LedOn( LED_GREEN );
    }
}


// Interrupt handler for sd card detection pin 
void EXTI0_IRQHandler( void )
{
	/* Check status */
	if ( EXTI->PR & ( EXTI_PR_PR0 ) )
    {
		/* Clear bit */
		EXTI->PR = EXTI_PR_PR0;
	}

    TM_DELAY_TimerStart( CustomTimer );

}


/* Called when Custom TIMER2 reaches zero */
static void ContactBounceTimer_Task( void* UserParameters )
{
    HwSDCardDetectQueueData_t hwSDCardDetectQueueData;

    if ( !TM_GPIO_GetInputPinValue( SDCARD_DETECT_PORT, SDCARD_DETECT_PIN ) )
    {
        TM_DISCO_LedOn( LED_GREEN );
        
        hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_INSERT;            
        xQueueSendFromISR( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL ); // Need to test!!!!!!
    }
    else
    {
        TM_DISCO_LedOff( LED_GREEN );

        hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_REMOVE;            
        xQueueSendFromISR( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL ); // Need to test!!!!!!!
    }
}
    
    
/* End of file */
