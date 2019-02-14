/*****************************************************************************************************

    HwAPI DAQ - Frequency



*******************************************************************************************************/
#ifndef _HWAPI_DAQ_FREQUENCY_H_
#define _HWAPI_DAQ_FREQUENCY_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"


// Calibration constants (not needed now)
#define FREQ_CALIBRATION_SLOPE      1.0f
#define FREQ_CALIBRATION_OFFSET     0.0f


// Frequency input selection port/pin defines 
#define MUX_FREQUENCY_A_PORT      GPIOA
#define MUX_FREQUENCY_A_PIN       GPIO_Pin_13

#define MUX_FREQUENCY_B_PORT      GPIOC
#define MUX_FREQUENCY_B_PIN       GPIO_Pin_9

#define MUX_FREQUENCY_C_PORT      GPIOC
#define MUX_FREQUENCY_C_PIN       GPIO_Pin_7


// Frequency input selection macro 
#define MUX_FREQUENCY_A_1()       GPIO_SetBits( MUX_FREQUENCY_A_PORT, MUX_FREQUENCY_A_PIN )
#define MUX_FREQUENCY_A_0()       GPIO_ResetBits( MUX_FREQUENCY_A_PORT, MUX_FREQUENCY_A_PIN )

#define MUX_FREQUENCY_B_1()       GPIO_SetBits( MUX_FREQUENCY_B_PORT, MUX_FREQUENCY_B_PIN )
#define MUX_FREQUENCY_B_0()       GPIO_ResetBits( MUX_FREQUENCY_B_PORT, MUX_FREQUENCY_B_PIN )

#define MUX_FREQUENCY_C_1()       GPIO_SetBits( MUX_FREQUENCY_C_PORT, MUX_FREQUENCY_C_PIN )
#define MUX_FREQUENCY_C_0()       GPIO_ResetBits( MUX_FREQUENCY_C_PORT, MUX_FREQUENCY_C_PIN )




/* Exported types ------------------------------------------------------------*/
enum stateHwDAQ_Frequency {
    HW_DAQ_FREQUENCY_INIT,
    HW_DAQ_FREQUENCY_GET_SINGLE,
    HW_DAQ_FREQUENCY_GET_AVERAGED,
    HW_DAQ_FREQUENCY_STOP,
    HW_DAQ_FREQUENCY_IDLE
};

// Select IC
typedef enum {
    FREQ_CHANNEL_1 = 0,
    FREQ_CHANNEL_2,
    FREQ_CHANNEL_3,
    FREQ_CHANNEL_4,
    FREQ_CHANNEL_5,
    FREQ_CHANNEL_6,
    FREQ_CHANNEL_7,
    FREQ_CHANNEL_8
} NChannelFreq_t;


// Measured frequency data
typedef struct {
    float frequency_kHz;
    float pulseHigh_ns;
    float pulseLow_ns;
}FreqPWMData_t;


#ifndef CALIBRATION_DATA_TYPEDEF
#define CALIBRATION_DATA_TYPEDEF
typedef struct {
    float slope;
    float offset;
} CalibrationData_t;
#endif

typedef struct {
    enum stateHwDAQ_Frequency stateHwDAQ_Frequency;
    NChannelFreq_t nChannelFrequency;
    FreqPWMData_t freqPWMData;
    int32_t numberAverages;
} HwDAQ_FrequencyQueueData_t;


/* Exported functions --------------------------------------------------------*/
HwAPI_Status_t HwAPI_DAQ_Frequency_GetSingle( NChannelFreq_t nChannel, FreqPWMData_t *valueFreq );
HwAPI_Status_t HwAPI_DAQ_Frequency_GetAveraged( NChannelFreq_t nChannel, FreqPWMData_t *valueFreq, int32_t numberAverages );
HwAPI_Status_t HwAPI_DAQ_Frequency_Stop( void );

void vTask_HwDAQ_Frequency( void *pvParameters );
HwAPI_BootStatus_t HwAPI_DAQ_Frequency_Run( void );

#endif /* _HWAPI_DAQ_FREQUENCY_H_*/
/* End of file */
