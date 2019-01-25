/*****************************************************************************************************

    HwAPI terminal



*******************************************************************************************************/


#ifndef _HW_API_TERMINAL_H_
#define _HW_API_TERMINAL_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"


/* Exported types ------------------------------------------------------------*/


/* Exported functions --------------------------------------------------------*/
void HwAPI_Terminal_SendMessage( char *message );

void vTask_HwTerminal( void *pvParameters );
void HwAPI_Terminal_Run( void );
HwAPI_BootStatus_t HwAPI_Terminal_GetBootStatus( void );

#endif /* _HW_API_TERMINAL_H_*/
/* End of file */
