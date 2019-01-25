/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for terminal

*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "HwAPI.h"


//
void HwAPI_Terminal_SendMessage( char *message )
{
    extern QueueHandle_t xQueue_HwTerminal_Rx;
    xQueueSend( xQueue_HwTerminal_Rx, message, NULL );
}


//
void HwAPI_Terminal_Run( void )
{
    extern TaskHandle_t xTask_HwTerminal;
    extern QueueHandle_t xQueue_HwTerminal_Rx;
    
    xQueue_HwTerminal_Rx = xQueueCreate( 5, sizeof( char[ TERMINAL_BUFFER ] ) );

	if( pdTRUE != xTaskCreate(  vTask_HwTerminal,
                                "Task - HwTerminal",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwTerminal ) ) { /* some error action */ }	
}


//
HwAPI_BootStatus_t HwAPI_Terminal_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwTerminal;
    
    return bootStatus_HwTerminal;
}


/* End of file */
