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
    
    while ( uxQueueSpacesAvailable( xQueue_HwTerminal_Rx ) == 0 ){;};
    xQueueSend( xQueue_HwTerminal_Rx, message, NULL );
}


//
HwAPI_BootStatus_t HwAPI_Terminal_Run( void )
{
    extern TaskHandle_t xTask_HwTerminal;
    extern QueueHandle_t xQueue_HwTerminal_Rx;
    extern volatile HwAPI_BootStatus_t bootStatus_HwTerminal;

    xQueue_HwTerminal_Rx = xQueueCreate( 15, sizeof( char[ TERMINAL_BUFFER_SIZE ] ) );

	if( pdTRUE != xTaskCreate(  vTask_HwTerminal,
                                "Task - HwTerminal",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwTerminal ) ) { /* some error action */ }	

    while ( bootStatus_HwTerminal == HW_TASK_BOOT_IDLE ){;}
    
    if ( bootStatus_HwTerminal == HW_TASK_BOOT_PENDING )
    {
        bootStatus_HwTerminal = HW_TASK_BOOT_RUN;
    }
    
    return bootStatus_HwTerminal;
}
/* End of file */
