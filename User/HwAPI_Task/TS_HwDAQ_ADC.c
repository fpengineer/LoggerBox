/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw DAQ ADC

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f4xx.h"

#include "defines.h"

#include "HwAPI.h"

#include "AD747x.h"
#include "delay.h"

TaskHandle_t xTask_HwDAQ_ADC;
QueueHandle_t xQueue_HwDAQ_ADC_Rx;
QueueHandle_t xQueue_HwDAQ_ADC_Tx;
volatile HwAPI_BootStatus_t bootStatus_HwDAQ_ADC = HW_TASK_BOOT_IDLE;


// Declare private functions
static void InitDAQ_ADCHardware( void );
static void SelectInputADC( NChannelADC_t nChannel, NSourceADC_t nSource );
static ValueDAQ_ADC_t GetSingleADC( void );
static ValueDAQ_ADC_t GetAveragedADC( int32_t numberAverages );

// Declare private variables


void vTask_HwDAQ_ADC( void *pvParameters )
{
    HwDAQ_ADCQueueData_t hwDAQ_ADCQueueData;
    
    hwDAQ_ADCQueueData.stateHwDAQ_ADC = HW_DAQ_ADC_INIT;            
    xQueueSend( xQueue_HwDAQ_ADC_Rx, &hwDAQ_ADCQueueData, NULL ); 

    while ( 1 )
    {
        xQueueReceive( xQueue_HwDAQ_ADC_Rx, &hwDAQ_ADCQueueData, portMAX_DELAY );
        switch ( hwDAQ_ADCQueueData.stateHwDAQ_ADC )
        {
            case HW_DAQ_ADC_INIT:
            {
                InitDAQ_ADCHardware();
				
                bootStatus_HwDAQ_ADC = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_DAQ_ADC_SELECT_INPUT:
            {
                SelectInputADC( hwDAQ_ADCQueueData.nChannelADC, hwDAQ_ADCQueueData.nSourceADC );
				break;
            }

            case HW_DAQ_ADC_GET_SINGLE:
            {
                hwDAQ_ADCQueueData.valueADC = GetSingleADC();
                xQueueSend( xQueue_HwDAQ_ADC_Tx, &hwDAQ_ADCQueueData, NULL ); 
				break;
            }

            case HW_DAQ_ADC_GET_AVERAGED:
            {
                hwDAQ_ADCQueueData.valueADC = GetAveragedADC( hwDAQ_ADCQueueData.numberAverages );
                xQueueSend( xQueue_HwDAQ_ADC_Tx, &hwDAQ_ADCQueueData, NULL ); 
				break;
            }

            case HW_DAQ_ADC_IDLE:
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
static void InitDAQ_ADCHardware( void )
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
    
    ADC_CS_1();
}









//*************************************************
//
// Private function
//
// Select input for ADC
//
//*************************************************
static void SelectInputADC( NChannelADC_t nChannel, NSourceADC_t nSource )
{
    switch ( nChannel )
    {
        case ADC_CHANNEL_1:
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_1();
            break;

        case ADC_CHANNEL_2:
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_1();
            break;

        case ADC_CHANNEL_3:
            MUX_CHANNEL_A_1();
            MUX_CHANNEL_B_0();
            break;

        case ADC_CHANNEL_4:
            MUX_CHANNEL_A_0();
            MUX_CHANNEL_B_0();
            break;

        default:
            break;
    }
    
    switch ( nSource )
    {
        case ADC_SOURCE_1:
            MUX_SOURCE_A_1();
            MUX_SOURCE_B_1();
            MUX_SOURCE_C_1();
            break;

        case ADC_SOURCE_2:
            MUX_SOURCE_A_0();
            MUX_SOURCE_B_1();
            MUX_SOURCE_C_1();
            break;

        case ADC_SOURCE_3:
            MUX_SOURCE_A_1();
            MUX_SOURCE_B_0();
            MUX_SOURCE_C_1();
            break;

        case ADC_SOURCE_4:
            MUX_SOURCE_A_0();
            MUX_SOURCE_B_0();
            MUX_SOURCE_C_1();
            break;

        case ADC_SOURCE_5:
            MUX_SOURCE_A_1();
            MUX_SOURCE_B_1();
            MUX_SOURCE_C_0();
            break;

        case ADC_SOURCE_6:
            MUX_SOURCE_A_0();
            MUX_SOURCE_B_1();
            MUX_SOURCE_C_0();
            break;

        case ADC_SOURCE_7:
            MUX_SOURCE_A_1();
            MUX_SOURCE_B_0();
            MUX_SOURCE_C_0();
            break;

        case ADC_SOURCE_8:
            MUX_SOURCE_A_0();
            MUX_SOURCE_B_0();
            MUX_SOURCE_C_0();
            break;

        default:
            break;
    }
}


//*************************************************
//
// Private function
//
// Get single ADC
//
//*************************************************
ValueDAQ_ADC_t GetSingleADC( void )
{
    ValueDAQ_ADC_t valueADC = 0;
    
    taskENTER_CRITICAL();
    ADC_CS_0();

    delay_us(1);
    while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_TXE ) == RESET ){;}
    SPI_I2S_SendData( SPI2, 0xff );

    while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY ) == SET ){;}
    while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_RXNE ) == RESET ){;}
    valueADC = SPI_I2S_ReceiveData( SPI2 ) << 8;
    SPI_I2S_SendData( SPI2, 0xff );

    while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY ) == SET ){;}
    while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_RXNE ) == RESET ){;}
    valueADC |= SPI_I2S_ReceiveData( SPI2 );


#if defined( AD7476 )

#elif defined( ad7477 )
    valueADC >>= 2; 

#elif defined( ad7478 )
    valueADC >>= 4; 
#endif        

    ADC_CS_1();
    taskEXIT_CRITICAL();

    return valueADC;
}


//*************************************************
//
// Private function
//
// Get single ADC
//
//*************************************************
ValueDAQ_ADC_t GetAveragedADC( int32_t numberAverages )
{
    ValueDAQ_ADC_t valueADC = 0;
    float temp = 0.0f;
    int32_t i = 0;
    
    taskENTER_CRITICAL();
    for ( i = 0; i < numberAverages; i++ )
    {
        ADC_CS_0();

        delay_us(1);
        while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_TXE ) == RESET ){;}
        SPI_I2S_SendData( SPI2, 0xff );

        while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY ) == SET ){;}
        while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_RXNE ) == RESET ){;}
        valueADC = SPI_I2S_ReceiveData( SPI2 ) << 8;
        SPI_I2S_SendData( SPI2, 0xff );

        while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_BSY ) == SET ){;}
        while( SPI_I2S_GetFlagStatus( SPI2, SPI_I2S_FLAG_RXNE ) == RESET ){;}
        valueADC |= SPI_I2S_ReceiveData( SPI2 );

#if defined( AD7476 )

#elif defined( ad7477 )
        valueADC >>= 2; 

#elif defined( ad7478 )
        valueADC >>= 4; 
#endif        

        ADC_CS_1();
    
        temp += ( float )valueADC;
    }
    taskEXIT_CRITICAL();
    
    return ( ValueDAQ_ADC_t )roundf( temp / numberAverages );
}


/* End of file */
