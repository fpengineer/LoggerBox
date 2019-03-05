/*****************************************************************************************************

    Plugin ConverterI7 - IC6 - V1_0 defines



*******************************************************************************************************/
#ifndef _CONVERTER_I7_IC6_V1_0_H_
#define _CONVERTER_I7_IC6_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"
#include "PluginsString.h"
#include "PluginsDelay.h"


#ifndef PLUGIN_8

#define PLUGIN_8
#define PLUGIN_8_NAME       "ConverterI7_IC6_V1_0"
#define PLUGIN_8_POINTER    ConverterI7_IC6_V1_0

#else 
#error "PLUGIN_8 already defined! Please select another plugin number and nam definitions."
#endif

/* Exported types --------------------------------------------------------*/
                                            
/* Exported functions --------------------------------------------------------*/
void ConverterI7_IC6_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

#endif /* _CONVERTER_I7_IC6_V1_0_H_ */
/* End of file */
