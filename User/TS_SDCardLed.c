/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - SD Card LED

*******************************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f4xx.h"
#include "defines.h"
#include "tm_stm32f4_gpio.h"

#include "TS_queue.h"
#include "TS_task.h"

void vTask_SDCardLed( void *pvParameters )
{
    extern QueueHandle_t xQueue_SDCardLed;
    extern QueueHandle_t xQueue_Terminal;
    enum stateSDCardLed stateSDCardLed = SDCARD_LED_OFF;
    TickType_t timeout = portMAX_DELAY;
    
    TM_GPIO_Init(GPIOC,
                 GPIO_PIN_2,
                 TM_GPIO_Mode_OUT,
                 TM_GPIO_OType_PP,
                 TM_GPIO_PuPd_NOPULL,
                 TM_GPIO_Speed_Medium);


    TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_2);

	while( 1 )
	{
        xQueueReceive(xQueue_SDCardLed, &stateSDCardLed, timeout );
        
        switch ((int32_t)stateSDCardLed)
        {
            case SDCARD_LED_ON:
                /* Enable Led */
                timeout = portMAX_DELAY;
                TM_GPIO_SetPinHigh(GPIOC, GPIO_Pin_2);
                break;
                
            case SDCARD_LED_OFF:
                /* Disable Led */
                timeout = portMAX_DELAY;
                TM_GPIO_SetPinLow(GPIOC, GPIO_Pin_2);
                break;
                
            case SDCARD_LED_FLASH:
                /* Toggle Led */
                timeout = 100 / portTICK_PERIOD_MS;
                TM_GPIO_TogglePinValue(GPIOC, GPIO_Pin_2);
                break;
                
            default:
                break;
        }
	}
}

/* End of file */
