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
#include "TS_HwTask.h"
#include "TS_queue.h"
#include "ClockOutMCO.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

TaskHandle_t xTask_HwBoot;
    
// Plugin task
TaskHandle_t xTask_MeasurePlanner;
TaskHandle_t xTask_MeasureX;

// Plugin queue
QueueHandle_t xQueue_MeasurePlanner_Rx;
QueueHandle_t xQueue_MeasureX_Rx;





/* User Global Variables */    

    
    
    
/*******************************************************************/
//void vApplicationIdleHook( void )
//{
//}
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
    extern BootState_t bootState_HwBoot;
	
    SystemInit();

	TM_DISCO_LedInit();
    TM_DELAY_Init();

//    OutputMCO();
    
    xQueue_MeasurePlanner_Rx = xQueueCreate( 5, sizeof( int ) );
//    xQueue_MeasureX_Rx = xQueueCreate( 5, sizeof( int ) );



#if 1       // Hardware boot task
    if( pdTRUE != xTaskCreate(  vTask_HwBoot,
                                "Task - Hardware boot",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwBoot )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
    vTaskStartScheduler();
                                
    while ( bootState_HwBoot != TASK_BOOT_RUN ){;}
#if 1       // MeasurePlanner
    if( pdTRUE != xTaskCreate(  vTask_MeasurePlanner,
                                "Task - Measure Planner",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_MeasurePlanner )) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
                                
    HwAPI_Terminal_SendMessage( "***********   LoggerBox   UF113.887   " SYSTEM_VERSION "   ***********\n" );


	while (1) {

	}
}
