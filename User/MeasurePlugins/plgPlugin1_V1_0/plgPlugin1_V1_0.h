/*****************************************************************************************************

    Plugin 1 defines



*******************************************************************************************************/
#ifndef _PLG_PLUGIN1_V1_0_H_
#define _PLG_PLUGIN1_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"


#ifndef PLUGIN_1

#define PLUGIN_1
#define PLUGIN_1_NAME       "Plugin1"
#define PLUGIN_1_POINTER    plgPlugin1

#else 
#error "PLUGIN_1 already defined! Please select another plugin number and name definitions."
#endif

/* Exported types --------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void plgPlugin1( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );


#endif /* _PLG_PLUGIN1_V1_0_H_ */
/* End of file */
