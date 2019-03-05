/*****************************************************************************************************

    Plugin 1290EF1 - V1_0 defines



*******************************************************************************************************/
#ifndef _1290EF1_V1_0_H_
#define _1290EF1_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"
#include "PluginsString.h"
#include "PluginsDelay.h"


#ifndef PLUGIN_12

#define PLUGIN_12
#define PLUGIN_12_NAME       "1290EF1_V1_0"
#define PLUGIN_12_POINTER    Egorov_1290EF1_V1_0

#else 
#error "PLUGIN_12 already defined! Please select another plugin number and nam definitions."
#endif

/* Exported types --------------------------------------------------------*/
                                            
/* Exported functions --------------------------------------------------------*/
void Egorov_1290EF1_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

#endif /* _1290EF1_V1_0_H_ */
/* End of file */
