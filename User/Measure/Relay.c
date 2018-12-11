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

#include "Relay.h"

#define RelayK1_On()        GPIO_SetBits(GPIOH, GPIO_Pin_1)
#define RelayK1_Off()       GPIO_ResetBits(GPIOH, GPIO_Pin_1)

#define RelayK2_On()        GPIO_SetBits(GPIOC, GPIO_Pin_15)
#define RelayK2_Off()       GPIO_ResetBits(GPIOC, GPIO_Pin_15)

#define RelayK3_On()        GPIO_SetBits(GPIOC, GPIO_Pin_13)
#define RelayK3_Off()       GPIO_ResetBits(GPIOC, GPIO_Pin_13)

#define RelayK4_On()        GPIO_SetBits(GPIOD, GPIO_Pin_4)
#define RelayK4_Off()       GPIO_ResetBits(GPIOD, GPIO_Pin_4)

#define RelayK5_On()        GPIO_SetBits(GPIOD, GPIO_Pin_2)
#define RelayK5_Off()       GPIO_ResetBits(GPIOD, GPIO_Pin_2)

#define RelayK6_On()        GPIO_SetBits(GPIOD, GPIO_Pin_0)
#define RelayK6_Off()       GPIO_ResetBits(GPIOD, GPIO_Pin_0)

#define RelayK7_On()        GPIO_SetBits(GPIOC, GPIO_Pin_11)
#define RelayK7_Off()       GPIO_ResetBits(GPIOC, GPIO_Pin_11)


void InitRelayAll(void)
{
    GPIO_InitTypeDef GPIO_cfg;
    
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);

// Relay K1
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_1;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOH, &GPIO_cfg);

// Relay K2
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_15;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_cfg);

// Relay K3
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_13;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_cfg);


// Relay K4
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_4;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOD, &GPIO_cfg);

// Relay K5
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_2;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOD, &GPIO_cfg);

// Relay K6
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_0;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOD, &GPIO_cfg);

// Relay K7
    GPIO_StructInit(&GPIO_cfg);
    GPIO_cfg.GPIO_Pin = GPIO_Pin_11;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(GPIOC, &GPIO_cfg);


    RelayK1_Off();
    RelayK2_Off();
    RelayK3_Off();
    RelayK4_Off();
    RelayK5_Off();
    RelayK6_Off();
    RelayK7_Off();
}


void RelaySet(enum relay relay)
{
    switch (relay)
    {
        case RELAY_K1:
            RelayK1_On();
            break;

        case RELAY_K2:
            RelayK2_On();
            break;

        case RELAY_K3:
            RelayK3_On();
            break;

        case RELAY_K4:
            RelayK4_On();
            break;

        case RELAY_K5:
            RelayK5_On();
            break;

        case RELAY_K6:
            RelayK6_On();
            break;

        case RELAY_K7:
            RelayK7_On();
            break;
        default:
            break;
    }
}


void RelayClear(enum relay relay)
{
    switch (relay)
    {
        case RELAY_K1:
            RelayK1_Off();
            break;

        case RELAY_K2:
            RelayK2_Off();
            break;

        case RELAY_K3:
            RelayK3_Off();
            break;

        case RELAY_K4:
            RelayK4_Off();
            break;

        case RELAY_K5:
            RelayK5_Off();
            break;

        case RELAY_K6:
            RelayK6_Off();
            break;

        case RELAY_K7:
            RelayK7_Off();
            break;
        default:
            break;
    }
}


void RelayClearAll(void)
{
    RelayK1_Off();
    RelayK2_Off();
    RelayK3_Off();
    RelayK4_Off();
    RelayK5_Off();
    RelayK6_Off();
    RelayK7_Off();
}





/* End of file */
