/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _SYSTEM_TIME_H_
#define _SYSTEM_TIME_H_

#include <stdint.h>
#include "defines.h"
#include "tm_stm32f4_rtc.h"

typedef struct {
    int32_t UpdateSystemTime;
    TM_RTC_Time_t datatime;
} cfgSystemTime_t;


#define UPDATE_SYSTEM_TIME_DISABLE 0
#define UPDATE_SYSTEM_TIME_ENABLE 1

cfgSystemTime_t ConfigSystemTime_GetParameters(void);
void ConfigSystemTime_MarkUpdated(void);
void SystemTime_convertToString(char* timeString, TM_RTC_Time_t datatime);
TM_RTC_Time_t SystemTime_convertFromString(char* timeString);
void ConfigSystemTime_SendParametersToTerminal(cfgSystemTime_t cfgSystemTime);

#endif /* _SYSTEM_TIME_H_ */
/* End of file */
