/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Plugin ConverterI7 - IC5 - V1.0
    
*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>

#include "ConverterI7_IC5_V1_0\ConverterI7_IC5_V1_0.h"


// Declare private functions
static PluginResult_t GetConfigData( CfgMeasurePlan_ConverterI7_IC5_V1_0_t *cfgMeasurePlan,
                                     CfgMeasureEnable_ConverterI7_IC5_V1_0_t *cfgMeasureEnable,
                                     CfgDatafileSettings_ConverterI7_IC5_V1_0_t *cfgDatafileSettings );

// Declare private variables

void ConverterI7_IC5_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    char measureDataFilename[ MEASURE_DATA_FILENAME_SIZE ];
    CfgMeasurePlan_ConverterI7_IC5_V1_0_t cfgMeasurePlan = INIT_CFG_MEASURE_PLAN_STRUCT;
    CfgMeasureEnable_ConverterI7_IC5_V1_0_t cfgMeasureEnable = INIT_CFG_MEASURE_ENABLE_STRUCT;
    CfgDatafileSettings_ConverterI7_IC5_V1_0_t cfgDatafileSettings = INIT_CFG_DATAFILE_SETTINGS_STRUCT;
        
    switch ( pluginCommand )
    {
        case CMD_PLUGIN_RUN:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Run\n" );
#endif
            /* Read plugin config file */
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Start reading of measure plan file\n" );
            *pluginResult = GetConfigData( &cfgMeasurePlan, &cfgMeasureEnable, &cfgDatafileSettings );
            if ( !pluginResult->error )
            {
                /* Create a new measurement file */
                if ( cfgDatafileSettings.enableDatafile )
                {
                    HwAPI_SystemTime_Get( pluginsTempString, GetSizeof_pluginsTempString() );
                    PrepareTimeString( pluginsTempString );
                    snprintf( measureDataFilename, sizeof( measureDataFilename ), "measure/"PLUGIN_4_NAME"/%s_%s.csv", cfgDatafileSettings.prefixDatafileName, pluginsTempString );
                    
                    snprintf( pluginsTempString, GetSizeof_pluginsTempString(), "Create '%s' file.\n", measureDataFilename );
                    HwAPI_Terminal_SendMessage( pluginsTempString );
                    
                    HwAPI_FatFs_CreateFile( measureDataFilename, 0 );

                    /* Open the measurement file */
                    HwAPI_FatFs_OpenFile( measureDataFilename, 0 );
                    snprintf( pluginsTempString, GetSizeof_pluginsTempString(),         
                              "\n[MeasurePlan]\n"                               
                              "BaseTactLength_s = %d\n"                           
                              "SourceG1_V = %.3f\n"                           
                              "SourceG2_V = %.3f\n"                           
                              "SourceG3_V = %.3f\n"                           
                              "SourceG4_V = %.3f\n",                           
                              cfgMeasurePlan.BaseTactLength_s,
                              cfgMeasurePlan.SourceG1_V,
                              cfgMeasurePlan.SourceG2_V,
                              cfgMeasurePlan.SourceG3_V,
                              cfgMeasurePlan.SourceG4_V );
                    HwAPI_FatFs_WriteTextFile( pluginsTempString, measureDataFilename, 0 );
                    HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - measure data file created\n" );
                }
                
                /* Initialize (prepare) the system for measure*/
                //HwAPI_Relay_ClearAll();
                //HwAPI_VoltageSource_ClearAll();
                
                /* Set up tact state (if needed) */
                /* Return tac length in ms */
                *tactLength_ms = cfgMeasurePlan.BaseTactLength_s * 1000;
            }
            break;
        }

        case CMD_PLUGIN_STOP:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Stop\n" );
#endif
            /* Clear all sources */
            /* Clear all relays */
            /* Close the measurement file */
            HwAPI_FatFs_CloseFile( measureDataFilename, 0 );

            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_TACT:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Tact\n" );
#endif
            /* Initialize variables for a new measure */
            /* Measure enabled parameters */
            /* Create string with measured parameters */
            /* Send string with measured parameters to terminal */
            /* Write data to measurement file */
            /* Enable/disable relays if needed */




            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_ERROR:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Error\n" );
#endif

            break;
        }

        case CMD_PLUGIN_IDLE:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Idle\n" );
#endif
            
            break;
        }

        default:
            break;
    }
}


//*************************************************
//
// Plugin private function
//
// Get config data from measure plan file
//
//*************************************************
static PluginResult_t GetConfigData( CfgMeasurePlan_ConverterI7_IC5_V1_0_t *cfgMeasurePlan,
                                     CfgMeasureEnable_ConverterI7_IC5_V1_0_t *cfgMeasureEnable,
                                     CfgDatafileSettings_ConverterI7_IC5_V1_0_t *cfgDatafileSettings )
{
    PluginResult_t pluginResult = { 0, 0, "" };
    
    /* Create filename for the config plan file */
    snprintf( measurePlanFilename, GetSizeof_measurePlanFilename(), "MeasurePlan_"PLUGIN_4_NAME".ini" );

        
    if ( FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasurePlan", "BaseTactLength_s", measurePlanFilename, &cfgMeasurePlan->BaseTactLength_s, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyFloat( "MeasurePlan", "SourceG1_V", measurePlanFilename, &cfgMeasurePlan->SourceG1_V, MEASURE_PLAN_FILE ) || 
         FATFS_OK != HwAPI_FatFs_INI_GetKeyFloat( "MeasurePlan", "SourceG2_V", measurePlanFilename, &cfgMeasurePlan->SourceG2_V, MEASURE_PLAN_FILE ) || 
         FATFS_OK != HwAPI_FatFs_INI_GetKeyFloat( "MeasurePlan", "SourceG3_V", measurePlanFilename, &cfgMeasurePlan->SourceG3_V, MEASURE_PLAN_FILE ) || 
         FATFS_OK != HwAPI_FatFs_INI_GetKeyFloat( "MeasurePlan", "SourceG4_V", measurePlanFilename, &cfgMeasurePlan->SourceG4_V, MEASURE_PLAN_FILE ) || 
    
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG1_V", measurePlanFilename, &cfgMeasureEnable->enableG1_V, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG2_V", measurePlanFilename, &cfgMeasureEnable->enableG2_V, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG3_V", measurePlanFilename, &cfgMeasureEnable->enableG3_V, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG4_V", measurePlanFilename, &cfgMeasureEnable->enableG4_V, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG1_I", measurePlanFilename, &cfgMeasureEnable->enableG1_I, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG2_I", measurePlanFilename, &cfgMeasureEnable->enableG2_I, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG3_I", measurePlanFilename, &cfgMeasureEnable->enableG3_I, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableG4_I", measurePlanFilename, &cfgMeasureEnable->enableG4_I, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC1_Vout", measurePlanFilename, &cfgMeasureEnable->enableIC1_Vout, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC2_Vout", measurePlanFilename, &cfgMeasureEnable->enableIC2_Vout, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC3_Vout", measurePlanFilename, &cfgMeasureEnable->enableIC3_Vout, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC4_Vout", measurePlanFilename, &cfgMeasureEnable->enableIC4_Vout, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC1_Freq_PWM", measurePlanFilename, &cfgMeasureEnable->enableIC1_Freq_PWM, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC2_Freq_PWM", measurePlanFilename, &cfgMeasureEnable->enableIC2_Freq_PWM, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC3_Freq_PWM", measurePlanFilename, &cfgMeasureEnable->enableIC3_Freq_PWM, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC4_Freq_PWM", measurePlanFilename, &cfgMeasureEnable->enableIC4_Freq_PWM, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC1_Temperature", measurePlanFilename, &cfgMeasureEnable->enableIC1_Temperature, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC2_Temperature", measurePlanFilename, &cfgMeasureEnable->enableIC2_Temperature, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC3_Temperature", measurePlanFilename, &cfgMeasureEnable->enableIC3_Temperature, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "MeasureEnable", "EnableIC4_Temperature", measurePlanFilename, &cfgMeasureEnable->enableIC4_Temperature, MEASURE_PLAN_FILE ) ||
         
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "DatafileSettings", "EnableDatafile", measurePlanFilename, &cfgDatafileSettings->enableDatafile, MEASURE_PLAN_FILE ) || 
         FATFS_OK != HwAPI_FatFs_INI_GetKeyString( "DatafileSettings", "PrefixDatafileName", measurePlanFilename, cfgDatafileSettings->prefixDatafileName, MEASURE_PLAN_FILE ) || 
         FATFS_OK != HwAPI_FatFs_INI_GetKeyInt( "DatafileSettings", "StringsToWrite", measurePlanFilename, ( int32_t *)&cfgDatafileSettings->stringsToWrite, MEASURE_PLAN_FILE ) ||
         FATFS_OK != HwAPI_FatFs_INI_GetKeyString( "DatafileSettings", "Delimiter", measurePlanFilename, cfgDatafileSettings->delimiter, MEASURE_PLAN_FILE ) )
    {
        /* Create error message and return */
        HwAPI_Terminal_SendMessage( "Measure plan file of the plugin "PLUGIN_4_NAME" read - Error.\n" );
        pluginResult.error = 1;
        pluginResult.errorCode = PLG_ERR_READ_MEASURE_PLAN_FILE;
        snprintf( pluginResult.message, sizeof( pluginResult.message ), "Plugin "PLUGIN_4_NAME". Error comes during reading of measure plan file.\n" );
        return pluginResult;
    }
         
    /* Send readed values to terminal */     
    HwAPI_Terminal_SendMessage( "Measure plan file of the plugin "PLUGIN_4_NAME" read - Success.\n" );
    snprintf( pluginsTempString, GetSizeof_pluginsTempString(),         
              "\n[MeasurePlan]\n"                               
              "BaseTactLength_s = %d\n"                           
              "SourceG1_V = %.3f\n"                           
              "SourceG2_V = %.3f\n"                           
              "SourceG3_V = %.3f\n"                           
              "SourceG4_V = %.3f\n"                           
              "\n[MeasureEnable]\n"                               
              "EnableG1_V = %d\n"          
              "EnableG2_V = %d\n"          
              "EnableG3_V = %d\n"          
              "EnableG4_V = %d\n"          
              "EnableG1_I = %d\n"          
              "EnableG2_I = %d\n"          
              "EnableG3_I = %d\n"          
              "EnableG4_I = %d\n"          
              "EnableIC1_Vout = %d\n"          
              "EnableIC2_Vout = %d\n"          
              "EnableIC3_Vout = %d\n"          
              "EnableIC4_Vout = %d\n"          
              "EnableIC1_Freq_PWMout = %d\n"          
              "EnableIC2_Freq_PWMout = %d\n"          
              "EnableIC3_Freq_PWMout = %d\n"          
              "EnableIC4_Freq_PWMout = %d\n"          
              "EnableIC1_Temperatureout = %d\n"          
              "EnableIC2_Temperatureout = %d\n"          
              "EnableIC3_Temperatureout = %d\n"          
              "EnableIC4_Temperatureout = %d\n"          
              "\n[DatafileSettings]\n"                               
              "EnableDatafile = %d\n" 
              "PrefixDatafileName = %s\n" 
              "StringsToWrite = %d\n"
              "Delimiter = %s\n",
              cfgMeasurePlan->BaseTactLength_s,
              cfgMeasurePlan->SourceG1_V,
              cfgMeasurePlan->SourceG2_V,
              cfgMeasurePlan->SourceG3_V,
              cfgMeasurePlan->SourceG4_V,
              cfgMeasureEnable->enableG1_V,
              cfgMeasureEnable->enableG2_V,
              cfgMeasureEnable->enableG3_V,
              cfgMeasureEnable->enableG4_V,
              cfgMeasureEnable->enableG1_I,
              cfgMeasureEnable->enableG2_I,
              cfgMeasureEnable->enableG3_I,
              cfgMeasureEnable->enableG4_I,
              cfgMeasureEnable->enableIC1_Vout,
              cfgMeasureEnable->enableIC2_Vout,
              cfgMeasureEnable->enableIC3_Vout,
              cfgMeasureEnable->enableIC4_Vout,
              cfgMeasureEnable->enableIC1_Freq_PWM,
              cfgMeasureEnable->enableIC2_Freq_PWM,
              cfgMeasureEnable->enableIC3_Freq_PWM,
              cfgMeasureEnable->enableIC4_Freq_PWM,
              cfgMeasureEnable->enableIC1_Temperature,
              cfgMeasureEnable->enableIC2_Temperature,
              cfgMeasureEnable->enableIC3_Temperature,
              cfgMeasureEnable->enableIC4_Temperature,
              cfgDatafileSettings->enableDatafile,
              cfgDatafileSettings->prefixDatafileName,
              cfgDatafileSettings->stringsToWrite,
              cfgDatafileSettings->delimiter );
    HwAPI_Terminal_SendMessage( pluginsTempString );
    
    return pluginResult;
}




/* End of file */
