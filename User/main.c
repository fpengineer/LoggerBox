/**
 *	Keil project for FatFS for SD cards
 *
 *	Before you start, select your target, on the right of the "Load" button
 *
 *	@author		Filipp Popov
 *	@email		filip@land.ru
 *	@website	
 *	@ide		Keil uVision 5
 *	@packs		STM32F4xx Keil packs version 2.2.0 or greater required
 *	@stdperiph	STM32F4xx Standard peripheral drivers version 1.4.0 or greater required
 */
#include <stdio.h>
#include <string.h>

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"

// Include FreeRTOS
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

// Include application
#include "TS_task.h"
#include "TS_queue.h"
#include "Measure.h"
#include "ClockOutMCO.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

    
// Plugin task
TaskHandle_t xTask_MeasurePlanner;
TaskHandle_t xTask_MeasureX;

// Plugin queue
QueueHandle_t xQueue_MeasurePlanner_Rx;
QueueHandle_t xQueue_MeasureX_Rx;


// Hw task
TaskHandle_t xTask_HwFatFs;
TaskHandle_t xTask_HwSystemTime;
TaskHandle_t xTask_HwTerminal;
TaskHandle_t xTask_HwRelay;
TaskHandle_t xTask_HwVoltageSource;
TaskHandle_t xTask_HwDAQ_ADC;
TaskHandle_t xTask_HwMeasureFrequency;
TaskHandle_t xTask_HwStatusLED;
TaskHandle_t xTask_HwSDCardLED;
TaskHandle_t xTask_HwRunButton;
TaskHandle_t xTask_HwSDCardDetect;

// Hw queues
QueueHandle_t xQueue_HwFatFs_Rx;
QueueHandle_t xQueue_HwFatFs_Tx;
QueueHandle_t xQueue_HwSystemTime_Rx;
QueueHandle_t xQueue_HwSystemTime_Tx;
QueueHandle_t xQueue_HwTerminal_Rx;
QueueHandle_t xQueue_HwRelay_Rx;
QueueHandle_t xQueue_HwVoltageSource_Rx;
QueueHandle_t xQueue_HwDAQ_ADC_Rx;
QueueHandle_t xQueue_HwDAQ_ADC_Tx;
QueueHandle_t xQueue_HwMeasureFrequency_Rx;
QueueHandle_t xQueue_HwMeasureFrequency_Tx;
QueueHandle_t xQueue_HwStatusLED_Rx;
QueueHandle_t xQueue_HwSDCardLED_Rx;
QueueHandle_t xQueue_HwRunButton_Rx;
QueueHandle_t xQueue_HwRunButton_Tx;
QueueHandle_t xQueue_HwSDCardDetect_Rx;
QueueHandle_t xQueue_HwSDCardDetect_Tx;



/* User Global Variables */    
//cfgMeasurePlan_t cfgMeasurePlan;
//cfgMeasureEnable_t cfgMeasureEnable;
uint32_t cardReady = 0;
uint32_t measureEnableFlag = 0;
volatile uint32_t runButtonFlag = 0;    //1 - button pressed, 0 - button not pressed
volatile uint32_t cardInsertState = 0;  //1 - card inserted, 0 - card not inserted

/*******************************************************************/
void vApplicationIdleHook( void )
{
}
/*******************************************************************/
void vApplicationMallocFailedHook( void )
{
    for( ;; );
}
/*******************************************************************/
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName )
{
    ( void ) pcTaskName;
    ( void ) pxTask;
 
    for( ;; );
}
/*******************************************************************/
void vApplicationTickHook( void )
{
}
/*******************************************************************/    

int main(void) {

	SystemInit();

	TM_DISCO_LedInit();
    TM_DELAY_Init();

//    OutputMCO();
    
    xQueue_MeasurePlanner_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_MeasureX_Rx = xQueueCreate( 5, sizeof( int ) );

//    xQueue_HwFatFs_Rx = xQueueCreate( 10, sizeof( int ) );
//    xQueue_HwFatFs_Tx = xQueueCreate( 10, sizeof( int ) );
//    xQueue_HwSystemTime_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwSystemTime_Tx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwTerminal_Rx = xQueueCreate( 15, sizeof( char[ TERMINAL_BUFFER ] ) );
//    xQueue_HwRelay_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwSource_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwMeasureADC_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwMeasureADC_Tx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwMeasureFrequency_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwMeasureFrequency_Tx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwStatusLED_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwSDCardLED_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwRunButton_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_HwRunButton_Tx = xQueueCreate( 5, sizeof( int ) );


#if 1       // MeasurePlanner
    if( pdTRUE != xTaskCreate(  vTask_MeasurePlanner,
                                "Task - Measure Planner",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_MeasurePlanner )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
                                
// Hw tasks
#if 0       // HwFatFs
	if( pdTRUE != xTaskCreate(  vTask_HwFatFs,
                                "Task - HwFatFs",
                                configMINIMAL_STACK_SIZE + 2000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwFatFs )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwSystemTime
	if( pdTRUE != xTaskCreate(  vTask_HwSystemTime,
                                "Task - HwSystemTime",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSystemTime )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwTerminal
	if( pdTRUE != xTaskCreate(  vTask_HwTerminal,
                                "Task - HwTerminal",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwTerminal )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwRelay
	if( pdTRUE != xTaskCreate(  vTask_HwRelay,
                                "Task - HwRelay",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwRelay )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwSource
	if( pdTRUE != xTaskCreate(  vTask_HwVoltageSource,
                                "Task - HwVoltageSource",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwVoltageSource )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwMeasureADC
	if( pdTRUE != xTaskCreate(  vTask_HwDAQ_ADC,
                                "Task - HwDAQ_ADC",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwDAQ_ADC )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwMeasureFrequency
	if( pdTRUE != xTaskCreate(  vTask_HwMeasureFrequency,
                                "Task - HwMeasureFrequency",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwMeasureFrequency )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwStatusLED
	if( pdTRUE != xTaskCreate(  vTask_HwStatusLED,
                                "Task - HwStatusLED",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwStatusLED )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwSDCardLED
	if( pdTRUE != xTaskCreate(  vTask_HwSDCardLED,
                                "Task - HwSDCardLED",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSDCardLED )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwRunButton
    if( pdTRUE != xTaskCreate(  vTask_HwRunButton,
                                "Task - HwRunButton",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwRunButton )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
#if 0       // HwSDCardDetect
	if( pdTRUE != xTaskCreate(  vTask_HwSDCardDetect,
                                "Task - HwSDCardDetect",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwSDCardDetect )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif

    xQueueSend( xQueue_HwTerminal_Rx, "***********   LoggerBox   UF113.887   " SYSTEM_VERSION "   ***********\n", NULL );



	vTaskStartScheduler();

	while (1) {

	}
}
