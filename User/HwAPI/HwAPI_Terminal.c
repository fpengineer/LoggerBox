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

#include "TS_queue.h"
#include "TS_HwQueue.h"

#include "HwAPI.h"


//
void HwAPI_Terminal_SendMessage( char *message )
{
    xQueueSend( xQueue_HwTerminal_Rx, message, NULL );
}


/* End of file */
