/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw Relay

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

#include "delay.h"

TaskHandle_t xTask_HwRelay;
QueueHandle_t xQueue_HwRelay_Rx;
QueueHandle_t xQueue_HwRelay_Tx;
volatile HwAPI_BootStatus_t bootStatus_HwRelay = HW_TASK_BOOT_IDLE;


// Declare private functions
static void InitRelayHardware( void );
void RelaySet( NRelay_t nRelay );
void RelayClear( NRelay_t nRelay );
void RelayClearAll( void );

// Declare private variables


void vTask_HwRelay( void *pvParameters )
{
    HwRelayQueueData_t hwRelayQueueData;
    
    hwRelayQueueData.stateHwRelay = HW_RELAY_INIT;            
    xQueueSend( xQueue_HwRelay_Rx, &hwRelayQueueData, NULL ); 

    while ( 1 )
    {
        xQueueReceive( xQueue_HwRelay_Rx, &hwRelayQueueData, portMAX_DELAY );
        switch ( hwRelayQueueData.stateHwRelay )
        {
            case HW_RELAY_INIT:
            {
				InitRelayHardware();
				RelayClearAll();
				
                bootStatus_HwRelay = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_RELAY_SET:
            {
				RelaySet( hwRelayQueueData.nRelay );
                break;
            }

            case HW_RELAY_CLEAR:
            {
				RelayClear( hwRelayQueueData.nRelay );
				break;
            }

            case HW_RELAY_CLEAR_ALL:
            {
				RelayClearAll();
				break;
            }

            case HW_RELAY_IDLE:
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
static void InitRelayHardware( void )
{
    GPIO_InitTypeDef GPIO_cfg;
    
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOC, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOD, ENABLE );
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOH, ENABLE );

// Relay K1
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K1_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K1_PORT, &GPIO_cfg );

// Relay K2
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K2_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K2_PORT, &GPIO_cfg );

// Relay K3
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K3_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K3_PORT, &GPIO_cfg );


// Relay K4
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K4_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K4_PORT, &GPIO_cfg );

// Relay K5
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K5_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K5_PORT, &GPIO_cfg );

// Relay K6
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K6_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K6_PORT, &GPIO_cfg );

// Relay K7
    GPIO_StructInit( &GPIO_cfg );
    GPIO_cfg.GPIO_Pin = NRELAY_K7_PIN;
    GPIO_cfg.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_cfg.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_cfg.GPIO_OType = GPIO_OType_PP;
    GPIO_Init( NRELAY_K7_PORT, &GPIO_cfg );
}




//*************************************************
//
// Private function
//
// set relay
//
//*************************************************
void RelaySet( NRelay_t nRelay )
{
    switch ( nRelay )
    {
        case NRELAY_K1:
            RelayK1_On();
            break;

        case NRELAY_K2:
            RelayK2_On();
            break;

        case NRELAY_K3:
            RelayK3_On();
            break;

        case NRELAY_K4:
            RelayK4_On();
            break;

        case NRELAY_K5:
            RelayK5_On();
            break;

        case NRELAY_K6:
            RelayK6_On();
            break;

        case NRELAY_K7:
            RelayK7_On();
            break;

        default:
            break;
    }
}


//*************************************************
//
// Private function
//
// clear relay
//
//*************************************************
void RelayClear( NRelay_t nRelay )
{
    switch ( nRelay )
    {
        case NRELAY_K1:
            RelayK1_Off();
            break;

        case NRELAY_K2:
            RelayK2_Off();
            break;

        case NRELAY_K3:
            RelayK3_Off();
            break;

        case NRELAY_K4:
            RelayK4_Off();
            break;

        case NRELAY_K5:
            RelayK5_Off();
            break;

        case NRELAY_K6:
            RelayK6_Off();
            break;

        case NRELAY_K7:
            RelayK7_Off();
            break;

        default:
            break;
    }
}

//*************************************************
//
// Private function
//
// clear relay
//
//*************************************************
void RelayClearAll( void )
{
    RelayClear( NRELAY_K1 );
    RelayClear( NRELAY_K2 );
    RelayClear( NRELAY_K3 );
    RelayClear( NRELAY_K4 );
    RelayClear( NRELAY_K5 );    
    RelayClear( NRELAY_K6 );
    RelayClear( NRELAY_K7 );
}
/* End of file */
