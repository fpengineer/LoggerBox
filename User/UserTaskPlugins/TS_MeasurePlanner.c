/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Measure Planner

*******************************************************************************************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "TS_queue.h"
#include "TS_task.h"

#include "HwAPI.h"

#include "defines.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

typedef enum {
    MEASURE_STOP,
    MEASURE_RUN
} MeasureStatus_t;

TaskHandle_t xTask_MeasurePlanner;
TaskHandle_t xTask_MeasurePlugin;

QueueHandle_t xQueue_MeasurePlanner_Rx;
QueueHandle_t xQueue_MeasurePlugin_Rx;
QueueHandle_t xQueue_MeasurePlugin_Tx;

extern const char *pluginsList[ 20 ];

// Declare private functions
static void LoadMeasurePlugin( void );
static void UnloadMeasurePlugin( void );
static void RunMeasurePlugin( void );
static void StopMeasurePlugin( void );

static void SendPluginsList( void );

static void SetSystemDefault( void );

// Declare private variables
static char tempString[450] = {""}; 
static char pluginName[50] = {""}; 
static char pluginFileName[100] = {""}; 


void vTask_MeasurePlanner( void *pvParameters )
{
    MeasurePlannerQueueData_t measurePlannerQueueData;

    HwBootData_t hwBootData = { HW_BOOT_IDLE, "" };
    MeasureStatus_t measureStatus = MEASURE_STOP;

    xQueue_MeasurePlanner_Rx = xQueueCreate( 5, sizeof( MeasurePlannerQueueData_t ) );

    measurePlannerQueueData.stateMeasurePlanner = MEASURE_PLANNER_INIT;            
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, NULL ); 

    while ( 1 )
	{
        xQueueReceive( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, portMAX_DELAY );

        switch ( measurePlannerQueueData.stateMeasurePlanner )
        {
            case MEASURE_PLANNER_INIT:
            {
                // Wait for HwBoot result
                while ( hwBootData.hwBootStatus == HW_BOOT_IN_PROGRESS ||
                        hwBootData.hwBootStatus == HW_BOOT_IDLE )
                {
                    hwBootData = HwAPI_Boot_GetStatus();
                }
                    
                if ( hwBootData.hwBootStatus == HW_BOOT_SUCCESS )
                {
                    // Start measure plugin loader
                    // Send to terminal list of plugins - created by a programmer *pluginsList[]
                    SendPluginsList();
                        
                    // Get FatFs status
                    if ( HwAPI_FatFs_GetStatus() == FATFS_OK )
                    {
                        // Load measure plugin
                        LoadMeasurePlugin();
                    }
                    break;
                }
                else
                {
                    // Error!
                    // Hardware boot failed
                    HwAPI_Terminal_SendMessage( "Error!\n"
                                                "Hardware boot failed. Please restart the system.\n" );
                }
                
            }
                
            case MEASURE_PLANNER_SD_CARD_INSERT:
            {
                measureStatus = MEASURE_STOP;

                // Check SD card initialization
                if ( HwAPI_FatFs_GetStatus() == FATFS_OK )
                {
                    // Load measure plugin
                    LoadMeasurePlugin();
                }
                break;
            }

            case MEASURE_PLANNER_SD_CARD_REMOVE:
            {
                measureStatus = MEASURE_STOP;
                
                // Send stop command to measure plugin
                StopMeasurePlugin();
                
                // Unload measure plugin
                UnloadMeasurePlugin();
                
                // Set system to default state
                SetSystemDefault();
                break;
            }

            case MEASURE_PLANNER_RUN_BUTTON_PRESSED:
            {
                switch ( measureStatus )
                {
                    case MEASURE_STOP:
                    {    
                        measureStatus = MEASURE_RUN;
                        // Send run command to measure plugin
                        RunMeasurePlugin();
                        break;
                    }
    
                    case MEASURE_RUN:
                    {
                        measureStatus = MEASURE_STOP;
                        // Send stop command to measure plugin
                        StopMeasurePlugin();

                        // Set system to default state
                        SetSystemDefault();
                        break;
                    }
        
                    default:
                        break;
                }
                break;
            }

            case MEASURE_PLANNER_GET_TYPE:
            {
                  
                break;
            }

            case MEASURE_PLANNER_RUN_MEASURE_TASK:
            {
                    
                break;
            }
                
            case MEASURE_PLANNER_STOP_MEASURE_TASK:
            {
                    
                break;
            }
                
            case MEASURE_PLANNER_IDLE:
            {
                    
                break;
            }
                
            default:
                break;
        }
    }
}


// SD card event callback
void SDCardDetect_Event( SDCardDetectStatus_t sdCardDetectStatus )
{
    QueueHandle_t xQueue_MeasurePlanner_Rx;
    MeasurePlannerQueueData_t measurePlannerQueueData;

    switch ( sdCardDetectStatus )
    {
        case SD_CARD_INSERT:
        {    
            measurePlannerQueueData.stateMeasurePlanner = MEASURE_PLANNER_SD_CARD_INSERT;            
            break;
        }
    
        case SD_CARD_REMOVE:
        {
            measurePlannerQueueData.stateMeasurePlanner = MEASURE_PLANNER_SD_CARD_REMOVE;            
            break;
    	}
        
        default:
            break;
    }
    
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, NULL ); 
}


// Run button event callback
void RunButton_Event( void )
{
    QueueHandle_t xQueue_MeasurePlanner_Rx;
    MeasurePlannerQueueData_t measurePlannerQueueData;
    
    measurePlannerQueueData.stateMeasurePlanner = MEASURE_PLANNER_RUN_BUTTON_PRESSED;            
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, NULL ); 
}



//*************************************************
//
// Private function
//
// Load measure plugin
//
//*************************************************
static void LoadMeasurePlugin( void )
{
    int32_t i = 0;                
    int32_t flagUpdateSystemTime = 0;
    FatFsStatus_t fatFsStatus = FATFS_OK;
                    
    // Check if config.ini exist
    fatFsStatus = HwAPI_FatFs_CheckFileExist( "config.ini" );
    switch ( fatFsStatus )
    {
        case FATFS_OK:
        {
            // Check system time settings
            HwAPI_SystemTime_ProcessConfig( &flagUpdateSystemTime, tempString );
            if ( flagUpdateSystemTime == UPDATE_SYSTEM_TIME_ENABLE )
            {
                sprintf( tempString, "System time updated: %s\n", tempString );
                HwAPI_Terminal_SendMessage( tempString );
            }
            else
            {
                sprintf( tempString, "System time: %s\n", tempString );
                HwAPI_Terminal_SendMessage( tempString );
            }
     
            // Get name of the plugin
            HwAPI_Terminal_SendMessage( "Get NameIC from config.ini\n" );
            fatFsStatus = HwAPI_FatFs_INI_GetKeyString( "SelectIC", "NameIC", "config.ini", pluginName );
            switch ( fatFsStatus )
            {
                case FATFS_OK:
                {
                    sprintf( tempString, "NameIC: %s\n", pluginName );
                    HwAPI_Terminal_SendMessage( tempString );
     
                    // Check if plugin exist
                    for ( i = 0; i < sizeof( pluginsList ) / sizeof( pluginsList[ 0 ] ); i++ )
                    {
                        if ( strcmp( pluginsList[ i ], pluginName ) == 0 )
                        {
                            // Create filename of the measure plan file
                            sprintf( pluginFileName, "MeasurePlan_%s.ini", pluginName );
       
                            // Check if measure plan file exist
                            fatFsStatus = HwAPI_FatFs_CheckFileExist( pluginFileName );
                            switch ( fatFsStatus )
                            {
                                case FATFS_OK:
                                {
                                    // Load selected plugin
                                    /*
                                    if( pdTRUE != xTaskCreate(  pluginsPointerList[ i ],
                                                                "Task - Measure Plugin",
                                                                configMINIMAL_STACK_SIZE + 5000,
                                                                NULL,
                                                                tskIDLE_PRIORITY + 1,
                                                                &xTask_MeasurePlugin ) ) { ERROR_ACTION(TASK_NOT_CREATE,0); }	

                                    xQueue_MeasurePlugin_Rx = xQueueCreate( 5, sizeof( MeasurePlannerQueueData_t ) );
                                    xQueue_MeasurePlugin_Tx = xQueueCreate( 5, sizeof( MeasurePlannerQueueData_t ) );
                                    */
                                    break;
                                }
       
                                case FATFS_ERROR_FILE_NOT_FOUND:
                                {  
                                    sprintf( tempString, "Error!\n"
                                                         "file %s not found!\n", pluginFileName );
                                    HwAPI_Terminal_SendMessage( tempString );
                                    break;
                                }
        
                                default:
                                {
                                    sprintf( tempString, "Error!\n"
                                                         "fatFsStatus = %d\n", fatFsStatus );
                                    HwAPI_Terminal_SendMessage( tempString );
                                    break;
                                }
                            }
                            break;	
                        }
                    }
                    break;
                }
       
                case FATFS_ERROR_INI_KEY_NOT_FOUND:
                case FATFS_ERROR_INI_SECTION_NOT_FOUND:
                { 
                    sprintf( tempString, "Error!\n"
                                         "Section [SelectIC] or key NameIC not found in the file config.ini!\n" );
                    HwAPI_Terminal_SendMessage( tempString );
                    break;
                }
        
                case FATFS_ERROR_FILE_NOT_FOUND:
                { 
                    sprintf( tempString, "Error!\n"
                                         "File config.ini not found!\n" );
                    HwAPI_Terminal_SendMessage( tempString );
                    break;
                }
        
                default:
                {
                    sprintf( tempString, "Error!\n"
                                         "fatFsStatus = %d\n", fatFsStatus );
                    HwAPI_Terminal_SendMessage( tempString );
                    break;
                }
            }
            break;
        }

        case FATFS_ERROR_FILE_NOT_FOUND:
        {
            sprintf( tempString, "Error!\n"
                                 "file config.ini not found!\n" );
            HwAPI_Terminal_SendMessage( tempString );
            break;
        }
        
        default:
            break;
    }
}



//*************************************************
//
// Private function
//
// Unload measure plugin
//
//*************************************************
static void UnloadMeasurePlugin( void )
{
    vTaskDelete( xTask_MeasurePlugin );
    vQueueDelete( xQueue_MeasurePlugin_Rx );
    vQueueDelete( xQueue_MeasurePlugin_Tx );
}



//*************************************************
//
// Private function
//
// Run measure plugin
//
//*************************************************
static void RunMeasurePlugin( void )
{
    extern QueueHandle_t xQueue_MeasurePlugin_Rx;
    MeasurePluginQueueData_t measurePluginQueueData;
    
    measurePluginQueueData.stateMeasurePlugin = MEASURE_PLUGIN_RUN;
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePluginQueueData, NULL ); 
}



//*************************************************
//
// Private function
//
// Stop measure plugin
//
//*************************************************
static void StopMeasurePlugin( void )
{
    extern QueueHandle_t xQueue_MeasurePlugin_Rx;
    MeasurePluginQueueData_t measurePluginQueueData;
    
    measurePluginQueueData.stateMeasurePlugin = MEASURE_PLUGIN_STOP;
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePluginQueueData, NULL ); 
}



//*************************************************
//
// Private function
//
// Load measure plugin
//
//*************************************************
static void SendPluginsList( void )
{
    int32_t i = 0;
    
    HwAPI_Terminal_SendMessage( "List of supported ICs:\n" );
    for ( i = 0; i < sizeof( pluginsList )/sizeof( pluginsList[ 0 ] ); i++ )
    {
        sprintf( tempString, "%s\n", pluginsList[ i ] );
        HwAPI_Terminal_SendMessage( tempString );
    }
}



//*************************************************
//
// Private function
//
// Set system to dafault state
//
//*************************************************
static void SetSystemDefault( void )
{

}
/* End of file */
