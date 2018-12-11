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
#include "Config.h"
#include "Measure.h"
#include "ClockOutMCO.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

TaskHandle_t xTask_SDCardLed;
TaskHandle_t xTask_StatusLed;
TaskHandle_t xTask_MainMeasure;
TaskHandle_t xTask_FatFs;
TaskHandle_t xTask_Terminal;
TaskHandle_t xTask_SystemTime;
TaskHandle_t xTask_RunButton;
TaskHandle_t xTask_SDCardDetect;

QueueHandle_t xQueue_SDCardLed;
QueueHandle_t xQueue_StatusLed;
QueueHandle_t xQueue_MainMeasure;
QueueHandle_t xQueue_FatFsIn;
QueueHandle_t xQueue_FatFsOut;
QueueHandle_t xQueue_Terminal;
QueueHandle_t xQueue_SystemTimeIn;
QueueHandle_t xQueue_SystemTimeOut;

/* User Global Variables */    
cfgMeasurePlan_t cfgMeasurePlan;
cfgMeasureEnable_t cfgMeasureEnable;
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
    
	xQueue_SDCardLed = xQueueCreate( 5, sizeof( enum stateSDCardLed ) ); 
	xQueue_StatusLed = xQueueCreate( 5, sizeof( enum stateStatusLed ) ); 
	xQueue_MainMeasure = xQueueCreate( 5, sizeof( MainMeasureQueueData_t ) ); 
	xQueue_FatFsIn = xQueueCreate( 10, sizeof( FatFsQueueData_t ) ); 
	xQueue_FatFsOut = xQueueCreate( 10, sizeof( FatFsQueueData_t ) ); 
	xQueue_Terminal = xQueueCreate( 15, sizeof( char[1800] ) ); 
	xQueue_SystemTimeIn = xQueueCreate( 5, sizeof( SystemTimeQueueData_t ) ); 
	xQueue_SystemTimeOut = xQueueCreate( 5, sizeof( SystemTimeQueueData_t ) ); 



	if( pdTRUE != xTaskCreate(  vTask_SDCardLed,
                                "SD Card Led",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_SDCardLed )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	

	if( pdTRUE != xTaskCreate(  vTask_StatusLed,
                                "Status Led",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_StatusLed )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	


    if( pdTRUE != xTaskCreate(  vTask_MainMeasure,
                                "Main Measure",
                                configMINIMAL_STACK_SIZE + 5000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_MainMeasure )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	


    if( pdTRUE != xTaskCreate(  vTask_FatFs,
                                "FatFs",
                                configMINIMAL_STACK_SIZE + 2000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_FatFs )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	


	if( pdTRUE != xTaskCreate(  vTask_Terminal,
                                "Terminal",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_Terminal )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	


    if( pdTRUE != xTaskCreate(  vTask_SystemTime,
                                "System Time",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_SystemTime )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	

    if( pdTRUE != xTaskCreate(  vTask_RunButton,
                                "Run Button",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_RunButton )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	

    if( pdTRUE != xTaskCreate(  vTask_SDCardDetect,
                                "SD Card Detect",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_SDCardDetect )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	


    xQueueSend( xQueue_Terminal, "*****************   Mockup 1290EF1  *********************\r\n", NULL );



	vTaskStartScheduler();

	while (1) {

	}
}
