/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw DAQ Frequency

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

#include "HwAPI.h"

#include "delay.h"

TaskHandle_t xTask_HwDAQ_Frequency;
QueueHandle_t xQueue_HwDAQ_Frequency_Rx;
QueueHandle_t xQueue_HwDAQ_Frequency_Tx;
HwAPI_BootStatus_t bootStatus_HwDAQ_Frequency = HW_TASK_BOOT_IDLE;


// Declare private functions
static void InitDAQ_FrequencyHardware( void );
static void SelectInputFrequency( NChannelFreq_t nChannel );
static FreqPWMData_t GetSingleFrequency( NChannelFreq_t nChannel );
static FreqPWMData_t GetAveragedFrequency( NChannelFreq_t nChannel, int32_t numberAverages );

// Declare private variables


void vTask_HwDAQ_Frequency( void *pvParameters )
{
    HwDAQ_FrequencyQueueData_t hwDAQ_FrequencyQueueData;
    
    hwDAQ_FrequencyQueueData.stateHwDAQ_Frequency = HW_DAQ_FREQUENCY_INIT;            
    xQueueSend( xQueue_HwDAQ_Frequency_Rx, &hwDAQ_FrequencyQueueData, NULL ); 

    while ( 1 )
    {
        xQueueReceive( xQueue_HwDAQ_Frequency_Rx, &hwDAQ_FrequencyQueueData, portMAX_DELAY );
        switch ( hwDAQ_FrequencyQueueData.stateHwDAQ_Frequency )
        {
            case HW_DAQ_FREQUENCY_INIT:
            {
                InitDAQ_FrequencyHardware();

                bootStatus_HwDAQ_Frequency = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_DAQ_FREQUENCY_GET_SINGLE:
            {
                hwDAQ_FrequencyQueueData.freqPWMData = GetSingleFrequency( hwDAQ_FrequencyQueueData.nChannelFrequency );
                xQueueSend( xQueue_HwDAQ_Frequency_Tx, &hwDAQ_FrequencyQueueData, NULL ); 
				break;
            }

            case HW_DAQ_FREQUENCY_GET_AVERAGED:
            {
                hwDAQ_FrequencyQueueData.freqPWMData = GetAveragedFrequency( hwDAQ_FrequencyQueueData.nChannelFrequency, hwDAQ_FrequencyQueueData.numberAverages );
                xQueueSend( xQueue_HwDAQ_Frequency_Tx, &hwDAQ_FrequencyQueueData, NULL ); 
				break;
            }

            case HW_DAQ_FREQUENCY_IDLE:
			{

				break;
			}            

            default:
                break;
        }
    }
}

//*************************************************
//
// Private function
//
// Initialize hardware
//
//*************************************************
static void InitDAQ_FrequencyHardware( void )
{
    GPIO_InitTypeDef GPIO_cfg;
    TIM_TimeBaseInitTypeDef timer_base;
    TIM_ICInitTypeDef timer_ic;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

// MUX FREQUENCY A
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_13;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_cfg);

// MUX FREQUENCY B
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_9;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_cfg);

// MUX FREQUENCY C
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_7;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_cfg);


// TIM1 CH2
    GPIO_StructInit(&GPIO_cfg);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);

    GPIO_cfg.GPIO_Pin = GPIO_Pin_9;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_AF;
    GPIO_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_100MHz;
//    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOA, &GPIO_cfg);
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    
    TIM_TimeBaseStructInit(&timer_base);
    timer_base.TIM_Prescaler = 0;
    TIM_TimeBaseInit(TIM1, &timer_base);
    
    timer_ic.TIM_Channel = TIM_Channel_2;
    timer_ic.TIM_ICPolarity = TIM_ICPolarity_Rising;
    timer_ic.TIM_ICSelection = TIM_ICSelection_DirectTI;
    timer_ic.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    timer_ic.TIM_ICFilter = 0;
    
    TIM_PWMIConfig(TIM1, &timer_ic);
    TIM_SelectInputTrigger(TIM1, TIM_TS_TI2FP2);
    
    TIM_SelectSlaveMode(TIM1, TIM_SlaveMode_Reset);
    TIM_SelectMasterSlaveMode(TIM1, TIM_MasterSlaveMode_Enable);
    
//    TIM_ITConfig(TIM1, TIM_IT_CC1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
//    NVIC_EnableIRQ(TIM1_IRQn);
}


//*************************************************
//
// Private function
//
// Select input for frequency source
//
//*************************************************
static void SelectInputFrequency( NChannelFreq_t nChannel )
{
    switch ( nChannel )
    {
        case FREQ_CHANNEL_1:
            MUX_FREQUENCY_A_0();
            MUX_FREQUENCY_B_0();
            MUX_FREQUENCY_C_0();
            break;

        case FREQ_CHANNEL_2:
            MUX_FREQUENCY_A_1();
            MUX_FREQUENCY_B_0();
            MUX_FREQUENCY_C_0();
            break;

        case FREQ_CHANNEL_3:
            MUX_FREQUENCY_A_0();
            MUX_FREQUENCY_B_1();
            MUX_FREQUENCY_C_0();
            break;

        case FREQ_CHANNEL_4:
            MUX_FREQUENCY_A_1();
            MUX_FREQUENCY_B_1();
            MUX_FREQUENCY_C_0();
            break;

        case FREQ_CHANNEL_5:
            MUX_FREQUENCY_A_0();
            MUX_FREQUENCY_B_0();
            MUX_FREQUENCY_C_1();
            break;

        case FREQ_CHANNEL_6:
            MUX_FREQUENCY_A_1();
            MUX_FREQUENCY_B_0();
            MUX_FREQUENCY_C_1();
            break;

        case FREQ_CHANNEL_7:
            MUX_FREQUENCY_A_0();
            MUX_FREQUENCY_B_1();
            MUX_FREQUENCY_C_1();
            break;

        case FREQ_CHANNEL_8:
            MUX_FREQUENCY_A_1();
            MUX_FREQUENCY_B_1();
            MUX_FREQUENCY_C_1();
            break;

        default:
            break;
    }
}


//*************************************************
//
// Private function
//
// Get single frequency values
//
//*************************************************
FreqPWMData_t GetSingleFrequency( NChannelFreq_t nChannel )
{
    FreqPWMData_t freqPWMData = { 0.0f, 0.0f, 0.0f };
    int32_t i = 0;
    uint16_t countPulseLow = 0;
    uint16_t countPulseHigh = 0;
    
    SelectInputFrequency( nChannel );

    taskENTER_CRITICAL();
    TIM_ClearFlag( TIM1, ( TIM_FLAG_CC1 | TIM_FLAG_CC2 ) );
    while ( ( TIM_GetFlagStatus( TIM1, ( TIM_FLAG_CC1 | TIM_FLAG_CC2 ) ) == RESET ) && ( i < 50 ) )
    {
        i++;
    }
    taskEXIT_CRITICAL();

    if ( i >= 50 )
    {
        freqPWMData.pulseHigh_ns = -1.0f;
        freqPWMData.pulseLow_ns = -1.0f;
        freqPWMData.frequency_kHz = -1.0f;
    }
    else
    {
        countPulseHigh = ( uint16_t )TIM_GetCapture1( TIM1 );
        countPulseLow = ( ( uint16_t )TIM_GetCapture2( TIM1 ) - countPulseHigh );

        freqPWMData.pulseHigh_ns = ( ( 1.0f / 168000000.0f ) * ( float )countPulseHigh ) * 1000000000.0f;
        freqPWMData.pulseLow_ns = ( ( 1.0f / 168000000.0f ) * ( float )countPulseLow ) * 1000000000.0f;
        freqPWMData.frequency_kHz = ( 1.0f / ( ( freqPWMData.pulseLow_ns / 1000000000.0f ) + ( freqPWMData.pulseHigh_ns / 1000000000.0f ) ) / 1000.0f );
    }

    return freqPWMData;
}


//*************************************************
//
// Private function
//
// Get single ADC
//
//*************************************************
FreqPWMData_t GetAveragedFrequency( NChannelFreq_t nChannel, int32_t numberAverages )
{
    FreqPWMData_t freqPWMData = { 0.0f, 0.0f, 0.0f };
    int32_t i = 0;
    uint32_t countPulseLow = 0;
    uint32_t countPulseHigh = 0;
    
    SelectInputFrequency( nChannel );

    taskENTER_CRITICAL();
    for ( i = 0; i < numberAverages; i++ )
    {
        TIM_ClearFlag( TIM1, ( TIM_FLAG_CC1 | TIM_FLAG_CC2 ) );
        while ( ( TIM_GetFlagStatus( TIM1, ( TIM_FLAG_CC1 | TIM_FLAG_CC2 ) ) == RESET ) && ( i < 50 ) )
        {
            i++;
        }
    
        if ( i >= 50 )
        {
            countPulseHigh = 0;
            countPulseLow = 0;
            break;
        }
        else
        {
            countPulseHigh += ( uint32_t )TIM_GetCapture1( TIM1 );
            countPulseLow += (( uint32_t )TIM_GetCapture2( TIM1 ) - countPulseHigh );
        }
    }
    taskEXIT_CRITICAL();
    
    countPulseHigh /= numberAverages;
    countPulseLow /= numberAverages;
    
    freqPWMData.pulseHigh_ns = ( ( 1.0f / 168000000.0f ) * ( float )countPulseHigh ) * 1000000000.0f;
    freqPWMData.pulseLow_ns = ( ( 1.0f / 168000000.0f ) * ( float )countPulseLow ) * 1000000000.0f;
    freqPWMData.frequency_kHz = ( 1.0f / ( ( freqPWMData.pulseLow_ns / 1000000000.0f ) + ( freqPWMData.pulseHigh_ns / 1000000000.0f ) ) / 1000.0f );

    return freqPWMData;
}


/* End of file */
