/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Plugin 2 V1.0 Calibration of the system
    
*******************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "HwAPI.h"
#include "plgPlugin2_V1_0\plgPlugin2_V1_0.h"
#include "plgPlugin2_V1_0\types.h"
#include "PluginsString.h"

void plgPlugin2( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    switch ( pluginCommand )
    {
        case CMD_PLUGIN_RUN:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin2 - Run\n" );
#endif
            //char tempString[ 500 ] = { "" };

            HwAPI_Terminal_SendMessage( "Start calibration.\n" );
/*
            sprintf( tempString, "valueSrc1\t"
                                 "valueSrc2\t"
                                 "valueSrc3\t"
                                 "valueSrc4\t"
                                 "valueSrc5\t"
                                 "valueSrc6\t"
                                 "valueSrc7\t"
                                 "valueSrc8\n" );
            HwAPI_Terminal_SendMessage( tempString );
*/
            *tactLength_ms = 1000;
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_STOP:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin2 - Stop\n" );
#endif
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_TACT:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin2 - Tact\n" );
#endif

            HwAPI_Terminal_SendMessage( "Set source: 1 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 1.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 1.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 1.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 1.0f );
            PluginDelay_ms( 15000 );
            
            HwAPI_Terminal_SendMessage( "Set source: 5 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 5.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 5.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 5.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 5.0f );
            PluginDelay_ms( 15000 );
            
            HwAPI_Terminal_SendMessage( "Set source: 10 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 10.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 10.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 10.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 10.0f );
            PluginDelay_ms( 15000 );
            
            HwAPI_Terminal_SendMessage( "Set source: 15 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 15.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 15.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 15.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 15.0f );
            PluginDelay_ms( 15000 );
            
            HwAPI_Terminal_SendMessage( "Set source: 20 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 20.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 20.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 20.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 20.0f );
            PluginDelay_ms( 15000 );
            
            HwAPI_Terminal_SendMessage( "Set source: 25 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 25.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 25.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 25.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 25.0f );
            PluginDelay_ms( 15000 );
            
            HwAPI_Terminal_SendMessage( "Set source: 28 V\n" );
            HwAPI_VoltageSource_Set( NSOURCE_1, 28.0f );
            HwAPI_VoltageSource_Set( NSOURCE_2, 28.0f );
            HwAPI_VoltageSource_Set( NSOURCE_3, 28.0f );
            HwAPI_VoltageSource_Set( NSOURCE_4, 28.0f );
            PluginDelay_ms( 15000 );
            
            
            
            /*
            float valueSrc1 = 0.0f;
            float valueSrc2 = 0.0f;
            float valueSrc3 = 0.0f;
            float valueSrc4 = 0.0f;
            float valueSrc5 = 0.0f;
            float valueSrc6 = 0.0f;
            float valueSrc7 = 0.0f;
            float valueSrc8 = 0.0f;
            char tempString[ 500 ] = { "" };

            
            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_1 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc1, SRC1_RANGE_V, 1024 );
            
            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_2 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc2, SRC2_RANGE_V, 1024 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_3 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc3, SRC3_RANGE_V, 1024 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_4 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc4, SRC4_RANGE_V, 1024 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_5 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc5, SRC5_RANGE_V, 1024 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_6 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc6, SRC6_RANGE_V, 1024 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_7 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc7, SRC7_RANGE_V, 1024 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_8 );
//            PluginDelay_ms( 100 );
            HwAPI_DAQ_ADC_GetAveraged( &valueSrc8, SRC8_RANGE_V, 1024 );

            sprintf( tempString, "%.2f\t%.2f\t%.2f\t%.3f\t%.2f\t%.2f\t%.2f\t%.3f\n",
                                 valueSrc1,
                                 valueSrc2,
                                 valueSrc3,
                                 valueSrc4,
                                 valueSrc5,
                                 valueSrc6,
                                 valueSrc7,
                                 valueSrc8 );
            HwAPI_Terminal_SendMessage( tempString );
*/            
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_ERROR:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin2 - Error\n" );
#endif
            break;
        }

        case CMD_PLUGIN_IDLE:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin2 - Idle\n" );
#endif
            break;
        }

        default:
            break;
    }
}


/* End of file */
