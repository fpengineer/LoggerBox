/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: terminal functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "defines.h"
#include "tm_stm32f4_rtc.h"

#include "SystemTime.h"
#include "minIni.h"

static char tempString[80] = {""}; 
static char configSectionName[25] = {""}; 
static char configKeyStringValue[25] = {""}; 
static int32_t configKeyIntValue = -1;

void TerminalSend(char *message)
{
    char tempString[80] = {""};
    extern QueueHandle_t xQueue_Terminal;
    
    strcpy(tempString, message);
    xQueueSend( xQueue_Terminal, &tempString, NULL );
    
}

TM_RTC_Time_t ConfigSystemTime_Get( void )
{
    extern QueueHandle_t xQueue_Terminal;
    TM_RTC_Time_t datatime;
   
// Sectoin [SystemTime]
    ini_getsection(0, configSectionName, sizeof(configSectionName), "config.ini");
    sprintf(tempString, "\n[%s]\n", configSectionName);
    xQueueSend( xQueue_Terminal, &tempString, NULL );

	configKeyIntValue = ini_getl("SystemTime", "UpdateSystemTime", -1, "config.ini");
    sprintf(tempString, "UpdateSystemTime = %d\n", configKeyIntValue);
    xQueueSend( xQueue_Terminal, &tempString, NULL );

    ini_gets("SystemTime", "SystemTimeString", "", configKeyStringValue, sizeof(configKeyStringValue), "config.ini");
    sprintf(tempString, "SystemTimeString = %s\n", configKeyStringValue);
    xQueueSend( xQueue_Terminal, &tempString, NULL );

	return datatime;
}

/* End of file */
