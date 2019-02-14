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
#include "PluginsDef.h"
#include "MeasurePlanner Utils.h"


TaskHandle_t xTask_MeasurePlanner;
TaskHandle_t xTask_MeasurePlugin;

QueueHandle_t xQueue_MeasurePlanner_Rx;
QueueHandle_t xQueue_MeasurePlugin_Rx;
QueueHandle_t xQueue_MeasurePlugin_Tx;

// Declare private variables
static char tempString[450] = {""}; 


void vTask_MeasurePlanner( void *pvParameters )
{
    MeasurePlannerQueueData_t measurePlannerQueueData;

    HwBootData_t hwBootData = { HW_BOOT_IDLE, "" };
    MeasureStatus_t measureStatus = MEASURE_STOP;

    ConfigData_t configData = { "", "", 0 };
    uint32_t flagPluginReady = 0;
    
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
                do
                {
                    hwBootData = HwAPI_Boot_GetStatus();
                } while ( hwBootData.hwBootStatus == HW_BOOT_IN_PROGRESS ||
                          hwBootData.hwBootStatus == HW_BOOT_IDLE );
                    
                if ( hwBootData.hwBootStatus == HW_BOOT_SUCCESS )
                {
                    flagPluginReady = 0;

                    HwAPI_Terminal_SendMessage( "TS_HwBoot - OK.\n"
                                                "TS_MeasurePlanner - OK.\n" );
                    
                    // Start measure plugin loader
                    HwAPI_Terminal_SendMessage( "***********   LoggerBox   UF113.887   " SYSTEM_VERSION "   ***********\n\n" );

                    // Get current system time
                    HwAPI_SystemTime_Get( configData.systemTimeString );
                    sprintf( tempString, "Current system time: %s\n\n", configData.systemTimeString );
                    HwAPI_Terminal_SendMessage( tempString );
                    
                    // Send to terminal list of plugins - created by a programmer in the *pluginsList[]
                    SendPluginsList();
                        
                    // Check FatFs status to load plugins
                    switch ( HwAPI_FatFs_GetStatus() )
                    {
                        case FATFS_OK:
                        {
                            int32_t pluginIndex = 0;
                            
                            // Read 'config.ini'
                            if ( ReadConfigFile( &configData, "config.ini" ) )
                            {
                                // Process SystemTime settings
                                ProcessSystemTimeConfig( configData.systemTimeString, configData.updateSystemTime );
                            
                                // Find measure plugin
                                pluginIndex = FindMeasurePlugin( configData.nameIC );
                                if ( pluginIndex >= 0 )
                                {
                                    // Check measure plan file exist
                                    if ( CheckMeasurePlanFile( configData.nameIC ) )
                                    {
                                        // Load measure plugin
                                        LoadMeasurePlugin( pluginIndex );
                                        flagPluginReady = 1;
                                    }
                                }
                            }
                            break;
                        }
                        
                        case FATFS_ERROR_NO_SD_CARD:
                        {
                            HwAPI_Terminal_SendMessage( "SD card not inserted! Please insert SD card.\n" );
                            flagPluginReady = 0;
                        }

                        default:
                            break;
                    }
                    HwAPI_StatusLED_On();
                }
                else
                {
                    // Error!
                    // Hardware boot failed
                    HwAPI_Terminal_SendMessage( "Error!\n"
                                                "Hardware boot failed. Please restart the system.\n" );
                    HwAPI_StatusLED_Flash( STATUS_LED_FLASH_FAST );
                }
                break;
            }
            
            case MEASURE_PLANNER_SD_CARD_INSERT:
            {
                flagPluginReady = 0;

                measureStatus = MEASURE_STOP;
                HwAPI_Terminal_SendMessage( "MeasurePlanner. SD card inserted.\n" );

                HwAPI_FatFs_InitSDCard();
                
                // Check SD card initialization
                if ( HwAPI_FatFs_GetStatus() == FATFS_OK )
                {
                    int32_t pluginIndex = 0;
                            
                    // Read 'config.ini'
                    if ( ReadConfigFile( &configData, "config.ini" ) )
                    {
                        // Process SystemTime settings
                        ProcessSystemTimeConfig( configData.systemTimeString, configData.updateSystemTime );
                            
                        // Find measure plugin
                        pluginIndex = FindMeasurePlugin( configData.nameIC );
                        if ( pluginIndex >= 0 )
                        {
                            // Check measure plan file exist
                            if ( CheckMeasurePlanFile( configData.nameIC ) )
                            {
                                // Load measure plugin
                                LoadMeasurePlugin( pluginIndex );
                                flagPluginReady = 1;
                            }
                        }
                    }
                }
                HwAPI_StatusLED_On();
                break;
            }

            case MEASURE_PLANNER_SD_CARD_REMOVE:
            {
                measureStatus = MEASURE_STOP;
                HwAPI_Terminal_SendMessage( "MeasurePlanner. SD card removed.\n" );

                HwAPI_FatFs_DeinitSDCard();

                if ( flagPluginReady )
                {
                    // Send stop command to measure plugin
                    StopMeasurePlugin();
                
                    // Unload measure plugin
                    UnloadMeasurePlugin();
                }
                flagPluginReady = 0;

                // Set system to default state
                SetSystemDefault();
                HwAPI_StatusLED_On();
                break;
            }

            case MEASURE_PLANNER_RUN_BUTTON_PRESSED:
            {
                //HwAPI_Terminal_SendMessage( "MeasurePlanner. MEASURE_PLANNER_RUN_BUTTON_PRESSED\n" );
                if ( flagPluginReady )
                {
                    switch ( measureStatus )
                    {
                        case MEASURE_STOP:
                        {       
                            measureStatus = MEASURE_RUN;
                               
                            // Send run command to measure plugin
                            RunMeasurePlugin();
                            HwAPI_StatusLED_Flash( STATUS_LED_FLASH_SLOW );
                            break;
                        }
    
                        case MEASURE_RUN:
                        {
                            measureStatus = MEASURE_STOP;
                        
                            // Send stop command to measure plugin
                            StopMeasurePlugin();

                            // Set system to default state
                            SetSystemDefault();

                            HwAPI_StatusLED_On();
                            break;
                        }
        
                        default:
                            break;
                    }
                }
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
    MeasurePlannerQueueData_t measurePlannerQueueData;

    //HwAPI_Terminal_SendMessage( "MeasurePlanner SD card event callback.\n" );

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
    MeasurePlannerQueueData_t measurePlannerQueueData;
    
    //HwAPI_Terminal_SendMessage( "MeasurePlanner. Run button event\n" );

    measurePlannerQueueData.stateMeasurePlanner = MEASURE_PLANNER_RUN_BUTTON_PRESSED;            
    xQueueSend( xQueue_MeasurePlanner_Rx, &measurePlannerQueueData, NULL ); 

}

/* End of file */