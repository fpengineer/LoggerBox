/*****************************************************************************************************

    Plugin 3 defines



*******************************************************************************************************/
#ifndef _PLG_PLUGIN3_V1_0_H_
#define _PLG_PLUGIN3_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"


#ifndef PLUGIN_3

#define PLUGIN_3
#define PLUGIN_3_NAME       "Plugin3"
#define PLUGIN_3_POINTER    plgPlugin3

#else 
#error "PLUGIN_1 already defined! Please select another plugin number and name definitions."
#endif

/* Exported types --------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void plgPlugin3( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );


#endif /* _PLG_PLUGIN3_V1_0_H_ */
/* End of file */
