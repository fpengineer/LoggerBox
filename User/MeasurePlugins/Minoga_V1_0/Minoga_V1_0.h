/*****************************************************************************************************

    Plugin Minoga - V1_0 defines
    


*******************************************************************************************************/
#ifndef _MINOGA_V1_0_H_
#define _MINOGA_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"
#include "PluginsString.h"
#include "PluginsDelay.h"


#ifndef PLUGIN_14

#define PLUGIN_14
#define PLUGIN_14_NAME       "Minoga_V1_0"
#define PLUGIN_14_POINTER    Minoga_V1_0

#else 
#error "PLUGIN_14 already defined! Please select another plugin number and nam definitions."
#endif

/* Exported types --------------------------------------------------------*/
                                            
/* Exported functions --------------------------------------------------------*/
void Minoga_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

#endif /* _MINOGA_V1_0_H_ */
/* End of file */
