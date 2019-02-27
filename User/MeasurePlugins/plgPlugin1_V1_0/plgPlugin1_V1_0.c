/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Plugin 1 V1.0
    
*******************************************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "HwAPI.h"
#include "plgPlugin1_V1_0\plgPlugin1_V1_0.h"
#include "PluginsString.h"

void plgPlugin1( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    static int32_t i = 0;
    char tempString[ 50 ] = { "" };

    switch ( pluginCommand )
    {
        case CMD_PLUGIN_RUN:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin1 - Run\n" );
#endif
            i = 0;
            *tactLength_ms = 500;
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_STOP:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin1 - Stop\n" );
#endif
            pluginResult->error = 0;
            break;
        }

        case CMD_PLUGIN_TACT:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin1 - Tact\n" );
#endif
            sprintf( tempString, "i = %d\n", i );
            HwAPI_Terminal_SendMessage( tempString );
            if ( i++ >= 4 )
            {
                pluginResult->error = 1;
                pluginResult->errorCode = 255;
                sprintf( pluginResult->message, "i reached 4.\n" );
            }
            else
            {
                pluginResult->error = 0;
            }
            break;
        }

        case CMD_PLUGIN_ERROR:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin1 - Error\n" );
#endif
            break;
        }

        case CMD_PLUGIN_IDLE:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin1 - Idle\n" );
#endif
            break;
        }

        default:
            break;
    }
}



/* End of file */
