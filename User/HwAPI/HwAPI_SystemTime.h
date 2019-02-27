/*****************************************************************************************************

    HwAPI SystemTime



*******************************************************************************************************/


#ifndef _HWAPI_SYSTEM_TIME_H_
#define _HWAPI_SYSTEM_TIME_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>


#include "HwAPI.h"
#include "tm_stm32f4_rtc.h"

#define UPDATE_SYSTEM_TIME_DISABLE 0
#define UPDATE_SYSTEM_TIME_ENABLE 1




/* Exported types ------------------------------------------------------------*/
enum stateHwSystemTime {
    HW_SYSTEM_TIME_INIT,
    HW_SYSTEM_TIME_SET,
    HW_SYSTEM_TIME_GET,
    HW_SYSTEM_TIME_IDLE
};

typedef struct {
    int32_t flagUpdateSystemTime;
    TM_RTC_Time_t datatime;
} cfgSystemTime_t;

typedef struct {
    enum stateHwSystemTime stateHwSystemTime ;
    TM_RTC_Time_t datatime;    
//    cfgSystemTime_t cfgSystemTime;
} HwSystemTimeQueueData_t;


/* Exported functions --------------------------------------------------------*/
void HwAPI_SystemTime_Set( char *timeString );
void HwAPI_SystemTime_Get( char *timeString, int32_t stringLength );

void vTask_HwSystemTime( void *pvParameters );
HwAPI_BootStatus_t HwAPI_SystemTime_Run( void );

#endif /* _HWAPI_SYSTEM_TIME_H_*/
/* End of file */
