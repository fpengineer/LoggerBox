/*****************************************************************************************************

    Plugin 2 defines



*******************************************************************************************************/
#ifndef _PLG_PLUGIN2_V1_0_H_
#define _PLG_PLUGIN2_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"


#ifndef PLUGIN_2

#define PLUGIN_2
#define PLUGIN_2_NAME       "Plugin2"
#define PLUGIN_2_POINTER    plgPlugin2

#else 
#error "PLUGIN_1 already defined! Please select another plugin number and name definitions."
#endif

/* Exported types --------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void plgPlugin2( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );


#endif /* _PLG_PLUGIN2_V1_0_H_ */
/* End of file */
