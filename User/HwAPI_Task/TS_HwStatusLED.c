/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw Status LED

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

#include "HwAPI.h"
#include "TS_HwQueue.h"
#include "TS_task.h"

// Declare private functions
static void InitStatusLEDHardware( void );

// Declare private variables


void vTask_HwStatusLED( void *pvParameters )
{
    HwStatusLEDQueueData_t hwStatusLEDQueueData;
    TickType_t timeout = 0;
    
    hwStatusLEDQueueData.stateHwStatusLED = HW_STATUS_LED_INIT;            
    xQueueSend( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, NULL ); 
	while ( 1 )
	{
        xQueueReceive( xQueue_HwStatusLED_Rx, &hwStatusLEDQueueData, timeout );
        switch ( hwStatusLEDQueueData.stateHwStatusLED )
        {
            case HW_STATUS_LED_INIT:
            {
				InitStatusLEDHardware();
				StatusLED_Off();
				
                bootState_HwStatusLED = TASK_BOOT_PENDING;
                break;
            }

            case HW_STATUS_LED_ON:
            {
                StatusLED_On();
                timeout = portMAX_DELAY;
                break;
            }
            
            case HW_STATUS_LED_OFF:
            {
				StatusLED_Off();
                timeout = portMAX_DELAY;
                break;
            }
            
            case HW_STATUS_LED_FLASH:
            {
				StatusLED_Toggle();
                timeout = hwStatusLEDQueueData.delay_ms / portTICK_PERIOD_MS;
                break;
            }                
            case HW_STATUS_LED_IDLE:
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
// Initialize hardware
//
//*************************************************
static void InitStatusLEDHardware( void )
{
    GPIO_InitTypeDef GPIO_cfg;
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );

    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = STATUS_LED_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( STATUS_LED_PORT, &GPIO_cfg );
}

/* End of file */
