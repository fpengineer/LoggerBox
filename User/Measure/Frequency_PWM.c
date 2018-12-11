/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Voltmeter functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"

#include "Frequency_PWM.h"


/*
static float CalculateFrequency(int16_t valueADC)
{
    return (float)valueADC;
}
*/

void InitFrequencyPWMMeter(void)
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

void FrequencySelectInput(enum frequencyInput frequencyInput)
{
    switch (frequencyInput)
    {
        case FREQUENCY_IC1:
            MUX_FREQUENCY_C_0();
            MUX_FREQUENCY_B_0();    
            MUX_FREQUENCY_A_0();    
            break;

        case FREQUENCY_IC2:
            MUX_FREQUENCY_C_1();
            MUX_FREQUENCY_B_0();    
            MUX_FREQUENCY_A_0();    
            break;

        case FREQUENCY_IC3:
            MUX_FREQUENCY_C_0();
            MUX_FREQUENCY_B_1();    
            MUX_FREQUENCY_A_0();    
            break;

        case FREQUENCY_IC4:
            MUX_FREQUENCY_C_1();
            MUX_FREQUENCY_B_1();    
            MUX_FREQUENCY_A_0();    
            break;

        case FREQUENCY_IC5:
            MUX_FREQUENCY_C_0();
            MUX_FREQUENCY_B_0();    
            MUX_FREQUENCY_A_1();    
            break;

        case FREQUENCY_IC6:
            MUX_FREQUENCY_C_1();
            MUX_FREQUENCY_B_0();    
            MUX_FREQUENCY_A_1();    
            break;

        case FREQUENCY_IC7:
            MUX_FREQUENCY_C_0();
            MUX_FREQUENCY_B_1();    
            MUX_FREQUENCY_A_1();    
            break;

        case FREQUENCY_IC8:
            MUX_FREQUENCY_C_1();
            MUX_FREQUENCY_B_1();    
            MUX_FREQUENCY_A_1();    
            break;

        default:
            break;
    }
}

void FrequencyGetSingleValue(FreqPWMData_t *freqPWMData)
{

    int32_t i = 0;
    uint16_t countPulseLow = 0;
    uint16_t countPulseHigh = 0;
    freqPWMData->frequency_kHz = 0.0f;
    freqPWMData->pulseHigh_ns = 0.0f;
    freqPWMData->pulseLow_ns = 0.0f;

    __disable_irq();
    TIM_ClearFlag(TIM1, (TIM_FLAG_CC1 | TIM_FLAG_CC2));
    i = 0;
    while ((TIM_GetFlagStatus(TIM1, (TIM_FLAG_CC1 | TIM_FLAG_CC2)) == RESET) && (i < 50))
    {
        i++;
    }
    __enable_irq();

    if (i >= 50)
    {
        freqPWMData->pulseHigh_ns = -1.0f;
        freqPWMData->pulseLow_ns = -1.0f;
        freqPWMData->frequency_kHz = -1.0f;
    }
    else
    {
        countPulseHigh = (uint16_t)TIM_GetCapture1(TIM1);
        countPulseLow = ((uint16_t)TIM_GetCapture2(TIM1) - countPulseHigh);

//       freqPWMData->pulseHigh_ns = (float)countPulseHigh;
//       freqPWMData->pulseLow_ns = (float)countPulseLow;
//       freqPWMData->frequency_kHz = (float)i;//-1.0f;
        
        freqPWMData->pulseHigh_ns = ((1.0f / 168000000.0f) * (float)countPulseHigh) * 1000000000.0f;
        freqPWMData->pulseLow_ns = ((1.0f / 168000000.0f) * (float)countPulseLow) * 1000000000.0f;
        freqPWMData->frequency_kHz = (1.0f / ((freqPWMData->pulseLow_ns / 1000000000.0f) + (freqPWMData->pulseHigh_ns / 1000000000.0f) ) / 1000.0f);
    }
}

void FrequencyGetAveragedValue(int32_t numberAverages, FreqPWMData_t *freqPWMData)
{
    int32_t temp = 0;
    int32_t i = 0;
    
    for (i = 0; i < numberAverages; i++)
    {
        temp++;
    }

    temp /= numberAverages;

    freqPWMData->frequency_kHz = 0.0f;
    freqPWMData->pulseHigh_ns = 0.0f;
    freqPWMData->pulseLow_ns = 0.0f;
    
}





/* End of file */
