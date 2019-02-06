/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw Run button

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

TaskHandle_t xTask_HwRunButton;
QueueHandle_t xQueue_HwRunButton_Rx;
QueueHandle_t xQueue_HwRunButton_Tx;
volatile HwAPI_BootStatus_t bootStatus_HwRunButton = HW_TASK_BOOT_IDLE;


// Declare private functions
static void InitGPIO_RunButton( void );

// Declare private variables
//static char tempString[450] = {""}; 


void vTask_HwRunButton( void *pvParameters )
{
    HwRunButtonQueueData_t hwRunButtonQueueData;
    RunButtonStatus_t runButtonStatus = RUN_BUTTON_NO_ACTION;
    
    hwRunButtonQueueData.stateHwRunButton = HW_RUN_BUTTON_INIT;            
    xQueueSend( xQueue_HwRunButton_Rx, &hwRunButtonQueueData, NULL ); 
    
    while (1)
    {
        xQueueReceive( xQueue_HwRunButton_Rx, &hwRunButtonQueueData, portMAX_DELAY );
        switch ( hwRunButtonQueueData.stateHwRunButton )
        {
            case HW_RUN_BUTTON_INIT:
            {
                InitGPIO_RunButton();
                
                bootStatus_HwRunButton = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_RUN_BUTTON_GET:
            {
                hwRunButtonQueueData.runButtonStatus = runButtonStatus;
                xQueueSend( xQueue_HwRunButton_Tx, &hwRunButtonQueueData, NULL );
                if ( runButtonStatus == RUN_BUTTON_PRESSED )
                {
                    runButtonStatus = RUN_BUTTON_NO_ACTION;
                }
                break;
            }

            case HW_RUN_BUTTON_PRESSED:
            {
                runButtonStatus = RUN_BUTTON_PRESSED;
                RunButton_Event();
                //HwAPI_Terminal_SendMessage( "Run button pressed\n" );
                break;
            }

            case HW_RUN_BUTTON_IDLE:
            {
                break;
            }    
                
            default:
                break;
        }
    }
}


static TimerHandle_t xProtectTimer;
static void RunButtonTimerCallback( TimerHandle_t xProtectTimer );
static volatile uint8_t flagTimerRun = 0;

//*************************************************
//
// Private function
//
// Initialize GPIO for SD card inserting detection
//
//*************************************************
static void InitGPIO_RunButton( void )
{
    GPIO_InitTypeDef GPIO_cfg;
    EXTI_InitTypeDef EXTI_cfg;

    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
    RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG,ENABLE );
    
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = RUN_BUTTON_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_IN;
    GPIO_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init( RUN_BUTTON_PORT, &GPIO_cfg );

    SYSCFG_EXTILineConfig( EXTI_PortSourceGPIOC, EXTI_PinSource3 ); 
    
    EXTI_StructInit( &EXTI_cfg );
    EXTI_cfg.EXTI_Mode = EXTI_Mode_Interrupt;
    if ( IS_GET_EXTI_LINE( RUN_BUTTON_PIN ) )
    {
        EXTI_cfg.EXTI_Line = RUN_BUTTON_PIN;
    }
    else
    {
        // Error!
        // Pin number is out of range
        // Some error action
    }
    EXTI_cfg.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_cfg.EXTI_LineCmd = ENABLE;
    EXTI_Init( &EXTI_cfg );

    NVIC_SetPriority( EXTI3_IRQn, 15 );
    NVIC_EnableIRQ( EXTI3_IRQn );

    // Create bounce protection timer
    xProtectTimer = xTimerCreate( "Run button timer",
                                  pdMS_TO_TICKS( 80 ),     // delay in ms to reduce contact bounce
                                  pdFALSE,                  // one-shot mode (disable autoreload)
                                  NULL,                     // TimerID not needed
                                  RunButtonTimerCallback );
}


// Interrupt handler for run button pin 
void EXTI3_IRQHandler( void )
{
    // Run protect timer
    if ( !flagTimerRun )
    {
        xTimerStartFromISR( xProtectTimer, NULL );
        flagTimerRun = 1;
    }
    EXTI_ClearITPendingBit( RUN_BUTTON_PIN );
}


//
static void RunButtonTimerCallback( TimerHandle_t xProtectTimer )
{
    HwRunButtonQueueData_t hwRunButtonQueueData;

    if ( !GPIO_ReadInputDataBit( RUN_BUTTON_PORT, RUN_BUTTON_PIN ) )
    {
        hwRunButtonQueueData.stateHwRunButton = HW_RUN_BUTTON_PRESSED;            
        xQueueSend( xQueue_HwRunButton_Rx, &hwRunButtonQueueData, NULL );
    }

    flagTimerRun = 0;
}
/* End of file */
