/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Status LED

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "stdint.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_task.h"

#include "stm32f4xx.h"
#include "defines.h"
#include "tm_stm32f4_gpio.h"

void vTask_StatusLed( void *pvParameters )
{
    extern QueueHandle_t xQueue_StatusLed;
    extern QueueHandle_t xQueue_Terminal;
    enum stateStatusLed stateStatusLed = STATUS_LED_OFF;
    TickType_t timeout = portMAX_DELAY;
    
    TM_GPIO_Init(GPIOC,
                 GPIO_PIN_0,
                 TM_GPIO_Mode_OUT,
                 TM_GPIO_OType_PP,
                 TM_GPIO_PuPd_NOPULL,
                 TM_GPIO_Speed_Medium);


    TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_0);

	while (1)
	{
        xQueueReceive(xQueue_StatusLed, &stateStatusLed, timeout );
        
        switch ((int32_t)stateStatusLed)
        {
            case STATUS_LED_ON:
                /* Enable Led */
                timeout = portMAX_DELAY;
                TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_0);
                break;
                
            case STATUS_LED_OFF:
                /* Disable Led */
                timeout = portMAX_DELAY;
                TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_0);
                break;
                
            case STATUS_LED_FLASH:
                /* Toggle Led */
                timeout = 500 / portTICK_PERIOD_MS;
                TM_GPIO_TogglePinValue(GPIOC, GPIO_Pin_0);
                break;
                
            default:
                break;
        }
    }
}


/* End of file */
