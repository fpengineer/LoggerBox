/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins delay wrapper

*******************************************************************************************************/
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"

#include "PluginsDelay.h"


/* wrapper for delay in ms */
void PluginDelay_ms( int32_t ms )
{
    vTaskDelay( ms );
}
/* End of file */
