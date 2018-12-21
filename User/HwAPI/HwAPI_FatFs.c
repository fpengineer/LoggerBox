/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for FatFs

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
void HwAPI_FatFs_GetKeyINI( int32_t keyType, char *nameSection, char *nameKey, char *fileName, void *data )
{
    int32_t keyIntegerValue = 0;
    float keyFloatValue = 0.0f;
    char keyStringValue[100] = "";
    
    switch ( keyType )
    {
        case INI_KEY_INT:
            keyIntegerValue = *(int *)data;
            break;
    
        case INI_KEY_FLOAT:
            keyFloatValue = *(float *)data;
            break;
    	
        case INI_KEY_STRING:
            keyStringValue = *(char *)data;
            break;
    	
        default:
            // rturn error if wrong key type
            break;
    }

//    xQueueSend( xQueue_HwTerminal_Rx, message, NULL );


    
}

//
void HwAPI_FatFs_PutKeyINI( int32_t keyType, char *nameSection, char *nameKey, char *fileName, void *data )
{
    
    
}


/* End of file */
