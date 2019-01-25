/*****************************************************************************************************

    HwAPI SD card LED



*******************************************************************************************************/
#ifndef _HWAPI_SDCARD_LED_H_
#define _HWAPI_SDCARD_LED_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"


// SD card LED port/pin defines
#define SDCARD_LED_PORT   GPIOC
#define SDCARD_LED_PIN    GPIO_Pin_2

// SD card LED On/Off macro
#define SDCardLED_On()        GPIO_SetBits( SDCARD_LED_PORT, SDCARD_LED_PIN )
#define SDCardLED_Off()       GPIO_ResetBits( SDCARD_LED_PORT, SDCARD_LED_PIN )
#define SDCardLED_Toggle()    GPIO_ToggleBits( SDCARD_LED_PORT, SDCARD_LED_PIN )

#define SDCARD_LED_FLASH_SLOW		500 // delay in milliseconds
#define SDCARD_LED_FLASH_FAST		200 // delay in milliseconds


/* Exported types ------------------------------------------------------------*/
enum stateHwSDCardLED {
    HW_SDCARD_LED_INIT,
    HW_SDCARD_LED_ON,
    HW_SDCARD_LED_OFF,
    HW_SDCARD_LED_FLASH,
    HW_SDCARD_LED_IDLE
};

typedef struct {
    enum stateHwSDCardLED stateHwSDCardLED;
    uint16_t delay_ms;
} HwSDCardLEDQueueData_t;


/* Exported functions --------------------------------------------------------*/
HwAPI_Status_t HwAPI_SDCardLED_On( void );
HwAPI_Status_t HwAPI_SDCardLED_Off( void );
HwAPI_Status_t HwAPI_SDCardLED_Flash( uint16_t delay_ms );

void vTask_HwSDCardLED( void *pvParameters );
void HwAPI_SDCardLED_Run( void );
HwAPI_BootStatus_t HwAPI_SDCardLED_GetBootStatus( void );


#endif /* _HWAPI_SDCARD_LED_H_*/
/* End of file */
