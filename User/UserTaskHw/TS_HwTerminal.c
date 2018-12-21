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
#include "tm_stm32f4_rtc.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_fatfs.h"

static char tempString[500] = {""}; 
//char* tempString2[20] = {""};
    
void vTask_Terminal( void *pvParameters )
{

    extern QueueHandle_t xQueue_Terminal;
	/* Initialize USART, TX: PB10, RX: PB11 */
    TM_USART_Init(USART2, TM_USART_PinsPack_2, (uint32_t)(115200.0 * 3.125)); // Why coefficient 3.125?

	while( 1 )
	{
        xQueueReceive( xQueue_Terminal, &tempString, portMAX_DELAY );

       /* Send to USART */
        TM_USART_Puts( USART2, tempString );
	}
}

/* End of file */
