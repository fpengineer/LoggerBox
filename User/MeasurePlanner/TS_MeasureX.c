/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: MeasureX task to use measure plugins
    
*******************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "HwAPI.h"
#include "MeasurePlannerDef.h"
#include "MeasurePlanner Utils.h"
#include "PluginsDef.h"

//TaskHandle_t xTask_MeasureX;
QueueHandle_t xQueue_MeasureX_Rx;
//QueueHandle_t xQueue_MeasureX_Tx;


static char tempString[ 200 ] = { "" };


void vTask_MeasureX( void *pvParameters )
{
#if 1
    MeasureXQueueData_t measureXQueueData;
    PluginResult_t pluginResult = { 0, 0, "" };
    int32_t tactLength_ms = 0;
    TickType_t xLastWakeTime;

    xLastWakeTime = xTaskGetTickCount();
    
    measureXQueueData.stateMeasureX = MEASURE_X_INIT;            
    xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 

    while ( 1 )
    {
        xQueueReceive( xQueue_MeasureX_Rx, &measureXQueueData, portMAX_DELAY );

        switch ( measureXQueueData.stateMeasureX )
        {
            case MEASURE_X_INIT:
            {
                //HwAPI_Terminal_SendMessage( "TS_MeasureX - Init\n" );

                break;
            }
            
            case MEASURE_X_RUN:
            {
                /* Check for a NULL plugin pointer */
                if ( measureXQueueData.pluginRef != NULL )
                {
                    /* Perform plugin command */
                    measureXQueueData.pluginRef( &pluginResult, CMD_PLUGIN_RUN, &tactLength_ms );

                    measureXQueueData.stateMeasureX = MEASURE_X_TACT;
                    xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
                
                    xLastWakeTime = xTaskGetTickCount();
                    vTaskDelayUntil( &xLastWakeTime, ( TickType_t )tactLength_ms );
                }
                else
                {
                    /* Run error handler */
                    pluginResult.error = 1;
                    pluginResult.errorCode = 10;
                    snprintf( pluginResult.message, sizeof( pluginResult.message ), "Error %d!\n Plugin pointer is NULL.", pluginResult.errorCode );

                    measureXQueueData.stateMeasureX = MEASURE_X_ERROR;
                    xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
                }
                break;
            }
            
            case MEASURE_X_TACT:
            {
                /* Check for a NULL plugin pointer */
                if ( measureXQueueData.pluginRef != NULL )
                {
                    /* Perform plugin command */
                    measureXQueueData.pluginRef( &pluginResult, CMD_PLUGIN_TACT, NULL );
                    
                    if ( !pluginResult.error )
                    {
                        measureXQueueData.stateMeasureX = MEASURE_X_TACT;            
                        xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL );
                        
                        vTaskDelayUntil( &xLastWakeTime, ( TickType_t )tactLength_ms );
                    }
                    else
                    {
                        measureXQueueData.stateMeasureX = MEASURE_X_ERROR;
                        xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
                    }
                    
                }
                else
                {
                    /* Run error handler */
                    pluginResult.error = 1;
                    pluginResult.errorCode = 10;
                    snprintf( pluginResult.message, sizeof( pluginResult.message ), "Error %d!\n Plugin pointer is NULL.", pluginResult.errorCode );

                    measureXQueueData.stateMeasureX = MEASURE_X_ERROR;
                    xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
                }
                break;
            }
    
            case MEASURE_X_STOP:
            {
                /* Check for a NULL plugin pointer */
                if ( measureXQueueData.pluginRef != NULL )
                {
                    /* Perform plugin command */
                    measureXQueueData.pluginRef( &pluginResult, CMD_PLUGIN_STOP, NULL );

                    if ( !pluginResult.error )
                    {
                        xQueueReset( xQueue_MeasureX_Rx );
                    }
                    else
                    {
                        measureXQueueData.stateMeasureX = MEASURE_X_ERROR;
                        xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
                    }
                }
                else
                {
                    /* Run error handler */
                    pluginResult.error = 1;
                    pluginResult.errorCode = 10;
                    snprintf( pluginResult.message, sizeof( pluginResult.message ), "Error %d!\n Plugin pointer is NULL.", pluginResult.errorCode );

                    measureXQueueData.stateMeasureX = MEASURE_X_ERROR;
                    xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
                }
                break;
            }
    
            case MEASURE_X_ERROR:
            {
                /* Send error message to the terminal */
                snprintf( tempString, sizeof( tempString ), "Error %d! %s\n", pluginResult.errorCode, pluginResult.message );
                HwAPI_Terminal_SendMessage( tempString );

                pluginResult.error = 0;
                pluginResult.errorCode = 0;
                snprintf( pluginResult.message, sizeof( pluginResult.message ), "" );
                
                xQueueReset( xQueue_MeasureX_Rx );

                /* Send error command to measure planner */
                MeasurePluginError();
                break;
            }

            case MEASURE_X_IDLE:
            {

                break;
            }

            default:
                break;
        }
    }
#endif
}
/* End of file */
