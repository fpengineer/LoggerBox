/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Plugin 3 V1.0
    
*******************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "HwAPI.h"
#include "plgPlugin3_V1_0\plgPlugin3_V1_0.h"
#include "PluginsString.h"
#include "PluginsDelay.h"

char string[100] = {""};

void plgPlugin3( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    switch ( pluginCommand )
    {
        case CMD_PLUGIN_RUN:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin3 - Run\n" );
#endif
            *tactLength_ms = 2000;
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_STOP:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin3 - Stop\n" );
#endif
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_TACT:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin3 - Tact\n" );
#endif
            float value = 0.0f;


            HwAPI_VoltageSource_Set( NSOURCE_1, 12.0f );
            PluginDelay_ms( 100 );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_1 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC1_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC1_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_1 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_2 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC2_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC2_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_2 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_3 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC3_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC3_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_3 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_4 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC4_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC4_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_4 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_5 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC5_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC5_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_5 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_6 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC6_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC6_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_6 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_7 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC7_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC7_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_7 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_DAQ_ADC_SelectInput( ADC_CHANNEL_1, ADC_SOURCE_8 );
            //HwAPI_DAQ_ADC_GetAveraged( &value, SRC8_RANGE_V, 512 );
            HwAPI_DAQ_ADC_GetSingle( &value, SRC8_RANGE_V );
            snprintf( string, sizeof(string), "ADC_SOURCE_8 = %.3f\n", value );        
            HwAPI_Terminal_SendMessage( string );

            HwAPI_Terminal_SendMessage( "\n----------------------------\n" );


            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_ERROR:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin3 - Error\n" );
#endif
            break;
        }

        case CMD_PLUGIN_IDLE:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin3 - Idle\n" );
#endif
            break;
        }

        default:
            break;
    }
}



/* End of file */
