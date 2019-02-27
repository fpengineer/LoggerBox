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

#include "HwAPI.h"

#include "defines.h"
#include "PluginsList.h"
#include "MeasurePlannerDef.h"
#include "MeasurePlanner Utils.h"

extern const char *pluginsList[];
extern void (*pluginsPointerList[])( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

static void (*pluginRef)( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms ) = NULL; 


// Read data from main config file
int32_t ReadConfigFile( ConfigData_t *configData, char *fileName )
{
    char tempString[ 150 ] = { "" };

    snprintf( tempString, sizeof( tempString ), "Read '%s' file.\n", fileName );
    HwAPI_Terminal_SendMessage( tempString );

    if ( FATFS_OK == HwAPI_FatFs_CheckFileExist( fileName ) )
    {
        HwAPI_FatFs_INI_GetConfigFileStrings( fileName, MAIN_CONFIG_FILE );

        if ( FATFS_OK == HwAPI_FatFs_INI_GetKeyInt( "SystemTime", "UpdateSystemTime", fileName, &configData->updateSystemTime, MAIN_CONFIG_FILE ) &&
             FATFS_OK == HwAPI_FatFs_INI_GetKeyString( "SystemTime", "SystemTimeString", fileName, configData->systemTimeString, MAIN_CONFIG_FILE ) &&
             FATFS_OK == HwAPI_FatFs_INI_GetKeyString( "SelectIC", "NameIC", fileName, configData->nameIC, MAIN_CONFIG_FILE ) )
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
    }
    else
    {
        snprintf( tempString, sizeof( tempString ), "Error! File '%s' not found.\n", fileName );
        HwAPI_Terminal_SendMessage( tempString );
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
        HwAPI_FatFs_INI_PutKeyInt( "SystemTime", "UpdateSystemTime", "config.ini", UPDATE_SYSTEM_TIME_DISABLE, MAIN_CONFIG_FILE );

        HwAPI_Terminal_SendMessage( "System time updated.\n" );

        // Get new system time
        HwAPI_SystemTime_Get( systemTimeString, sizeof( systemTimeString ) );
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
    char filename[ 100 ] = { "" };
    char tempString[ 100 ] = { "" };
    int32_t i = 0;
    
    HwAPI_Terminal_SendMessage( "Check if measure plan file exist.\n" );

    // Create filename of the measure plan file
    snprintf( filename, sizeof( filename ), "MeasurePlan_%s.ini", nameIC );
      
    // Check if measure plan file exist
    switch ( HwAPI_FatFs_CheckFileExist( filename ) )
    {
        case FATFS_OK:
        {
            snprintf( tempString, sizeof( tempString ), "File '%s' found.\n\n", filename );
            HwAPI_Terminal_SendMessage( tempString );
            HwAPI_FatFs_INI_GetConfigFileStrings( filename, MEASURE_PLAN_FILE );
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

    //HwAPI_Terminal_SendMessage( "Load selected plugin.\n" );

    // Load selected plugin
    if ( pluginIndex >= 0 )
    {
        pluginRef = pluginsPointerList[ pluginIndex ];
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
        pluginRef = NULL;
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
    HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_1 );
    HwAPI_DAQ_ADC_Stop();
    
    // Stop DAQ Frequency measure and clear tx queue
    HwAPI_DAQ_Frequency_Stop();
}


// Run measure plugin
void RunMeasurePlugin( void )
{
    MeasureXQueueData_t measureXQueueData;
    
    measureXQueueData.stateMeasureX = MEASURE_X_RUN;
    measureXQueueData.pluginRef = pluginRef;
    xQueueSend( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
}


// Stop measure plugin
void StopMeasurePlugin( void )
{
    MeasureXQueueData_t measureXQueueData;
    
    measureXQueueData.stateMeasureX = MEASURE_X_STOP;
    measureXQueueData.pluginRef = pluginRef;
    xQueueSendToFront( xQueue_MeasureX_Rx, &measureXQueueData, NULL ); 
}


// Error handler from the measure plugin
void MeasurePluginError( void )
{
    MeasurePlannerQueueData_t measurePlannerQueueData;

    measurePlannerQueueData.stateMeasurePlanner = MEASURE_PLANNER_PLUGIN_ERROR;            
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, NULL ); 
}
/* End of file */
