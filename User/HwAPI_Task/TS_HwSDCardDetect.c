/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw SD Card Detect

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "queue.h"

#include "stm32f4xx.h"
#include "defines.h"

#include "HwAPI.h"

TaskHandle_t xTask_HwSDCardDetect;
QueueHandle_t xQueue_HwSDCardDetect_Rx;
QueueHandle_t xQueue_HwSDCardDetect_Tx;
volatile HwAPI_BootStatus_t bootStatus_HwSDCardDetect = HW_TASK_BOOT_IDLE;


// Declare private functions
static void InitGPIO_SDCardDetect( void );

// Declare private variables
//static char tempString[450] = {""}; 

void vTask_HwSDCardDetect( void *pvParameters )
{
    HwSDCardDetectQueueData_t hwSDCardDetectQueueData;
    SDCardDetectStatus_t sdCardDetectStatus = SD_CARD_REMOVE;
    
    hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_INIT;            
    xQueueSend( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL ); 
    
    while ( 1 )
    {
        xQueueReceive( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, portMAX_DELAY );
        switch ( hwSDCardDetectQueueData.stateHwSDCardDetect )
        {
            case HW_SDCARD_DETECT_INIT:
            {
                // Init gpio for sd card detction signal
                InitGPIO_SDCardDetect();

                if ( !GPIO_ReadInputDataBit( SDCARD_DETECT_PORT, SDCARD_DETECT_PIN ) )
                {
                    sdCardDetectStatus = SD_CARD_INSERT;
                    HwAPI_FatFs_InitSDCard();
                }
                
                bootStatus_HwSDCardDetect = HW_TASK_BOOT_PENDING;
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
                //HwAPI_Terminal_SendMessage( "SD card inserted\n" );
                HwAPI_FatFs_InitSDCard();
                break;
            }

            case HW_SDCARD_DETECT_REMOVE:
            {
                sdCardDetectStatus = SD_CARD_REMOVE;
                //HwAPI_Terminal_SendMessage( "SD card removed\n" );
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




static TimerHandle_t xProtectTimer;
static void SDCardDetectTimerCallback( TimerHandle_t xTimer );
static EXTI_InitTypeDef EXTI_cfg;
static volatile uint8_t flagTimerRun = 0;

//*************************************************
//
// Private function
//
// Initialize GPIO for SD card inserting detection
//
//*************************************************
static void InitGPIO_SDCardDetect( void )
{
    GPIO_InitTypeDef GPIO_cfg;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG,ENABLE );
    
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = SDCARD_DETECT_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_IN;
    GPIO_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init( SDCARD_DETECT_PORT, &GPIO_cfg );

    SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOA, EXTI_PinSource0 ); 
    
    EXTI_StructInit( &EXTI_cfg );
    EXTI_cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    if ( IS_GET_EXTI_LINE( SDCARD_DETECT_PIN ) )
    {
        EXTI_cfg.EXTI_Line = SDCARD_DETECT_PIN;
    }
    else
    {
        // Error!
        // Pin number is out of range
        // Some error action
    }

    if ( !GPIO_ReadInputDataBit( SDCARD_DETECT_PORT, SDCARD_DETECT_PIN ) )
    {
        EXTI_cfg.EXTI_Trigger = EXTI_Trigger_Rising;
    }
    else
    {
        EXTI_cfg.EXTI_Trigger = EXTI_Trigger_Falling;
    }
    EXTI_cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init( &EXTI_cfg );

    NVIC_SetPriority( EXTI0_IRQn, 15 );
    NVIC_EnableIRQ( EXTI0_IRQn );

    // Create bounce protection timer
    xProtectTimer = xTimerCreate( "SD card detect timer",
                                  pdMS_TO_TICKS( 150 ),     // delay in ms to reduce contact bounce
                                  pdFALSE,                  // one-shot mode (disable autoreload)
                                  NULL,                     // TimerID not needed
                                  SDCardDetectTimerCallback );
}


// Interrupt handler for sd card detection pin 
void EXTI0_IRQHandler( void )
{
    // Run protect timer
    if ( !flagTimerRun )
    {
        xTimerStartFromISR( xProtectTimer, NULL );
        flagTimerRun = 1;
    }
    EXTI_ClearITPendingBit( SDCARD_DETECT_PIN );
}


//
static void SDCardDetectTimerCallback( TimerHandle_t xTimer )
{
    HwSDCardDetectQueueData_t hwSDCardDetectQueueData;

    if ( !GPIO_ReadInputDataBit( SDCARD_DETECT_PORT, SDCARD_DETECT_PIN ) )
    {
        hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_INSERT;            
        xQueueSend( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL );
        
        EXTI_cfg.EXTI_Trigger = EXTI_Trigger_Rising;
        EXTI_Init( &EXTI_cfg );
    }
    else
    {
        hwSDCardDetectQueueData.stateHwSDCardDetect = HW_SDCARD_DETECT_REMOVE;            
        xQueueSend( xQueue_HwSDCardDetect_Rx, &hwSDCardDetectQueueData, NULL );
        
        EXTI_cfg.EXTI_Trigger = EXTI_Trigger_Falling;
        EXTI_Init( &EXTI_cfg );
    }

    flagTimerRun = 0;
}
/* End of file */
