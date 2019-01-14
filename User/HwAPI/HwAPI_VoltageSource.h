/*****************************************************************************************************

    HwAPI Voltage Source



*******************************************************************************************************/


#ifndef _HWAPI_VOLTAGE_SOURCE_H_
#define _HWAPI_VOLTAGE_SOURCE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"
#include "AD56x0.h"



// Source range
#define NSOURCE1_RANGE      27.0f
#define NSOURCE2_RANGE      27.0f
#define NSOURCE3_RANGE      27.0f
#define NSOURCE4_RANGE      27.0f


// Calibration constants
#define NSOURCE1_CALIBRATION_SLOPE		1.0f
#define NSOURCE1_CALIBRATION_OFFSET		0.0f

#define NSOURCE2_CALIBRATION_SLOPE		1.0f
#define NSOURCE2_CALIBRATION_OFFSET		0.0f

#define NSOURCE3_CALIBRATION_SLOPE		1.0f
#define NSOURCE3_CALIBRATION_OFFSET		0.0f

#define NSOURCE4_CALIBRATION_SLOPE		1.0f
#define NSOURCE4_CALIBRATION_OFFSET		0.0f


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




/* Exported functions --------------------------------------------------------*/
HwAPI_StatusTypeDef HwAPI_VoltageSource_Set( NSource_t nSource, float value );
HwAPI_StatusTypeDef HwAPI_VoltageSource_Clear( NSource_t nSource );
HwAPI_StatusTypeDef HwAPI_VoltageSource_ClearAll( void );



#endif /* _HWAPI_SOURCE_H_*/
/* End of file */
