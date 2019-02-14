/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measue Planner utilites

*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "TS_queue.h"
#include "TS_task.h"

#include "HwAPI.h"

#include "defines.h"
#include "PluginsDef.h"
#include "MeasurePlanner Utils.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

extern TaskHandle_t xTask_MeasurePlanner;
extern TaskHandle_t xTask_MeasurePlugin;

extern QueueHandle_t xQueue_MeasurePlanner_Rx;
extern QueueHandle_t xQueue_MeasurePlugin_Rx;
extern QueueHandle_t xQueue_MeasurePlugin_Tx;

extern const char *pluginsList[];
extern void (*pluginsPointerList[])( void *pvParameters );



// Read data from main config file
int32_t ReadConfigFile( ConfigData_t *configData, char *fileName )
{
    char tempString[ 50 ] = { "" };

    HwAPI_Terminal_SendMessage( "Read 'config.ini'.\n" );

    if ( FATFS_OK == HwAPI_FatFs_INI_GetKeyInt( "SystemTime", "UpdateSystemTime", "config.ini", &configData->updateSystemTime ) &&
         FATFS_OK == HwAPI_FatFs_INI_GetKeyString( "SystemTime", "SystemTimeString", "config.ini", configData->systemTimeString ) &&
         FATFS_OK == HwAPI_FatFs_INI_GetKeyString( "SelectIC", "NameIC", "config.ini", configData->nameIC ) )
    {
        HwAPI_Terminal_SendMessage( "[SystemTime]\n" );
        snprintf( tempString, sizeof(tempString), "UpdateSystemTime = %d\n"
                                                  "SystemTimeString = %s\n", 
                                                  configData->updateSystemTime,
                                                  configData->systemTimeString );
        HwAPI_Terminal_SendMessage( tempString );

        HwAPI_Terminal_SendMessage( "\n[SelectIC]\n" );
        snprintf( tempString, sizeof( tempString ), "NameIC = %s\n\n", configData->nameIC );
        HwAPI_Terminal_SendMessage( tempString );
        
        return 1;
    }

    return 0;
}


// Process system time setings from the config file
void ProcessSystemTimeConfig( char *systemTimeString, int32_t updateSystemTime )
{
    char tempString[ 100 ] = { "" };
    
    // check system time update enable flag
    if ( updateSystemTime == UPDATE_SYSTEM_TIME_ENABLE )
    {
        // Set system time
        HwAPI_SystemTime_Set( systemTimeString );
                
        // disable system time enable flag in "config.ini" file
        HwAPI_FatFs_INI_PutKeyInt( "SystemTime", "UpdateSystemTime", "config.ini", UPDATE_SYSTEM_TIME_DISABLE );

        HwAPI_Terminal_SendMessage( "System time updated.\n" );

        // Get new system time
        HwAPI_SystemTime_Get( systemTimeString );
        snprintf( tempString, sizeof( tempString ), "New system time: %s\n\n", systemTimeString );
        HwAPI_Terminal_SendMessage( tempString );
    }
}


// Find measure plugin in the registered plugin list
int32_t FindMeasurePlugin( char *nameIC )
{
    char tempString[ 100 ] = { "" };
    int32_t i = 0;
    
    HwAPI_Terminal_SendMessage( "Find plugin in the plugins list.\n" );

    // Check if plugin exist
    for ( i = 0; i < GetSizeof_pluginsList() / GetSizeof_pluginsListElement(); i++ )
    {
        if ( strcmp( pluginsList[ i ], nameIC ) == 0 )
        {
            snprintf( tempString, sizeof( tempString ), "Plugin '%s' found.\n\n", nameIC );
            HwAPI_Terminal_SendMessage( tempString );
            return i;
        }
    }

    snprintf( tempString, sizeof( tempString ), "Error! Plugin '%s' did not found in the registered plugins list.\n\n", nameIC );
    HwAPI_Terminal_SendMessage( tempString );
    return -1;
}
    

// Check if measure plun file exist for selected plugin
int32_t CheckMeasurePlanFile( char *nameIC )
{
    char tempString[ 100 ] = { "" };
    int32_t i = 0;
    
    HwAPI_Terminal_SendMessage( "Check if measure plan file exist.\n" );

    // Create filename of the measure plan file
    snprintf( tempString, sizeof( tempString ), "MeasurePlan_%s.ini", nameIC );
      
    // Check if measure plan file exist
    switch ( HwAPI_FatFs_CheckFileExist( tempString ) )
    {
        case FATFS_OK:
        {
            snprintf( tempString, sizeof( tempString ), "File 'MeasurePlan_%s.ini' found.\n\n", nameIC );
            HwAPI_Terminal_SendMessage( tempString );
            i = 1;
            break;
        }
       
        case FATFS_ERROR_FILE_NOT_FOUND:
        {  
            snprintf( tempString, sizeof( tempString ), "Error! File 'MeasurePlan_%s.ini' not found.\n\n", nameIC );
            HwAPI_Terminal_SendMessage( tempString );
            break;
        }
        
        default:
            break;
    }
    return i;
}


// Load measure plugin
void LoadMeasurePlugin( int32_t pluginIndex )
{
    char tempString[ 100 ] = { "" };

    HwAPI_Terminal_SendMessage( "Load selected plugin.\n" );

    // Load selected plugin
    if ( pluginIndex >= 0 )
    {
        if( pdTRUE != xTaskCreate(  pluginsPointerList[ pluginIndex ],
                                "Task - Measure Plugin",
                                configMINIMAL_STACK_SIZE + 5000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_MeasurePlugin ) ) { ERROR_ACTION(TASK_NOT_CREATE,0); }	

        xQueue_MeasurePlugin_Rx = xQueueCreate( 5, sizeof( MeasurePluginQueueData_t ) );
        xQueue_MeasurePlugin_Tx = xQueueCreate( 5, sizeof( MeasurePluginQueueData_t ) );
    }
    else
    {
        snprintf( tempString, sizeof( tempString ), "Error!\n"
                                                    "Wrong plugin index. pluginIndex = %d.\n", pluginIndex );
        HwAPI_Terminal_SendMessage( tempString );
   }
}


// Unload measure plugin
void UnloadMeasurePlugin( void )
{
    vTaskDelete( xTask_MeasurePlugin );
    vQueueDelete( xQueue_MeasurePlugin_Rx );
    vQueueDelete( xQueue_MeasurePlugin_Tx );
}


// Send plugins list
void SendPluginsList( void )
{
    char tempString[ 50 ] = { "" };
    int32_t i = 0;
    
    HwAPI_Terminal_SendMessage( "List of registered ICs:\n" );

    for ( i = 0; i < ( GetSizeof_pluginsList() / GetSizeof_pluginsListElement() - 1 ); i++ )
    {
        snprintf( tempString, sizeof( tempString ), "%s\n", pluginsList[ i ] );
        HwAPI_Terminal_SendMessage( tempString );
    }
    HwAPI_Terminal_SendMessage( "\n" );
}


// Set system to default state
void SetSystemDefault( void )
{
    // Clear relays
    HwAPI_Relay_ClearAll();
    
    // Clear voltage source
    HwAPI_VoltageSource_ClearAll();
    
    // Stop DAQ ADC measure and clear tx queue
    HwAPI_DAQ_ADC_Stop();
    
    // Stop DAQ Frequency measure and clear tx queue
    HwAPI_DAQ_Frequency_Stop();
}


// Run measure plugin
void RunMeasurePlugin( void )
{
//    extern QueueHandle_t xQueue_MeasurePlugin_Rx;
    MeasurePluginQueueData_t measurePluginQueueData;
    
    measurePluginQueueData.stateMeasurePlugin = MEASURE_PLUGIN_RUN;
    xQueueSend( xQueue_MeasurePlugin_Rx, &measurePluginQueueData, NULL ); 
}


// Stop measure plugin
void StopMeasurePlugin( void )
{
//    extern QueueHandle_t xQueue_MeasurePlugin_Rx;
    MeasurePluginQueueData_t measurePluginQueueData;
    
    measurePluginQueueData.stateMeasurePlugin = MEASURE_PLUGIN_STOP;
    xQueueSendToFront( xQueue_MeasurePlugin_Rx, &measurePluginQueueData, NULL ); 
}
/* End of file */
