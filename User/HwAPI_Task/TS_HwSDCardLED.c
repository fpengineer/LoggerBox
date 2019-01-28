/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw SD card LED

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


TaskHandle_t xTask_HwSDCardLED;
QueueHandle_t xQueue_HwSDCardLED_Rx;
volatile HwAPI_BootStatus_t bootStatus_HwSDCardLED = HW_TASK_BOOT_IDLE;

// Declare private functions
static void InitSDCardLEDHardware( void );

// Declare private variables


void vTask_HwSDCardLED( void *pvParameters )
{
    HwSDCardLEDQueueData_t hwSDCardLEDQueueData;
    TickType_t timeout = 0;
    
    hwSDCardLEDQueueData.stateHwSDCardLED = HW_SDCARD_LED_INIT;            
    xQueueSend( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, NULL ); 
	while ( 1 )
	{
        xQueueReceive( xQueue_HwSDCardLED_Rx, &hwSDCardLEDQueueData, timeout );
        switch ( hwSDCardLEDQueueData.stateHwSDCardLED )
        {
            case HW_SDCARD_LED_INIT:
            {
				InitSDCardLEDHardware();
				SDCardLED_Off();
				
                bootStatus_HwSDCardLED = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_SDCARD_LED_ON:
            {
                SDCardLED_On();
                timeout = portMAX_DELAY;
                break;
            }
            
            case HW_SDCARD_LED_OFF:
            {
				SDCardLED_Off();
                timeout = portMAX_DELAY;
                break;
            }
            
            case HW_SDCARD_LED_FLASH:
            {
				SDCardLED_Toggle();
                timeout = hwSDCardLEDQueueData.delay_ms / portTICK_PERIOD_MS;
                break;
            }                
            case HW_SDCARD_LED_IDLE:
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
static void InitSDCardLEDHardware( void )
{
    GPIO_InitTypeDef GPIO_cfg;
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );

    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = SDCARD_LED_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( SDCARD_LED_PORT, &GPIO_cfg );
}

/* End of file */
