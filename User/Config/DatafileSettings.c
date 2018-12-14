/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Datafile settings configuration functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "defines.h"

#include "Config.h"
#include "minIni.h"

static char tempString[150] = {""}; 
//static char configKeyStringValue[25] = {""}; 

cfgDatafileSettings_t ConfigDatafileSettings_GetParameters(void)
{
//    extern QueueHandle_t xQueue_Terminal;
    cfgDatafileSettings_t cfgDatafileSettings;
    
// Sectoin [DatafileSettings]
    ini_gets( "DatafileSettings", 
              "PrefixDatafileName", 
              "test", 
              cfgDatafileSettings.prefixDatafileName, 
              sizeof(cfgDatafileSettings.prefixDatafileName),
              "config.ini");

	cfgDatafileSettings.stringsToWrite = ini_getl( "DatafileSettings",
                                                   "StringsToWrite", 
                                                   100,
                                                   "config.ini");

    ini_gets( "DatafileSettings", 
              "Delimiter", 
              "test", 
              cfgDatafileSettings.delimiter, 
              sizeof(cfgDatafileSettings.delimiter),
              "config.ini");
    
	return cfgDatafileSettings;
}


void ConfigDatafileSettings_SendParametersToTerminal(cfgDatafileSettings_t cfgDatafileSettings)
{
    extern QueueHandle_t xQueue_HwTerminal_Rx;

    sprintf(tempString, "\r\n[DatafileSettings]\r\n"
                        "PrefixDatafileName = %s\r\n"
                        "StringsToWrite = %d\r\n" 
                        "delimiter = %s\r\n", 
                        cfgDatafileSettings.prefixDatafileName,
                        cfgDatafileSettings.stringsToWrite,
                        cfgDatafileSettings.delimiter);
    
    xQueueSend( xQueue_HwTerminal_Rx, &tempString, NULL );

}
/* End of file */
