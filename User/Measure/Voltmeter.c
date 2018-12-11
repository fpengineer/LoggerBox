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
#include "stm32f4xx_spi.h"

#include "Voltmeter.h"

static void delay(volatile uint32_t delay_i)
{
    while	(delay_i!=0)
    {
    delay_i--;
    }
}

static float CalculateADC(int16_t valueADC)
{
    return ((5.0f / 16384.0f) * (float)valueADC) * 1.0f + 0.0f;
}


void InitVoltmeter(void)
{
    GPIO_InitTypeDef GPIO_cfg;
    SPI_InitTypeDef SPI_cfg;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

// MUX SOURCE A
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_7;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

// MUX SOURCE B
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_10;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

// MUX CHANNEL A
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_9;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

// MUX CHANNEL B
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_12;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

// ADC1 CS
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_8;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

   
// SPI3 SCK, MOSI, MISO
    GPIO_StructInit(&GPIO_cfg);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

    GPIO_cfg.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_AF;
    GPIO_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB, &GPIO_cfg);
    
// SPI 2
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);

    SPI_StructInit(&SPI_cfg);
    SPI_cfg.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_cfg.SPI_DataSize = SPI_DataSize_8b;
    SPI_cfg.SPI_CPOL = SPI_CPOL_High;
    SPI_cfg.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_cfg.SPI_NSS = SPI_NSS_Soft;
    SPI_cfg.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
    SPI_cfg.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_cfg.SPI_Mode = SPI_Mode_Master;
    SPI_Init(SPI2, &SPI_cfg);
    SPI_Cmd(SPI2, ENABLE);
    SPI_NSSInternalSoftwareConfig(SPI2, SPI_NSSInternalSoft_Set);
    
    ADC1_CS_1();
}

void VoltmeterSelectInput(enum voltmeterInput voltmeterInput)
{
    switch (voltmeterInput)
    {
        case VOLTMETER_G1_V:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_G2_V:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_G3_V:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_G4_V:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_G1_I:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_G2_I:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_G3_I:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_G4_I:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_IC1_VOUT:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_IC2_VOUT:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_IC3_VOUT:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_IC4_VOUT:
            MUX_SOURCE_A_1();    
            MUX_SOURCE_B_0();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_IC1_COMP:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_IC2_COMP:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_1();
            break;

        case VOLTMETER_IC3_COMP:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_0();
            break;

        case VOLTMETER_IC4_COMP:
            MUX_SOURCE_A_0();    
            MUX_SOURCE_B_1();    
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_0();
            break;

        default:
            break;
    }
}

float VoltmeterGetSingleValue(void)
{
    int16_t valueADC = 0;
    
    ADC1_CS_0();
    delay(1);
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){;}
    SPI_I2S_SendData(SPI2, 0xff);
//    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET){;}
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){;}
    valueADC = SPI_I2S_ReceiveData(SPI2) << 8;
    SPI_I2S_SendData(SPI2, 0xff);
//    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET){;}
    while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){;}
    valueADC |= SPI_I2S_ReceiveData(SPI2);
//    delay(100);//15);
    ADC1_CS_1();

    return CalculateADC(valueADC);
//    return valueADC;
}

float VoltmeterGetAveragedValue(int32_t numberAverages)
{
    int16_t valueADC = 0;
    int32_t temp = 0;
    int32_t i = 0;
    
    for (i = 0; i < numberAverages; i++)
    {
        ADC1_CS_0();
        delay(1);
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_TXE) == RESET){;}
        SPI_I2S_SendData(SPI2, 0xff);
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET){;}
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){;}
        valueADC = SPI_I2S_ReceiveData(SPI2) << 8;
        SPI_I2S_SendData(SPI2, 0xff);
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_BSY) == SET){;}
        while(SPI_I2S_GetFlagStatus(SPI2, SPI_I2S_FLAG_RXNE) == RESET){;}
        valueADC |= SPI_I2S_ReceiveData(SPI2);
        ADC1_CS_1();
        temp += valueADC;
        delay(1);
    }

    temp /= numberAverages;


    return CalculateADC((int16_t)temp);
}





/* End of file */
