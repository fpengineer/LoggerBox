/*****************************************************************************************************

    HwAPI SystemTime



*******************************************************************************************************/


#ifndef _HW_API_SYSTEM_TIME_H_
#define _HW_API_SYSTEM_TIME_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>



#include "HwAPI Def.h"
#include "tm_stm32f4_rtc.h"

#define UPDATE_SYSTEM_TIME_DISABLE 0
#define UPDATE_SYSTEM_TIME_ENABLE 1


/* Exported types ------------------------------------------------------------*/
typedef struct {
    int32_t flagUpdateSystemTime;
    TM_RTC_Time_t datatime;
} cfgSystemTime_t;


/* Exported functions --------------------------------------------------------*/
void HwAPI_SystemTime_Set( TM_RTC_Time_t datatime );    // perhaps not needed
void HwAPI_SystemTime_Get( char *timeString );
void HwAPI_SystemTime_ProcessConfig( int32_t *flagUpdateSystemTime, char *timeString );
void HwAPI_SystemTime_SendToTerminal( char *timeString );

#endif /* _HW_API_SYSTEM_TIME_H_*/
/* End of file */
