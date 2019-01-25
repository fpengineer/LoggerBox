/*****************************************************************************************************

    HwAPI Relay



*******************************************************************************************************/


#ifndef _HWAPI_RELAY_H_
#define _HWAPI_RELAY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"


// Relay port/pin defines
#define NRELAY_K1_PORT    GPIOH
#define NRELAY_K1_PIN     GPIO_Pin_1

#define NRELAY_K2_PORT    GPIOC
#define NRELAY_K2_PIN     GPIO_Pin_15

#define NRELAY_K3_PORT    GPIOC
#define NRELAY_K3_PIN     GPIO_Pin_13

#define NRELAY_K4_PORT    GPIOD
#define NRELAY_K4_PIN     GPIO_Pin_4

#define NRELAY_K5_PORT    GPIOD
#define NRELAY_K5_PIN     GPIO_Pin_2

#define NRELAY_K6_PORT    GPIOD
#define NRELAY_K6_PIN     GPIO_Pin_0

#define NRELAY_K7_PORT    GPIOC
#define NRELAY_K7_PIN     GPIO_Pin_11


// Relay On/Off macro
#define RelayK1_On()        GPIO_SetBits( NRELAY_K1_PORT, NRELAY_K1_PIN )
#define RelayK1_Off()       GPIO_ResetBits( NRELAY_K1_PORT, NRELAY_K1_PIN )

#define RelayK2_On()        GPIO_SetBits( NRELAY_K2_PORT, NRELAY_K2_PIN)
#define RelayK2_Off()       GPIO_ResetBits( NRELAY_K2_PORT, NRELAY_K2_PIN )

#define RelayK3_On()        GPIO_SetBits( NRELAY_K3_PORT, NRELAY_K3_PIN )
#define RelayK3_Off()       GPIO_ResetBits( NRELAY_K3_PORT, NRELAY_K3_PIN )

#define RelayK4_On()        GPIO_SetBits( NRELAY_K4_PORT, NRELAY_K4_PIN )
#define RelayK4_Off()       GPIO_ResetBits( NRELAY_K4_PORT, NRELAY_K4_PIN )

#define RelayK5_On()        GPIO_SetBits( NRELAY_K5_PORT, NRELAY_K5_PIN )
#define RelayK5_Off()       GPIO_ResetBits( NRELAY_K5_PORT, NRELAY_K5_PIN )

#define RelayK6_On()        GPIO_SetBits( NRELAY_K6_PORT, NRELAY_K6_PIN )
#define RelayK6_Off()       GPIO_ResetBits( NRELAY_K6_PORT, NRELAY_K6_PIN )

#define RelayK7_On()        GPIO_SetBits( NRELAY_K7_PORT, NRELAY_K7_PIN )
#define RelayK7_Off()       GPIO_ResetBits( NRELAY_K7_PORT, NRELAY_K7_PIN )


/* Exported types ------------------------------------------------------------*/
enum stateHwRelay {
    HW_RELAY_INIT,
    HW_RELAY_SET,
    HW_RELAY_CLEAR,
    HW_RELAY_CLEAR_ALL,
    HW_RELAY_IDLE
};

typedef enum {
    NRELAY_K1 = 0,
    NRELAY_K2,
    NRELAY_K3,
    NRELAY_K4,
    NRELAY_K5,
    NRELAY_K6,
    NRELAY_K7
} NRelay_t;

typedef struct {
    enum stateHwRelay stateHwRelay;
    NRelay_t nRelay;
} HwRelayQueueData_t;




/* Exported functions --------------------------------------------------------*/
HwAPI_Status_t HwAPI_Relay_Set( NRelay_t nRelay );
HwAPI_Status_t HwAPI_Relay_Clear( NRelay_t nRelay );
HwAPI_Status_t HwAPI_Relay_ClearAll( void );

void vTask_HwRelay( void *pvParameters );
HwAPI_BootStatus_t HwAPI_Relay_Run( void );

#endif /* _HWAPI_RELAY_H_*/
/* End of file */
