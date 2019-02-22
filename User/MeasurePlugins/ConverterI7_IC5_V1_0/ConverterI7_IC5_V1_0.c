/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Plugin ConverterI7 - IC5 - V1.0
    
*******************************************************************************************************/
#include <stdio.h>
#include <stdint.h>

#include "HwAPI.h"
#include "ConverterI7_IC5_V1_0\ConverterI7_IC5_V1_0.h"


// Declare private functions

// Declare private variables
//static char tempString[ 100 ] = { "" };

void ConverterI7_IC5_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    switch ( pluginCommand )
    {
        case CMD_PLUGIN_RUN:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Run\n" );
#endif




            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_STOP:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Stop\n" );
#endif
            



            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_TACT:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "ConverterI7_IC5_V1_0 - Tact\n" );
#endif




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
/* End of file */
