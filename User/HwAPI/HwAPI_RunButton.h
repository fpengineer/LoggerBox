/*****************************************************************************************************

    HwAPI Run button



*******************************************************************************************************/


#ifndef _HWAPI_RUN_BUTTON_H_
#define _HWAPI_RUN_BUTTON_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"

// Run button detect port/pin defines
#define RUN_BUTTON_PORT          GPIOC
#define RUN_BUTTON_PIN           GPIO_Pin_3


/* Exported types ------------------------------------------------------------*/
enum stateHwRunButton {
    HW_RUN_BUTTON_INIT,
    HW_RUN_BUTTON_GET,
    HW_RUN_BUTTON_PRESSED,
    HW_RUN_BUTTON_IDLE
};

typedef enum {
    RUN_BUTTON_PRESSED,
    RUN_BUTTON_NO_ACTION
} RunButtonStatus_t;

typedef struct {
    enum stateHwRunButton stateHwRunButton;
    RunButtonStatus_t runButtonStatus;
} HwRunButtonQueueData_t;


/* Exported functions --------------------------------------------------------*/
RunButtonStatus_t HwAPI_RunButton_GetStatus( void );

void vTask_HwRunButton( void *pvParameters );
HwAPI_BootStatus_t HwAPI_RunButton_Run( void );

#endif /* _HWAPI_RUN_BUTTON_H_*/
/* End of file */
