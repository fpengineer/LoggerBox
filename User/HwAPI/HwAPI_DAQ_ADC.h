/*****************************************************************************************************

    HwAPI DAQ - ADC



*******************************************************************************************************/


#ifndef _HWAPI_DAQ_ADC_H_
#define _HWAPI_DAQ_ADC_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"


// Standart ranges for channels
#define SRC1_RANGE_V     30.0f
#define SRC2_RANGE_V     30.0f
#define SRC3_RANGE_V     30.0f
#define SRC4_RANGE_V     5.0f
#define SRC5_RANGE_V     30.0f
#define SRC6_RANGE_V     30.0f
#define SRC7_RANGE_V     30.0f
#define SRC8_RANGE_V     5.0f


// Calibration constants (not needed now)
#define SRC1_CALIBRATION_SLOPE		1.0003f
#define SRC1_CALIBRATION_OFFSET		-0.015f

#define SRC2_CALIBRATION_SLOPE		1.001f
#define SRC2_CALIBRATION_OFFSET		-0.01f

#define SRC3_CALIBRATION_SLOPE		1.0018f
#define SRC3_CALIBRATION_OFFSET		-0.015f

#define SRC4_CALIBRATION_SLOPE		1.001f
#define SRC4_CALIBRATION_OFFSET		0.0023f

#define SRC5_CALIBRATION_SLOPE		1.001f//0.9994f
#define SRC5_CALIBRATION_OFFSET		-0.018f//-0.045f

#define SRC6_CALIBRATION_SLOPE		1.0f
#define SRC6_CALIBRATION_OFFSET		-0.023f

#define SRC7_CALIBRATION_SLOPE		0.9995f
#define SRC7_CALIBRATION_OFFSET		-0.012f

#define SRC8_CALIBRATION_SLOPE		1.0f
#define SRC8_CALIBRATION_OFFSET		0.0f

// ADC CS port/pin defines
#define ADC_CS_PORT    GPIOE
#define ADC_CS_PIN     GPIO_Pin_8

// DAC CS macro
#define ADC_CS_1()       GPIO_SetBits( ADC_CS_PORT, ADC_CS_PIN )
#define ADC_CS_0()       GPIO_ResetBits( ADC_CS_PORT, ADC_CS_PIN )


// Source selection port/pin defines 
#define MUX_SOURCE_C_PORT      GPIOE
#define MUX_SOURCE_C_PIN       GPIO_Pin_7

#define MUX_SOURCE_B_PORT      GPIOE
#define MUX_SOURCE_B_PIN       GPIO_Pin_10

#define MUX_SOURCE_A_PORT      GPIOE
#define MUX_SOURCE_A_PIN       GPIO_Pin_11


// Source selection macro 
#define MUX_SOURCE_A_1()       GPIO_SetBits( MUX_SOURCE_A_PORT, MUX_SOURCE_A_PIN )
#define MUX_SOURCE_A_0()       GPIO_ResetBits( MUX_SOURCE_A_PORT, MUX_SOURCE_A_PIN )

#define MUX_SOURCE_B_1()       GPIO_SetBits( MUX_SOURCE_B_PORT, MUX_SOURCE_B_PIN )
#define MUX_SOURCE_B_0()       GPIO_ResetBits( MUX_SOURCE_B_PORT, MUX_SOURCE_B_PIN )

#define MUX_SOURCE_C_1()       GPIO_SetBits( MUX_SOURCE_C_PORT, MUX_SOURCE_C_PIN )
#define MUX_SOURCE_C_0()       GPIO_ResetBits( MUX_SOURCE_C_PORT, MUX_SOURCE_C_PIN )



// Channel selection port/pin defines 
#define MUX_CHANNEL_A_PORT      GPIOE
#define MUX_CHANNEL_A_PIN       GPIO_Pin_9

#define MUX_CHANNEL_B_PORT      GPIOE
#define MUX_CHANNEL_B_PIN       GPIO_Pin_12

// Channel selection macro 
#define MUX_CHANNEL_A_1()       GPIO_SetBits( MUX_CHANNEL_A_PORT, MUX_CHANNEL_A_PIN )
#define MUX_CHANNEL_A_0()       GPIO_ResetBits( MUX_CHANNEL_A_PORT,  MUX_CHANNEL_A_PIN )

#define MUX_CHANNEL_B_1()       GPIO_SetBits( MUX_CHANNEL_B_PORT, MUX_CHANNEL_B_PIN )
#define MUX_CHANNEL_B_0()       GPIO_ResetBits( MUX_CHANNEL_B_PORT, MUX_CHANNEL_B_PIN )

/* Exported types ------------------------------------------------------------*/
enum stateHwDAQ_ADC {
    HW_DAQ_ADC_INIT,
    HW_DAQ_ADC_SELECT_INPUT,
    HW_DAQ_ADC_GET_SINGLE,
    HW_DAQ_ADC_GET_AVERAGED,
    HW_DAQ_ADC_STOP,
    HW_DAQ_ADC_IDLE
};

// Select input source for the ADC
typedef enum {
    ADC_SOURCE_1 = 0,
    ADC_SOURCE_2,
    ADC_SOURCE_3,
    ADC_SOURCE_4,
    ADC_SOURCE_5,
    ADC_SOURCE_6,
    ADC_SOURCE_7,
    ADC_SOURCE_8
} NSourceADC_t;

// Select IC
typedef enum {
    ADC_CHANNEL_1 = 0,
    ADC_CHANNEL_2,
    ADC_CHANNEL_3,
    ADC_CHANNEL_4
} NChannelADC_t;

typedef uint16_t ValueDAQ_ADC_t;

#ifndef CALIBRATION_DATA_TYPEDEF
#define CALIBRATION_DATA_TYPEDEF
typedef struct {
    float slope;
    float offset;
} CalibrationData_t;
#endif

typedef struct {
    enum stateHwDAQ_ADC stateHwDAQ_ADC;
    NChannelADC_t nChannelADC;
    NSourceADC_t nSourceADC;
    ValueDAQ_ADC_t valueADC;
    int32_t numberAverages;
} HwDAQ_ADCQueueData_t;

/* Exported functions --------------------------------------------------------*/
HwAPI_Status_t HwAPI_DAQ_ADC_SelectInput( NChannelADC_t nChannel, NSourceADC_t nSource );
HwAPI_Status_t HwAPI_DAQ_ADC_GetSingle( float *valueADC, float range );
HwAPI_Status_t HwAPI_DAQ_ADC_GetAveraged( float *valueADC, float range, int32_t numberAverages );
HwAPI_Status_t HwAPI_DAQ_ADC_Stop( void );

void vTask_HwDAQ_ADC( void *pvParameters );
HwAPI_BootStatus_t HwAPI_DAQ_ADC_Run( void );

#endif /* _HWAPI_DAQ_ADC_H_*/
/* End of file */
