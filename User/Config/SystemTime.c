/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: System Time configuration functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "defines.h"
#include "tm_stm32f4_rtc.h"

#include "Config.h"
#include "minIni.h"

static char tempString[150] = {""}; 
static char configKeyStringValue[25] = {""}; 

cfgSystemTime_t ConfigSystemTime_GetParameters(void)
{
    extern QueueHandle_t xQueue_Terminal;
    cfgSystemTime_t cfgSystemTime;
    
// Sectoin [SystemTime]
	cfgSystemTime.UpdateSystemTime = ini_getl("SystemTime", "UpdateSystemTime", -1, "config.ini");

    ini_gets("SystemTime", "SystemTimeString", "", configKeyStringValue, sizeof(configKeyStringValue), "config.ini");
    cfgSystemTime.datatime = SystemTime_convertFromString(configKeyStringValue);
    
	return cfgSystemTime;
}

void ConfigSystemTime_MarkUpdated(void)
{
	ini_putl("SystemTime", "UpdateSystemTime", UPDATE_SYSTEM_TIME_DISABLE, "config.ini");
}


void SystemTime_convertToString(char *timeString, TM_RTC_Time_t datatime)
{
    sprintf(timeString, "%02d.%02d.%04d %02d:%02d:%02d",
                        datatime.date,
                        datatime.month,
                        datatime.year + 2000,
                        datatime.hours,
                        datatime.minutes,
                        datatime.seconds);
}

TM_RTC_Time_t SystemTime_convertFromString(char *timeString)
{
    TM_RTC_Time_t datatime;

    datatime.day = 1;
    datatime.date = atoi(timeString);
    datatime.month = atoi(timeString + 3);
    datatime.year = atoi(timeString + 6) - 2000;
    datatime.hours = atoi(timeString + 10);
    datatime.minutes = atoi(timeString + 14);
    datatime.seconds = atoi(timeString + 17);
    return datatime;
}

void ConfigSystemTime_SendParametersToTerminal(cfgSystemTime_t cfgSystemTime)
{
    extern QueueHandle_t xQueue_Terminal;
    char string[25] = {""}; 

    SystemTime_convertToString(string, cfgSystemTime.datatime);
    sprintf(tempString, "\r\n[SystemTime]\r\n"
                        "UpdateSystemTime = %d\r\n"
                        "SystemTimeString = %s\r\n", 
                        cfgSystemTime.UpdateSystemTime,
                        string);
    
    xQueueSend( xQueue_Terminal, &tempString, NULL );

}
/* End of file */
