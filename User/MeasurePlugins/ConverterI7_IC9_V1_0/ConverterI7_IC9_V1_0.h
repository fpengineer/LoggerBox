/*****************************************************************************************************

    Plugin ConverterI7 - IC9 - V1_0 defines



*******************************************************************************************************/
#ifndef _CONVERTER_I7_IC9_V1_0_H_
#define _CONVERTER_I7_IC9_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"
#include "PluginsString.h"
#include "PluginsDelay.h"


#ifndef PLUGIN_11

#define PLUGIN_11
#define PLUGIN_11_NAME       "ConverterI7_IC9_V1_0"
#define PLUGIN_11_POINTER    ConverterI7_IC9_V1_0

#else 
#error "PLUGIN_11 already defined! Please select another plugin number and nam definitions."
#endif

/* Exported types --------------------------------------------------------*/
                                            
/* Exported functions --------------------------------------------------------*/
void ConverterI7_IC9_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

#endif /* _CONVERTER_I7_IC9_V1_0_H_ */
/* End of file */
