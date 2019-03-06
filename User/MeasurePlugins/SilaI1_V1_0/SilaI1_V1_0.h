/*****************************************************************************************************

    Plugin SilaI1 - V1_0 defines



*******************************************************************************************************/
#ifndef _SILA_I1_V1_0_H_
#define _SILA_I1_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"
#include "PluginsString.h"
#include "PluginsDelay.h"


#ifndef PLUGIN_13

#define PLUGIN_13
#define PLUGIN_13_NAME       "SilaI1_V1_0"
#define PLUGIN_13_POINTER    SilaI1_V1_0

#else 
#error "PLUGIN_13 already defined! Please select another plugin number and nam definitions."
#endif

/* Exported types --------------------------------------------------------*/
                                            
/* Exported functions --------------------------------------------------------*/
void SilaI1_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

#endif /* _BARANOV_SILA_I1_V1_0_H_ */
/* End of file */
