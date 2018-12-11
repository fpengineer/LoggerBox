/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Run button functions

*******************************************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_disco.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_exti.h"

//#include "RunButton.h"


/* Create 2 callback functions for custom timers */
void CustomTIMER1_Task(void* UserParameters);
void CustomTIMER2_Task(void* UserParameters);

/* Pointers to custom timers */
TM_DELAY_Timer_t* CustomTimer1;
TM_DELAY_Timer_t* CustomTimer2;

void InitRunButton(void)
{
    extern volatile uint32_t cardInsertState;
	/* Timer1 has reload value each 500ms, enabled auto reload feature and timer is enabled */
	CustomTimer1 = TM_DELAY_TimerCreate(70, 0, 0, CustomTIMER1_Task, NULL);
	CustomTimer2 = TM_DELAY_TimerCreate(70, 0, 0, CustomTIMER2_Task, NULL);
    
    TM_EXTI_Attach(GPIOC, GPIO_Pin_3, TM_EXTI_Trigger_Falling);
    TM_EXTI_Attach(GPIOA, GPIO_Pin_0, TM_EXTI_Trigger_Rising_Falling);

    if (!TM_GPIO_GetInputPinValue(GPIOA, GPIO_Pin_0))
    {
        cardInsertState = 1;    
        TM_DISCO_LedOn(LED_GREEN);
    }
}



void TM_EXTI_Handler(uint16_t GPIO_Pin) {
    /* Handle Run Button interrupt */
    if (GPIO_Pin == GPIO_Pin_3)
    {
        TM_DELAY_TimerStart(CustomTimer1);
    }
    
    /* Handle SD card detect interrupt */
    if (GPIO_Pin == GPIO_Pin_0)
    {
        TM_DELAY_TimerStart(CustomTimer2);
    }
}

/* Called when Custom TIMER1 reaches zero */
void CustomTIMER1_Task(void* UserParameters)
{
    extern volatile uint32_t runButtonFlag;

    if (!TM_GPIO_GetInputPinValue(GPIOC, GPIO_Pin_3))
    {
        if (runButtonFlag == 0)
        {
            /* Enable/Disable measuring */
            runButtonFlag = 1;
            TM_DISCO_LedToggle(LED_RED);
        }
    }
}

/* Called when Custom TIMER2 reaches zero */
void CustomTIMER2_Task(void* UserParameters)
{
    extern volatile uint32_t cardInsertState;
    
    if (!TM_GPIO_GetInputPinValue(GPIOA, GPIO_Pin_0))
    {
        cardInsertState = 1;
        TM_DISCO_LedOn(LED_GREEN);
    }
    else
    {
        cardInsertState = 0;
        TM_DISCO_LedOff(LED_GREEN);
    }
}

/* End of file */
