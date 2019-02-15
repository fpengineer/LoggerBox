/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw Voltage Source

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "stm32f4xx.h"

#include "defines.h"

#include "HwAPI.h"

#include "AD56x0.h"
#include "delay.h"

TaskHandle_t xTask_HwVoltageSource;
QueueHandle_t xQueue_HwVoltageSource_Rx;
//QueueHandle_t xQueue_HwVoltageSource_Tx;
volatile HwAPI_BootStatus_t bootStatus_HwVoltageSource = HW_TASK_BOOT_IDLE;


// Declare private functions
static void InitVoltageSourceHardware( void );
void SetSourceValue( NSource_t nSource, ValueAD56x0_t valueDAC );

// Declare private variables


void vTask_HwVoltageSource( void *pvParameters )
{
    HwVoltageSourceQueueData_t hwVoltageSourceQueueData;
    
    hwVoltageSourceQueueData.stateHwVoltageSource = HW_VOLTAGE_SOURCE_INIT;            
    xQueueSend( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, NULL ); 

    while ( 1 )
    {
        xQueueReceive( xQueue_HwVoltageSource_Rx, &hwVoltageSourceQueueData, portMAX_DELAY );
        switch ( hwVoltageSourceQueueData.stateHwVoltageSource )
        {
            case HW_VOLTAGE_SOURCE_INIT:
            {
				InitVoltageSourceHardware();
                SetSourceValue( NSOURCE_1, 0 );
                SetSourceValue( NSOURCE_2, 0 );
                SetSourceValue( NSOURCE_3, 0 );
                SetSourceValue( NSOURCE_4, 0 );
				
                bootStatus_HwVoltageSource = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_VOLTAGE_SOURCE_SET:
            {
                SetSourceValue( hwVoltageSourceQueueData.nSource, 
                                hwVoltageSourceQueueData.valueDAC );
				break;
            }

            case HW_VOLTAGE_SOURCE_CLEAR:
            {
                SetSourceValue( hwVoltageSourceQueueData.nSource, 0 );
				break;
            }

            case HW_VOLTAGE_SOURCE_CLEAR_ALL:
            {
                SetSourceValue( NSOURCE_1, 0 );
                SetSourceValue( NSOURCE_2, 0 );
                SetSourceValue( NSOURCE_3, 0 );
                SetSourceValue( NSOURCE_4, 0 );
				break;
            }

            case HW_VOLTAGE_SOURCE_IDLE:
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
static void InitVoltageSourceHardware( void )
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




//*************************************************
//
// Private function
//
// Send value to Source 1
//
//*************************************************
void SetSourceValue( NSource_t nSource, ValueAD56x0_t valueDAC )
{
    taskENTER_CRITICAL();

    switch ( nSource )
    {
        case NSOURCE_1:
            DAC1_CS_0();
            break;
        
        case NSOURCE_2:
            DAC2_CS_0();
            break;
        
        case NSOURCE_3:
            DAC3_CS_0();
            break;
        
        case NSOURCE_4:
            DAC4_CS_0();
            break;
        
        default:
            DAC1_CS_1();
            DAC2_CS_1();
            DAC3_CS_1();
            DAC4_CS_1();
            break;
    }

#if defined( AD5620 ) || defined( AD5640 )
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_TXE ) == RESET ){;}
    SPI_I2S_SendData( SPI3, ( uint16_t )( valueDAC >> 8 ) & 0x00ff );
    delay_us( 5 );
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_BSY ) == SET ){;}
    SPI_I2S_SendData( SPI3, ( uint16_t )valueDAC & 0x00ff );
    delay_us( 5 );
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_BSY ) == SET ){;}
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_RXNE ) == RESET ){;}
    //delay_us( 15 );

#elif defined( ad5660 )
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_TXE ) == RESET ){;}
    SPI_I2S_SendData( SPI3, ( uint16_t )( valueDAC >> 16 ) & 0x00ff );
    delay_us( 5 );
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_BSY ) == SET ){;}
    SPI_I2S_SendData( SPI3, ( uint16_t )( valueDAC >> 8 ) & 0x00ff );
    delay_us( 5 );
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_BSY ) == SET ){;}
    SPI_I2S_SendData( SPI3, ( uint16_t )valueDAC & 0x00ff );
    delay_us( 5 );
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_BSY ) == SET ){;}
    while( SPI_I2S_GetFlagStatus( SPI3, SPI_I2S_FLAG_RXNE ) == RESET ){;}
//    delay_us( 15 );
#endif        
    
    switch ( nSource )
    {
        case NSOURCE_1:
            DAC1_CS_1();
            break;
        
        case NSOURCE_2:
            DAC2_CS_1();
            break;
        
        case NSOURCE_3:
            DAC3_CS_1();
            break;
        
        case NSOURCE_4:
            DAC4_CS_1();
            break;
        
        default:
            DAC1_CS_1();
            DAC2_CS_1();
            DAC3_CS_1();
            DAC4_CS_1();
            break;
    }

    taskEXIT_CRITICAL();
}


/* End of file */
