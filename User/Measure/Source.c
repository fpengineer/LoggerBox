/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Source G1, G2, G3 functions

*******************************************************************************************************/
#include <stdint.h>
#include <math.h>
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"

#include "Source.h"

static void delay(volatile uint32_t delay_i)
{
    while	(delay_i!=0)
    {
    delay_i--;
    }
}

static uint16_t CalculateDAC(float value)
{
    uint16_t temp;

    temp = (uint16_t)roundf((value * 4096.0f) / 15.0f);
    if (temp > 4095)
    {
        temp = 4095;
    }
    return temp;
}


void InitSourceAll(void)
{
    GPIO_InitTypeDef GPIO_cfg;
    SPI_InitTypeDef SPI_cfg;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

// DAC1 CS
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_9;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB, &GPIO_cfg);

// DAC2 CS
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_1;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

// DAC3 CS
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_3;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);

// DAC4 CS
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_5;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOE, &GPIO_cfg);




// SPI3 SCK, MOSI, MISO
    GPIO_StructInit(&GPIO_cfg);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_SPI3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI3);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI3);

    GPIO_cfg.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_3 | GPIO_Pin_5;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_AF;
    GPIO_cfg.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOB, &GPIO_cfg);
    
// SPI3 - Init Module    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);

    SPI_StructInit(&SPI_cfg);
    SPI_cfg.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_cfg.SPI_DataSize = SPI_DataSize_8b;
    SPI_cfg.SPI_CPOL = SPI_CPOL_High;
    SPI_cfg.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_cfg.SPI_NSS = SPI_NSS_Soft;
    SPI_cfg.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
    SPI_cfg.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_cfg.SPI_Mode = SPI_Mode_Master;
    SPI_Init(SPI3, &SPI_cfg);
    SPI_Cmd(SPI3, ENABLE);
    SPI_NSSInternalSoftwareConfig(SPI3, SPI_NSSInternalSoft_Set);
    
    DAC1_CS_1();
    DAC2_CS_1();
    DAC3_CS_1();
    DAC4_CS_1();
}


void SetSourceG1(float value)
{
    uint16_t valueDAC = 0;
    value = value * 1.012f + 0.0f;
    valueDAC = CalculateDAC(value);
    valueDAC = (valueDAC << 2) & 0x3fff;
    
    DAC1_CS_0();
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){;}
    SPI_I2S_SendData(SPI3, (valueDAC >> 8) & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    SPI_I2S_SendData(SPI3,  valueDAC & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    delay(15);
    DAC1_CS_1();
}

void SetSourceG2(float value)
{
    uint16_t valueDAC = 0;
    value = value * 1.005f + (-0.015f);
    valueDAC = CalculateDAC(value);
    valueDAC = (valueDAC << 2) & 0x3fff;
    
    DAC2_CS_0();
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){;}
    SPI_I2S_SendData(SPI3, (valueDAC >> 8) & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    SPI_I2S_SendData(SPI3,  valueDAC & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    delay(15);
    DAC2_CS_1();
}

void SetSourceG3(float value)
{
    uint16_t valueDAC = 0;
    value = value * 1.007f + 0.017f;
    valueDAC = CalculateDAC(value);
    valueDAC = (valueDAC << 2) & 0x3fff;
    
    DAC3_CS_0();
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){;}
    SPI_I2S_SendData(SPI3, (valueDAC >> 8) & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    SPI_I2S_SendData(SPI3,  valueDAC & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    delay(15);
    DAC3_CS_1();
}

void SetSourceG4(float value)
{
    uint16_t valueDAC = 0;
    value = value * 1.009f + (-0.07f);
    valueDAC = CalculateDAC(value);
    valueDAC = (valueDAC << 2) & 0x3fff;
    
    DAC4_CS_0();
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_TXE) == RESET){;}
    SPI_I2S_SendData(SPI3, (valueDAC >> 8) & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    SPI_I2S_SendData(SPI3,  valueDAC & 0x00ff);
    delay(5);
    while(SPI_I2S_GetFlagStatus(SPI3, SPI_I2S_FLAG_BSY) == SET){;}
    delay(15);
    DAC4_CS_1();
}


/* End of file */
