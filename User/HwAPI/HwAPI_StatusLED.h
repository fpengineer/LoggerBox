/*****************************************************************************************************

    HwAPI Status LED



*******************************************************************************************************/
#ifndef _HWAPI_STATUS_LED_H_
#define _HWAPI_STATUS_LED_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"


// Status LED port/pin defines
#define STATUS_LED_PORT   GPIOC
#define STATUS_LED_PIN    GPIO_Pin_0

// Status LED On/Off macro
#define StatusLED_On()        GPIO_SetBits( STATUS_LED_PORT, STATUS_LED_PIN )
#define StatusLED_Off()       GPIO_ResetBits( STATUS_LED_PORT, STATUS_LED_PIN )
#define StatusLED_Toggle()    GPIO_ToggleBits( STATUS_LED_PORT, STATUS_LED_PIN )

#define STATUS_LED_FLASH_SLOW		500 // delay in milliseconds
#define STATUS_LED_FLASH_FAST		200 // delay in milliseconds


/* Exported types ------------------------------------------------------------*/
enum stateHwStatusLED {
    HW_STATUS_LED_INIT,
    HW_STATUS_LED_ON,
    HW_STATUS_LED_OFF,
    HW_STATUS_LED_FLASH,
    HW_STATUS_LED_IDLE
};

typedef struct {
    enum stateHwStatusLED stateHwStatusLED;
    uint16_t delay_ms;
} HwStatusLEDQueueData_t;


/* Exported functions --------------------------------------------------------*/
HwAPI_Status_t HwAPI_StatusLED_On( void );
HwAPI_Status_t HwAPI_StatusLED_Off( void );
HwAPI_Status_t HwAPI_StatusLED_Flash( uint16_t delay_ms );

void vTask_HwStatusLED( void *pvParameters );
void HwAPI_StatusLED_Run( void );
HwAPI_BootStatus_t HwAPI_StatusLED_GetBootStatus( void );


#endif /* _HWAPI_STATUS_LED_H_*/
/* End of file */
