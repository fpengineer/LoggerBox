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
void HwAPI_SystemTim_Get( TM_RTC_Time_t *datatime );

#endif /* _HW_API_SYSTEM_TIME_H_*/
/* End of file */
