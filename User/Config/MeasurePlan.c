/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plan configuration functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"

#include "defines.h"
#include "tm_stm32f4_rtc.h"

#include "Config.h"
#include "minIni.h"

static char tempString[500] = {""}; 
static char configKeyStringValue[25] = {""}; 

cfgMeasurePlan_t ConfigMeasurePlan_GetParameters(void)
{
    cfgMeasurePlan_t cfgMeasurePlan;
    
// Sectoin [MeasurePlan]
    cfgMeasurePlan.Tact1_Length_s = ini_getl("MeasurePlan", "Tact1_Length_s", -1, "config.ini");

    cfgMeasurePlan.Tact2_Length_s = ini_getl("MeasurePlan", "Tact2_Length_s", -1, "config.ini");
    
    cfgMeasurePlan.Tact3_Length_s = ini_getl("MeasurePlan", "Tact3_Length_s", -1, "config.ini");
    
    ini_gets("MeasurePlan", "SourceG1_V", "key not found", configKeyStringValue, sizeof(configKeyStringValue), "config.ini");
    cfgMeasurePlan.SourceG1_V = atof(configKeyStringValue);

    ini_gets("MeasurePlan", "SourceG2_V", "key not found", configKeyStringValue, sizeof(configKeyStringValue), "config.ini");
    cfgMeasurePlan.SourceG2_V = atof(configKeyStringValue);

    ini_gets("MeasurePlan", "SourceG3_V", "key not found", configKeyStringValue, sizeof(configKeyStringValue), "config.ini");
    cfgMeasurePlan.SourceG3_V = atof(configKeyStringValue);

    ini_gets("MeasurePlan", "SourceG4_V", "key not found", configKeyStringValue, sizeof(configKeyStringValue), "config.ini");
    cfgMeasurePlan.SourceG4_V = atof(configKeyStringValue);

    return cfgMeasurePlan;
}

void ConfigMeasurePlan_SendParametersToTerminal(cfgMeasurePlan_t cfgMeasurePlan)
{
    extern QueueHandle_t xQueue_Terminal;

    sprintf(tempString, "\r\n[MeasurePlan]\r\n"
                        "Tact1_Length_s = %d\r\n"
                        "Tact2_Length_s = %d\r\n"
                        "Tact3_Length_s = %d\r\n"
                        "SourceG1_V = %.1f\r\n"
                        "SourceG2_V = %.1f\r\n"
                        "SourceG3_V = %.1f\r\n"
                        "SourceG4_V = %.1f\r\n",
                        cfgMeasurePlan.Tact1_Length_s,
                        cfgMeasurePlan.Tact2_Length_s,
                        cfgMeasurePlan.Tact3_Length_s,
                        cfgMeasurePlan.SourceG1_V,
                        cfgMeasurePlan.SourceG2_V,
                        cfgMeasurePlan.SourceG3_V,
                        cfgMeasurePlan.SourceG4_V);

    xQueueSend( xQueue_Terminal, &tempString, NULL );
}


/* End of file */
