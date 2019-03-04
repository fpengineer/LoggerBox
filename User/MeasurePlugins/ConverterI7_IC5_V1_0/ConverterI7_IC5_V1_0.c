/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Plugin ConverterI7 - IC5 - V1.0
    
*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>

#include "ConverterI7_IC5_V1_0\ConverterI7_IC5_V1_0.h"
#include "ConverterI7_IC5_V1_0\types.h"
#include "ConverterI7_IC5_V1_0\defs.h"


// Declare private functions
static PluginResult_t GetConfigData( CfgMeasurePlan_t *cfgMeasurePlan,
                                     CfgMeasureEnable_t *cfgMeasureEnable,
                                     CfgDatafileSettings_t *cfgDatafileSettings );
static void CreateHeaderString( char *string, int32_t stringSize, CfgMeasureEnable_t *cfgMeasureEnable, char *delimiter );
static void CreateMeasureString( char *string, int32_t stringSize, MeasureValues_t *measureValues, CfgMeasureEnable_t *cfgMeasureEnable, char *delimiter );

// Declare private variables

void ConverterI7_IC5_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    static char measureDataFilename[ MEASURE_DATA_FILENAME_SIZE ];
    static CfgMeasurePlan_t cfgMeasurePlan = INIT_CFG_MEASURE_PLAN_STRUCT;
    static CfgMeasureEnable_t cfgMeasureEnable = INIT_CFG_MEASURE_ENABLE_STRUCT;
    static CfgDatafileSettings_t cfgDatafileSettings = INIT_CFG_DATAFILE_SETTINGS_STRUCT;
    
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
                    
                    /* Create measure conditions */
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
                    PluginDelay_ms( 100 ); // delay to avoid a race condition while writing current 'pluginsTempString'

                    /* Create header string to write to the file */
                    CreateHeaderString( pluginsTempString, GetSizeof_pluginsTempString(), &cfgMeasureEnable, cfgDatafileSettings.delimiter );
                    HwAPI_FatFs_WriteTextFile( pluginsTempString, measureDataFilename, 0 );
                    HwAPI_FatFs_CloseFile( measureDataFilename, 0 );
                    PluginDelay_ms( 100 ); // delay to avoid a race condition while writing current 'pluginsTempString'
                    
                    HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - measure data file created\n" );

                }
                
                /* Create header string to send to terminal */
                CreateHeaderString( pluginsTempString, GetSizeof_pluginsTempString(), &cfgMeasureEnable, "\t" );
                HwAPI_Terminal_SendMessage( pluginsTempString );
                HwAPI_Terminal_SendMessage( "\n" );

                /* Initialize (prepare) the system for measure*/
                HwAPI_Relay_ClearAll();
                HwAPI_VoltageSource_ClearAll();
                HwAPI_VoltageSource_Set( NSOURCE_1, cfgMeasurePlan.SourceG1_V );
                HwAPI_VoltageSource_Set( NSOURCE_2, cfgMeasurePlan.SourceG2_V );
                HwAPI_VoltageSource_Set( NSOURCE_3, cfgMeasurePlan.SourceG3_V );
                HwAPI_VoltageSource_Set( NSOURCE_4, cfgMeasurePlan.SourceG4_V );
                
                /* Set up tact state (if needed) */
                /* Return tact length in ms */
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
            HwAPI_VoltageSource_ClearAll();
            
            /* Clear all relays */
            HwAPI_Relay_ClearAll();
            

            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_TACT:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Tact\n" );
#endif
            /* Initialize variables for a new measure */
            MeasureValues_t measureValues = INIT_MEASURE_VALUES_STRUCT;
            
            /* Measure enabled parameters */
            if ( cfgMeasureEnable.enableG1_V )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC1, ADC_SOURCE_Gn_V );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG1_V, ADC_RANGE_Gn_V, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG2_V )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC2, ADC_SOURCE_Gn_V );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG2_V, ADC_RANGE_Gn_V, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG3_V )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC3, ADC_SOURCE_Gn_V );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG3_V, ADC_RANGE_Gn_V, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG4_V )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC4, ADC_SOURCE_Gn_V );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG4_V, ADC_RANGE_Gn_V, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG1_I )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC1, ADC_SOURCE_Gn_I );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG1_I, ADC_RANGE_Gn_I, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG2_I )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC2, ADC_SOURCE_Gn_I );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG2_I, ADC_RANGE_Gn_I, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG3_I )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC3, ADC_SOURCE_Gn_I );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG3_I, ADC_RANGE_Gn_I, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableG4_I )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC4, ADC_SOURCE_Gn_I );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueG4_I, ADC_RANGE_Gn_I, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableIC1_Vout )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC1, ADC_SOURCE_ICn_Vout );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueIC1_Vout, ADC_RANGE_ICn_Vout, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableIC2_Vout )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC2, ADC_SOURCE_ICn_Vout );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueIC2_Vout, ADC_RANGE_ICn_Vout, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableIC3_Vout )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC3, ADC_SOURCE_ICn_Vout );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueIC3_Vout, ADC_RANGE_ICn_Vout, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableIC4_Vout )
            {
                HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_IC4, ADC_SOURCE_ICn_Vout );
                HwAPI_DAQ_ADC_GetAveraged( &measureValues.valueIC4_Vout, ADC_RANGE_ICn_Vout, ADC_N_AVERAGES );
            }
            
            if ( cfgMeasureEnable.enableIC1_Freq_PWM )
            {
                HwAPI_DAQ_Frequency_GetSingle( FREQ_CHANNEL_IC1, &measureValues.valueIC1_PWM );
            }
            
            if ( cfgMeasureEnable.enableIC2_Freq_PWM )
            {
                HwAPI_DAQ_Frequency_GetSingle( FREQ_CHANNEL_IC2, &measureValues.valueIC2_PWM );
            }
            
            if ( cfgMeasureEnable.enableIC3_Freq_PWM )
            {
                HwAPI_DAQ_Frequency_GetSingle( FREQ_CHANNEL_IC3, &measureValues.valueIC3_PWM );
            }
            
            if ( cfgMeasureEnable.enableIC4_Freq_PWM )
            {
                HwAPI_DAQ_Frequency_GetSingle( FREQ_CHANNEL_IC4, &measureValues.valueIC4_PWM );
            }
            
            if ( cfgDatafileSettings.enableDatafile )
            {
                /* Create string with measured parameters to write to file */
                CreateMeasureString( pluginsTempString, GetSizeof_pluginsTempString(), &measureValues, &cfgMeasureEnable, cfgDatafileSettings.delimiter );
                snprintf( pluginsTempString, GetSizeof_pluginsTempString(), "%s\n", pluginsTempString );

                /* Write data to measurement file */
                HwAPI_FatFs_OpenFile( measureDataFilename, 0 );
                switch ( HwAPI_FatFs_WriteTextFile( pluginsTempString, measureDataFilename, 0 ) )
                {
                    case FATFS_OK:
                        HwAPI_FatFs_CloseFile( measureDataFilename, 0 );
                        PluginDelay_ms( 10 ); // delay to avoid a race condition while writing current 'pluginsTempString'
                        pluginResult->error = 0;
                        break;

                    case FATFS_ERROR_FILE_NOT_FOUND:
                        pluginResult->error = 1;
                        pluginResult->errorCode = PLG_ERR_NO_MEASURE_DATA_FILE;
                        sprintf( pluginResult->message, "Measure data file not found." );
                        break;

                    default:
                        pluginResult->error = 1;
                        pluginResult->errorCode = PLG_ERR_COMMON;
                        break;
                }
            }
            
            /* Create string with measured parameters to send to terminal */
            CreateMeasureString( pluginsTempString, GetSizeof_pluginsTempString(), &measureValues, &cfgMeasureEnable, "\t" );

            /* Send string to terminal */
            HwAPI_Terminal_SendMessage( pluginsTempString );
            int32_t fileSize = 0;
            HwAPI_FatFs_GetFileSize( &fileSize,  measureDataFilename, 0 );
            snprintf( pluginsTempString, GetSizeof_pluginsTempString(), "\tf_size = %.1f kB\n", (float)fileSize / 1024.0f ); 
            HwAPI_Terminal_SendMessage( pluginsTempString );
           
            /* Enable/disable relays if needed */
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
static PluginResult_t GetConfigData( CfgMeasurePlan_t *cfgMeasurePlan,
                                     CfgMeasureEnable_t *cfgMeasureEnable,
                                     CfgDatafileSettings_t *cfgDatafileSettings )
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
              "EnableIC1_Freq_PWM = %d\n"          
              "EnableIC2_Freq_PWM = %d\n"          
              "EnableIC3_Freq_PWM = %d\n"          
              "EnableIC4_Freq_PWM = %d\n"          
              "EnableIC1_Temperature = %d\n"          
              "EnableIC2_Temperature = %d\n"          
              "EnableIC3_Temperature = %d\n"          
              "EnableIC4_Temperature = %d\n"          
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


//*************************************************
//
// Plugin private function
//
// Create string with measured values
//
//*************************************************
static void CreateHeaderString( char *string, int32_t stringSize, CfgMeasureEnable_t *cfgMeasureEnable, char *delimiter )
{
    sprintf( string, "" );        

    if ( cfgMeasureEnable->enableG1_V )
    {
        snprintf( string, stringSize, "%sG1_V, V%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG2_V )
    {
        snprintf( string, stringSize, "%sG2_V, V%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG3_V )
    {
        snprintf( string, stringSize, "%sG3_V, V%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG4_V )
    {
        snprintf( string, stringSize, "%sG4_V, V%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG1_I )
    {
        snprintf( string, stringSize, "%sG1_I, mA%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG2_I )
    {
        snprintf( string, stringSize, "%sG2_I, mA%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG3_I )
    {
        snprintf( string, stringSize, "%sG3_I, mA%s", string, delimiter );        
    }
       
    if ( cfgMeasureEnable->enableG4_I )
    {
        snprintf( string, stringSize, "%sG4_I, mA%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC1_Vout )
    {
        snprintf( string, stringSize, "%sIC1_Vout, V%s", string, delimiter );        
    }
           
    if ( cfgMeasureEnable->enableIC2_Vout )
    {
        snprintf( string, stringSize, "%sIC2_Vout, V%s", string, delimiter );        
    }
           
    if ( cfgMeasureEnable->enableIC3_Vout )
    {
        snprintf( string, stringSize, "%sIC3_Vout, V%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC4_Vout )
    {
        snprintf( string, stringSize, "%sIC4_Vout, V%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC1_Freq_PWM )
    {
        snprintf( string, stringSize, "%sIC1_Freq, kHz%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC1_PulseHigh, ns%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC1_PulseLow, ns%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC2_Freq_PWM )
    {
        snprintf( string, stringSize, "%sIC2_Freq, kHz%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC2_PulseHigh, ns%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC2_PulseLow, ns%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC3_Freq_PWM )
    {
        snprintf( string, stringSize, "%sIC3_Freq, kHz%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC3_PulseHigh, ns%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC3_PulseLow, ns%s", string, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC4_Freq_PWM )
    {
        snprintf( string, stringSize, "%sIC4_Freq, kHz%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC4_PulseHigh, ns%s", string, delimiter );        
        snprintf( string, stringSize, "%sIC4_PulseLow, ns%s", string, delimiter );        
    }

    snprintf( string, stringSize, "%s\n", string );       
}


//*************************************************
//
// Plugin private function
//
// Create string with measured values
//
//*************************************************
static void CreateMeasureString( char *string, int32_t stringSize, MeasureValues_t *measureValues, CfgMeasureEnable_t *cfgMeasureEnable, char *delimiter )
{
    char timeString[ 30 ] = { "" };

    sprintf( string, "" );        

    if ( cfgMeasureEnable->enableG1_V )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG1_V, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG2_V )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG2_V, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG3_V )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG3_V, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG4_V )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG4_V, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG1_I )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG4_I, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG2_I )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG4_I, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableG3_I )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG4_I, delimiter );        
    }
       
    if ( cfgMeasureEnable->enableG4_I )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueG4_I, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC1_Vout )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueIC1_Vout, delimiter );        
    }
           
    if ( cfgMeasureEnable->enableIC2_Vout )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueIC2_Vout, delimiter );        
    }
           
    if ( cfgMeasureEnable->enableIC3_Vout )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueIC3_Vout, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC4_Vout )
    {
        snprintf( string, stringSize, "%s%.3f%s", string, measureValues->valueIC4_Vout, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC1_Freq_PWM )
    {
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC1_PWM.frequency_kHz, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC1_PWM.pulseHigh_ns, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC1_PWM.pulseLow_ns, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC2_Freq_PWM )
    {
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC2_PWM.frequency_kHz, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC2_PWM.pulseHigh_ns, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC2_PWM.pulseLow_ns, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC3_Freq_PWM )
    {
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC3_PWM.frequency_kHz, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC3_PWM.pulseHigh_ns, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC3_PWM.pulseLow_ns, delimiter );        
    }
            
    if ( cfgMeasureEnable->enableIC4_Freq_PWM )
    {
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC4_PWM.frequency_kHz, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC4_PWM.pulseHigh_ns, delimiter );        
        snprintf( string, stringSize, "%s%.1f%s", string, measureValues->valueIC4_PWM.pulseLow_ns, delimiter );        
    }

    HwAPI_SystemTime_Get( timeString, sizeof( timeString ) );
    snprintf( string, stringSize, "%s%s", string, timeString );        
}
/* End of file */
