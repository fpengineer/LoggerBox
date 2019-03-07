/*****************************************************************************************************

    HwAPI Voltage Source



*******************************************************************************************************/


#ifndef _HWAPI_VOLTAGE_SOURCE_H_
#define _HWAPI_VOLTAGE_SOURCE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "AD56x0.h"



// Source range
#define NSOURCE1_RANGE      30.0f
#define NSOURCE2_RANGE      30.0f
#define NSOURCE3_RANGE      30.0f
#define NSOURCE4_RANGE      30.0f


// Calibration constants
#define NSOURCE1_CALIBRATION_SLOPE		1.01f
#define NSOURCE1_CALIBRATION_OFFSET		( -0.025f )

#define NSOURCE2_CALIBRATION_SLOPE		1.008f
#define NSOURCE2_CALIBRATION_OFFSET		( -0.075f )

#define NSOURCE3_CALIBRATION_SLOPE		0.993f
#define NSOURCE3_CALIBRATION_OFFSET		( -0.06f )

#define NSOURCE4_CALIBRATION_SLOPE		1.014f
#define NSOURCE4_CALIBRATION_OFFSET		( -0.205f )


// DAC CS port/pin defines
#define NSOURCE1_CS_PORT    GPIOB
#define NSOURCE1_CS_PIN     GPIO_Pin_9

#define NSOURCE2_CS_PORT    GPIOE
#define NSOURCE2_CS_PIN     GPIO_Pin_1

#define NSOURCE3_CS_PORT    GPIOE
#define NSOURCE3_CS_PIN     GPIO_Pin_3

#define NSOURCE4_CS_PORT    GPIOE
#define NSOURCE4_CS_PIN     GPIO_Pin_5


// DAC CS macro
#define DAC1_CS_1()       GPIO_SetBits( NSOURCE1_CS_PORT, NSOURCE1_CS_PIN )
#define DAC1_CS_0()       GPIO_ResetBits( NSOURCE1_CS_PORT, NSOURCE1_CS_PIN )

#define DAC2_CS_1()       GPIO_SetBits( NSOURCE2_CS_PORT, NSOURCE2_CS_PIN )
#define DAC2_CS_0()       GPIO_ResetBits( NSOURCE2_CS_PORT, NSOURCE2_CS_PIN )

#define DAC3_CS_1()       GPIO_SetBits( NSOURCE3_CS_PORT, NSOURCE3_CS_PIN )
#define DAC3_CS_0()       GPIO_ResetBits( NSOURCE3_CS_PORT, NSOURCE3_CS_PIN )

#define DAC4_CS_1()       GPIO_SetBits( NSOURCE4_CS_PORT, NSOURCE4_CS_PIN )
#define DAC4_CS_0()       GPIO_ResetBits( NSOURCE4_CS_PORT, NSOURCE4_CS_PIN )

/* Exported types ------------------------------------------------------------*/
enum stateHwVoltageSource {
    HW_VOLTAGE_SOURCE_INIT,
    HW_VOLTAGE_SOURCE_SET,
    HW_VOLTAGE_SOURCE_CLEAR,
    HW_VOLTAGE_SOURCE_CLEAR_ALL,
    HW_VOLTAGE_SOURCE_IDLE
};

typedef enum {
    NSOURCE_1 = 0,
    NSOURCE_2,
    NSOURCE_3,
    NSOURCE_4
} NSource_t;

#ifndef CALIBRATION_DATA_TYPEDEF
#define CALIBRATION_DATA_TYPEDEF
typedef struct {
    float slope;
    float offset;
} CalibrationData_t;
#endif

typedef struct {
    enum stateHwVoltageSource stateHwVoltageSource;
    NSource_t nSource;
    ValueAD56x0_t valueDAC;
} HwVoltageSourceQueueData_t;



/* Exported functions --------------------------------------------------------*/
HwAPI_Status_t HwAPI_VoltageSource_Set( NSource_t nSource, float value );
HwAPI_Status_t HwAPI_VoltageSource_Clear( NSource_t nSource );
HwAPI_Status_t HwAPI_VoltageSource_ClearAll( void );

void vTask_HwVoltageSource( void *pvParameters );
HwAPI_BootStatus_t HwAPI_VoltageSource_Run( void );

#endif /* _HWAPI_SOURCE_H_*/
/* End of file */
