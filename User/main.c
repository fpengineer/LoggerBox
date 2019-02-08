/**
 *	LoggerBox project
 *
 *	
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

// Include application
#include "HwAPI.h"
#include "TS_Task.h"
#include "TS_queue.h"
#include "ClockOutMCO.h"

#define	ERROR_ACTION( CODE,POS )		do{}while( 0 )

   
// Plugin task
TaskHandle_t xTask_HwBoot;
extern TaskHandle_t xTask_MeasurePlanner;
//TaskHandle_t xTask_MeasureX;

// Plugin queue

int main(void) {
    SystemInit();

	TM_DISCO_LedInit();
    TM_DELAY_Init();

//    OutputMCO();
    
    TM_DISCO_LedOn( LED_RED );

#if 1  // Hardware boot
    if( pdTRUE != xTaskCreate(  vTask_HwBoot,
                                "Task - Hardware boot",
                                configMINIMAL_STACK_SIZE + 5000, // check if additional stack needed
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwBoot ) ) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
    
#if 1  // Measure planner
    if( pdTRUE != xTaskCreate(  vTask_MeasurePlanner,
                                "Task - Measure Planner",
                                configMINIMAL_STACK_SIZE + 5000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_MeasurePlanner ) ) { ERROR_ACTION(TASK_NOT_CREATE,0); }	
#endif
    
    vTaskStartScheduler();
                                
    while ( 1 ){;}
}











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
