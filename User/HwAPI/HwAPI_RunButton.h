/*****************************************************************************************************

    HwAPI Run button



*******************************************************************************************************/


#ifndef _HWAPI_RUN_BUTTON_H_
#define _HWAPI_RUN_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"

// Run button detect port/pin defines
#define RUN_BUTTON_PORT          GPIOC
#define RUN_BUTTON_PIN           GPIO_Pin_3


/* Exported types ------------------------------------------------------------*/
typedef enum {
    RUN_BUTTON_PRESSED,
    RUN_BUTTON_NO_ACTION
} RunButtonStatus_t;


/* Exported functions --------------------------------------------------------*/
RunButtonStatus_t HwAPI_RunButton_GetStatus( void );

#endif /* _HWAPI_RUN_BUTTON_H_*/
/* End of file */
