/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw Run button

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
static void InitGPIO_RunButton( void );
/* Create callback function for custom timer */
static void ContactBounceTimer_Task(void* UserParameters);



//static char tempString[450] = {""}; 


/* Pointers to custom timers */
static TM_DELAY_Timer_t* CustomTimer;


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



//*************************************************
//
// Private function
//
// Initialize GPIO for SD card inserting detection
//
//*************************************************
static void InitGPIO_RunButton( void )
{
	CustomTimer = TM_DELAY_TimerCreate( 70, 0, 0, ContactBounceTimer_Task, NULL );

    TM_EXTI_Attach( RUN_BUTTON_PORT,
                    RUN_BUTTON_PIN, 
                    TM_EXTI_Trigger_Falling );
}


// Interrupt handler for sd card detection pin 
void EXTI3_IRQHandler( void )
{
	/* Check status */
	if ( EXTI->PR & ( EXTI_PR_PR3 ) )
    {
		/* Clear bit */
		EXTI->PR = EXTI_PR_PR3;
	}

    TM_DELAY_TimerStart( CustomTimer );

}


/* Called when Custom TIMER2 reaches zero */
static void ContactBounceTimer_Task( void* UserParameters )
{
    HwRunButtonQueueData_t hwRunButtonQueueData;

    if ( !TM_GPIO_GetInputPinValue( RUN_BUTTON_PORT, RUN_BUTTON_PIN ) )
    {
        TM_DISCO_LedToggle( LED_RED );
        
        hwRunButtonQueueData.stateHwRunButton = HW_RUN_BUTTON_PRESSED;            
        xQueueSendFromISR( xQueue_HwRunButton_Rx, &hwRunButtonQueueData, NULL ); // Need to test!!!!!!
    }
}
    
    
/* End of file */
