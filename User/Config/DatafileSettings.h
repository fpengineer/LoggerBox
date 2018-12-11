/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _DATAFILE_SETTINGS_H_
#define _DATAFILE_SETTINGS_H_

#include <stdint.h>
#include "defines.h"
#include "tm_stm32f4_rtc.h"

typedef struct {
    char prefixDatafileName[15];
    uint32_t stringsToWrite;
    char delimiter[5];
} cfgDatafileSettings_t;


cfgDatafileSettings_t ConfigDatafileSettings_GetParameters(void);
void ConfigDatafileSettings_SendParametersToTerminal(cfgDatafileSettings_t cfgDatafileSettings);

#endif /* _DATAFILE_SETTINGS_H_ */
/* End of file */
