/*****************************************************************************************************

    HwAPI SystemTime



*******************************************************************************************************/


#ifndef _HW_API_SYSTEM_TIME_H_
#define _HW_API_SYSTEM_TIME_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>



#include "HwAPI Def.h"



/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void HwAPI_SystemTime_Set( TM_RTC_Time_t datatime );
TM_RTC_Time_t HwAPI_SystemTime_Get( void );

#endif /* _HW_API_SYSTEM_TIME_H_*/
/* End of file */
