/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Hw to boot for all enabled hardware modules

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "HwAPI.h"
#include "TS_HwQueue.h"
#include "TS_HwTask.h"

#include "delay.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

// Hw task
TaskHandle_t xTask_HwSystemTime;
TaskHandle_t xTask_HwTerminal;
TaskHandle_t xTask_HwFatFs;
TaskHandle_t xTask_HwSDCardDetect;
TaskHandle_t xTask_HwVoltageSource;
TaskHandle_t xTask_HwRelay;
TaskHandle_t xTask_HwDAQ_ADC;
TaskHandle_t xTask_HwDAQ_Frequency;
TaskHandle_t xTask_HwStatusLED;
TaskHandle_t xTask_HwSDCardLED;
TaskHandle_t xTask_HwRunButton;

// Hw queues
QueueHandle_t xQueue_HwSystemTime_Rx;
QueueHandle_t xQueue_HwSystemTime_Tx;
QueueHandle_t xQueue_HwTerminal_Rx;
QueueHandle_t xQueue_HwFatFs_Rx;
QueueHandle_t xQueue_HwFatFs_Tx;
QueueHandle_t xQueue_HwSDCardDetect_Rx;
QueueHandle_t xQueue_HwSDCardDetect_Tx;
QueueHandle_t xQueue_HwVoltageSource_Rx;
QueueHandle_t xQueue_HwRelay_Rx;
QueueHandle_t xQueue_HwDAQ_ADC_Rx;
QueueHandle_t xQueue_HwDAQ_ADC_Tx;
QueueHandle_t xQueue_HwDAQ_Frequency_Rx;
QueueHandle_t xQueue_HwDAQ_Frequency_Tx;
QueueHandle_t xQueue_HwStatusLED_Rx;
QueueHandle_t xQueue_HwSDCardLED_Rx;
QueueHandle_t xQueue_HwRunButton_Rx;
QueueHandle_t xQueue_HwRunButton_Tx;


// task boot state
enum bootState bootState_HwSystemTime = TASK_BOOT_IDLE;
enum bootState bootState_HwTerminal = TASK_BOOT_IDLE;
enum bootState bootState_HwFatFs = TASK_BOOT_IDLE;
enum bootState bootState_HwSDCardDetect = TASK_BOOT_IDLE;
enum bootState bootState_HwRelay = TASK_BOOT_IDLE;
enum bootState bootState_HwVoltageSource = TASK_BOOT_IDLE;
enum bootState bootState_HwDAQ_ADC = TASK_BOOT_IDLE;
enum bootState bootState_HwDAQ_Frequency = TASK_BOOT_IDLE;
enum bootState bootState_HwStatusLED = TASK_BOOT_IDLE;
enum bootState bootState_HwSDCardLED = TASK_BOOT_IDLE;
enum bootState bootState_HwRunButton = TASK_BOOT_IDLE;

enum bootState bootState_HwBoot = TASK_BOOT_IDLE;




// Declare private functions

// Declare private variables


void vTask_HwBoot( void *pvParameters )
{

    xQueue_HwSystemTime_Rx = xQueueCreate( 5, sizeof( HwSystemTimeQueueData_t ) );
    xQueue_HwSystemTime_Tx = xQueueCreate( 5, sizeof( HwSystemTimeQueueData_t ) );
    
    xQueue_HwTerminal_Rx = xQueueCreate( 15, sizeof( char[ TERMINAL_BUFFER ] ) );
    
    xQueue_HwFatFs_Rx = xQueueCreate( 10, sizeof( HwFatFsQueueData_t ) );
    xQueue_HwFatFs_Tx = xQueueCreate( 10, sizeof( HwFatFsQueueData_t ) );

    xQueue_HwSDCardDetect_Rx = xQueueCreate( 5, sizeof( HwSDCardDetectQueueData_t ) );
    xQueue_HwSDCardDetect_Tx = xQueueCreate( 5, sizeof( HwSDCardDetectQueueData_t ) );

    xQueue_HwRelay_Rx = xQueueCreate( 5, sizeof( HwRelayQueueData_t ) );

    xQueue_HwVoltageSource_Rx = xQueueCreate( 5, sizeof( HwVoltageSourceQueueData_t ) );

    xQueue_HwDAQ_ADC_Rx = xQueueCreate( 5, sizeof( HwDAQ_ADCQueueData_t ) );
    xQueue_HwDAQ_ADC_Tx = xQueueCreate( 5, sizeof( HwDAQ_ADCQueueData_t ) );

    xQueue_HwDAQ_Frequency_Rx = xQueueCreate( 5, sizeof( HwDAQ_FrequencyQueueData_t ) );
    xQueue_HwDAQ_Frequency_Tx = xQueueCreate( 5, sizeof( HwDAQ_FrequencyQueueData_t ) );

    xQueue_HwStatusLED_Rx = xQueueCreate( 5, sizeof( HwStatusLEDQueueData_t ) );

    xQueue_HwSDCardLED_Rx = xQueueCreate( 5, sizeof( HwSDCardLEDQueueData_t ) );

    xQueue_HwRunButton_Rx = xQueueCreate( 5, sizeof( HwRunButtonQueueData_t ) );
    xQueue_HwRunButton_Tx = xQueueCreate( 5, sizeof( HwRunButtonQueueData_t ) );


// Hw tasks
#if 1       // HwSystemTime
	if( pdTRUE != xTaskCreate(  vTask_HwSystemTime,
                                "Task - HwSystemTime",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSystemTime )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwTerminal
	if( pdTRUE != xTaskCreate(  vTask_HwTerminal,
                                "Task - HwTerminal",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwTerminal )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwFatFs
	if( pdTRUE != xTaskCreate(  vTask_HwFatFs,
                                "Task - HwFatFs",
                                configMINIMAL_STACK_SIZE + 2000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwFatFs )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwSDCardDetect
	if( pdTRUE != xTaskCreate(  vTask_HwSDCardDetect,
                                "Task - HwSDCardDetect",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSDCardDetect )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwRelay
	if( pdTRUE != xTaskCreate(  vTask_HwRelay,
                                "Task - HwRelay",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwRelay )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwVoltageSource
	if( pdTRUE != xTaskCreate(  vTask_HwVoltageSource,
                                "Task - HwVoltageSource",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwVoltageSource )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwMeasureADC
	if( pdTRUE != xTaskCreate(  vTask_HwDAQ_ADC,
                                "Task - HwDAQ_ADC",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwDAQ_ADC )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwDAQ_Frequency
	if( pdTRUE != xTaskCreate(  vTask_HwDAQ_Frequency,
                                "Task - HwDAQ_Frequency",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwDAQ_Frequency )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwStatusLED
	if( pdTRUE != xTaskCreate(  vTask_HwStatusLED,
                                "Task - HwStatusLED",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwStatusLED )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwSDCardLED
	if( pdTRUE != xTaskCreate(  vTask_HwSDCardLED,
                                "Task - HwSDCardLED",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSDCardLED )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 1       // HwRunButton
    if( pdTRUE != xTaskCreate(  vTask_HwRunButton,
                                "Task - HwRunButton",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwRunButton )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif

                                
                                
    // Wait for all hardware tasks run or error
    while ( bootState_HwTerminal != TASK_BOOT_RUN &&
            bootState_HwSystemTime != TASK_BOOT_RUN &&
            bootState_HwFatFs != TASK_BOOT_RUN &&
            bootState_HwSDCardDetect != TASK_BOOT_RUN &&
            bootState_HwRelay != TASK_BOOT_RUN &&
            bootState_HwVoltageSource != TASK_BOOT_RUN &&
            bootState_HwDAQ_ADC != TASK_BOOT_RUN &&
            bootState_HwDAQ_Frequency != TASK_BOOT_RUN &&
            bootState_HwStatusLED != TASK_BOOT_RUN &&
            bootState_HwSDCardLED != TASK_BOOT_RUN &&
            bootState_HwRunButton != TASK_BOOT_RUN )
    {
        // Check HwTerminal task
        if ( bootState_HwTerminal == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwTerminal task run\n" );
            bootState_HwTerminal = TASK_BOOT_RUN;
        }
        else if ( bootState_HwTerminal == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwTerminal task boot error\n" );
            break;
        }

        // Check HwSystemTime task
        if ( bootState_HwSystemTime == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwSystemTime task run\n" );
            bootState_HwSystemTime = TASK_BOOT_RUN;
        }
        else if ( bootState_HwSystemTime == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwSystemTime task boot error\n" );
            break;
        }

        // Check HwFatFs task
        if ( bootState_HwFatFs == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwFatFs task run\n" );
            bootState_HwFatFs = TASK_BOOT_RUN;
        }
        else if ( bootState_HwFatFs == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwFatFs task boot error\n" );
            break;
        }

        // Check HwSDCardDetect task
        if ( bootState_HwSDCardDetect == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task run\n" );
            bootState_HwSDCardDetect = TASK_BOOT_RUN;
        }
        else if ( bootState_HwSDCardDetect == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwSDCardDetect task boot error\n" );
            break;
        }

        // Check HwRelay task
        if ( bootState_HwRelay == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwRelay task run\n" );
            bootState_HwRelay = TASK_BOOT_RUN;
        }
        else if ( bootState_HwRelay == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwRelay task boot error\n" );
            break;
        }

        // Check HwVoltageSource task
        if ( bootState_HwVoltageSource == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwVoltageSource task run\n" );
            bootState_HwVoltageSource = TASK_BOOT_RUN;
        }
        else if ( bootState_HwVoltageSource == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwVoltageSource task boot error\n" );
            break;
        }

        // Check HwDAQ_ADC task
        if ( bootState_HwDAQ_ADC == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task run\n" );
            bootState_HwDAQ_ADC = TASK_BOOT_RUN;
        }
        else if ( bootState_HwDAQ_ADC == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_ADC task boot error\n" );
            break;
        }

        // Check HwDAQ_Frequency task
        if ( bootState_HwDAQ_Frequency == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task run\n" );
            bootState_HwDAQ_Frequency = TASK_BOOT_RUN;
        }
        else if ( bootState_HwDAQ_Frequency == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwDAQ_Frequency task boot error\n" );
            break;
        }

        // Check HwStatusLED task
        if ( bootState_HwStatusLED == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwStatusLED task run\n" );
            bootState_HwStatusLED = TASK_BOOT_RUN;
        }
        else if ( bootState_HwStatusLED == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwStatusLED task boot error\n" );
            break;
        }

        // Check HwSDCardLED task
        if ( bootState_HwSDCardLED == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwSDCardLED task run\n" );
            bootState_HwSDCardLED = TASK_BOOT_RUN;
        }
        else if ( bootState_HwSDCardLED == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwSDCardLED task boot error\n" );
            break;
        }

        // Check HwRunButton task
        if ( bootState_HwRunButton == TASK_BOOT_PENDING )
        {
            HwAPI_Terminal_SendMessage( "HwRunButton task run\n" );
            bootState_HwRunButton = TASK_BOOT_RUN;
        }
        else if ( bootState_HwRunButton == TASK_BOOT_ERROR )
        {
            HwAPI_Terminal_SendMessage( "HwRunButton task boot error\n" );
            break;
        }
    }
                                
    bootState_HwBoot = TASK_BOOT_RUN;

    while ( 1 )
    {


    }
}

/* End of file */
