/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Terminal

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_usart.h"

#include "HwAPI.h"

TaskHandle_t xTask_HwTerminal;
QueueHandle_t xQueue_HwTerminal_Rx;
volatile HwAPI_BootStatus_t bootStatus_HwTerminal = HW_TASK_BOOT_IDLE;

static char tempString[500] = {""}; 
    
void vTask_HwTerminal( void *pvParameters )
{
	/* Initialize USART, TX: PB10, RX: PB11 */
    TM_USART_Init(USART2, TM_USART_PinsPack_2, (uint32_t)(115200.0 * 3.125)); // Why coefficient is 3.125?
    bootStatus_HwTerminal = HW_TASK_BOOT_PENDING;
	
    while( 1 )
	{
        xQueueReceive( xQueue_HwTerminal_Rx, &tempString, portMAX_DELAY );

       /* Send to USART */
        TM_USART_Puts( USART2, tempString );
	}
}

/* End of file */
