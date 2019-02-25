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

void plgPlugin3( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms )
{
    switch ( pluginCommand )
    {
        case CMD_PLUGIN_RUN:
        {
#ifdef PLUGINS_DEBUG_INFO
            HwAPI_Terminal_SendMessage( "Plugin3 - Run\n" );
#endif
            *tactLength_ms = 500;
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
