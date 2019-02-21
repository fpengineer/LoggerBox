/*****************************************************************************************************

    Plugins defines



*******************************************************************************************************/
#ifndef _PLUGINS_DEF_H_
#define _PLUGINS_DEF_H_

#include <stdint.h>


/* Exported types ------------------------------------------------------------*/
typedef enum {
    CMD_PLUGIN_RUN,
    CMD_PLUGIN_STOP,
    CMD_PLUGIN_TACT,
    CMD_PLUGIN_ERROR,
    CMD_PLUGIN_IDLE
}PluginCommand_t;

typedef struct {
    int8_t error;
    int32_t errorCode;
    char message[ 150 ];
}PluginResult_t;

/* Exported functions --------------------------------------------------------*/


#endif /* _PLUGINS_DEF_H_ */
/* End of file */
