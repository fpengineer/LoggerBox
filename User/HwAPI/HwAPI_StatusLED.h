/*****************************************************************************************************

    HwAPI Status LED



*******************************************************************************************************/
#ifndef _HWAPI_STATUS_LED_H_
#define _HWAPI_STATUS_LED_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"


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



/* Exported functions --------------------------------------------------------*/
HwAPI_StatusTypeDef HwAPI_StatusLED_On( void );
HwAPI_StatusTypeDef HwAPI_StatusLED_Off( void );
HwAPI_StatusTypeDef HwAPI_StatusLED_Flash( uint16_t delay_ms );



#endif /* _HWAPI_STATUS_LED_H_*/
/* End of file */
