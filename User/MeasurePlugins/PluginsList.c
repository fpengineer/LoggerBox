/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plugins list

*******************************************************************************************************/
#include <stdlib.h>
#include <stdint.h>

#include "PluginsDef.h"


const char *pluginsList[ 20 ] = {    
#ifdef PLUGIN_0
    PLUGIN_0_NAME,
#endif
#ifdef PLUGIN_1
    PLUGIN_1_NAME,
#endif
#ifdef PLUGIN_2
    PLUGIN_2_NAME,
#endif
#ifdef PLUGIN_3
    PLUGIN_3_NAME,
#endif
#ifdef PLUGIN_4
    PLUGIN_4_NAME,
#endif
#ifdef PLUGIN_5
    PLUGIN_5_NAME,
#endif
#ifdef PLUGIN_6
    PLUGIN_6_NAME,
#endif
#ifdef PLUGIN_7
    PLUGIN_7_NAME,
#endif
#ifdef PLUGIN_8
    PLUGIN_8_NAME,
#endif
#ifdef PLUGIN_9
    PLUGIN_9_NAME,
#warning "Last plugin number defined! Please check plugins numbers sequence or add additional plugin numbers to pluginList[]."
#endif
    "empty"
};



/* End of file */
