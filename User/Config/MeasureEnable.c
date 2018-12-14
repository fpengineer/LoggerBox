/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Measure plan configuration functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "queue.h"

#include "defines.h"
#include "tm_stm32f4_rtc.h"

#include "Config.h"
#include "minIni.h"

static char tempString[350] = {""}; 

cfgMeasureEnable_t ConfigMeasureEnable_GetParameters(void)
{
    cfgMeasureEnable_t cfgMeasureEnable;
    

// Section [MeasureEnable]
    cfgMeasureEnable.enableG1_V = ini_getl("MeasureEnable", "enableG1_V", -1, "config.ini");
    cfgMeasureEnable.enableG2_V = ini_getl("MeasureEnable", "enableG2_V", -1, "config.ini");
    cfgMeasureEnable.enableG3_V = ini_getl("MeasureEnable", "enableG3_V", -1, "config.ini");
    cfgMeasureEnable.enableG4_V = ini_getl("MeasureEnable", "enableG4_V", -1, "config.ini");

    cfgMeasureEnable.enableG1_I = ini_getl("MeasureEnable", "enableG1_I", -1, "config.ini");
    cfgMeasureEnable.enableG2_I = ini_getl("MeasureEnable", "enableG2_I", -1, "config.ini");
    cfgMeasureEnable.enableG3_I = ini_getl("MeasureEnable", "enableG3_I", -1, "config.ini");
    cfgMeasureEnable.enableG4_I = ini_getl("MeasureEnable", "enableG4_I", -1, "config.ini");

    cfgMeasureEnable.enableIC1_Vout = ini_getl("MeasureEnable", "enableIC1_Vout", -1, "config.ini");
    cfgMeasureEnable.enableIC2_Vout = ini_getl("MeasureEnable", "enableIC2_Vout", -1, "config.ini");
    cfgMeasureEnable.enableIC3_Vout = ini_getl("MeasureEnable", "enableIC3_Vout", -1, "config.ini");
    cfgMeasureEnable.enableIC4_Vout = ini_getl("MeasureEnable", "enableIC4_Vout", -1, "config.ini");

    cfgMeasureEnable.enableIC1_Comp = ini_getl("MeasureEnable", "enableIC1_Comp", -1, "config.ini");
    cfgMeasureEnable.enableIC2_Comp = ini_getl("MeasureEnable", "enableIC2_Comp", -1, "config.ini");
    cfgMeasureEnable.enableIC3_Comp = ini_getl("MeasureEnable", "enableIC3_Comp", -1, "config.ini");
    cfgMeasureEnable.enableIC4_Comp = ini_getl("MeasureEnable", "enableIC4_Comp", -1, "config.ini");

    cfgMeasureEnable.enableIC1_Freq_PWM = ini_getl("MeasureEnable", "enableIC1_Freq_PWM", -1, "config.ini");
    cfgMeasureEnable.enableIC2_Freq_PWM = ini_getl("MeasureEnable", "enableIC2_Freq_PWM", -1, "config.ini");
    cfgMeasureEnable.enableIC3_Freq_PWM = ini_getl("MeasureEnable", "enableIC3_Freq_PWM", -1, "config.ini");
    cfgMeasureEnable.enableIC4_Freq_PWM = ini_getl("MeasureEnable", "enableIC4_Freq_PWM", -1, "config.ini");

    cfgMeasureEnable.enableIC1_Temperature = ini_getl("MeasureEnable", "enableIC1_Temperature", -1, "config.ini");
    cfgMeasureEnable.enableIC2_Temperature = ini_getl("MeasureEnable", "enableIC2_Temperature", -1, "config.ini");
    cfgMeasureEnable.enableIC3_Temperature = ini_getl("MeasureEnable", "enableIC3_Temperature", -1, "config.ini");
    cfgMeasureEnable.enableIC4_Temperature = ini_getl("MeasureEnable", "enableIC4_Temperature", -1, "config.ini");

    return cfgMeasureEnable;
}

void ConfigMeasureEnable_SendParametersToTerminal(cfgMeasureEnable_t cfgMeasureEnable)
{
    extern QueueHandle_t xQueue_HwTerminal_Rx;
        
// Section [MeasureEnable]
    sprintf(tempString, "\r\n[MeasureEnable]\r\n"
                        "enableG1_V = %d\r\n"
                        "enableG2_V = %d\r\n"
                        "enableG3_V = %d\r\n"
                        "enableG4_V = %d\r\n"
                        "enableG1_I = %d\r\n"
                        "enableG2_I = %d\r\n"
                        "enableG3_I = %d\r\n"
                        "enableG4_I = %d\r\n"
                        "enableIC1_Vout = %d\r\n"
                        "enableIC2_Vout = %d\r\n"
                        "enableIC3_Vout = %d\r\n"
                        "enableIC4_Vout = %d\r\n"
                        "enableIC1_Comp = %d\r\n"
                        "enableIC2_Comp = %d\r\n"
                        "enableIC3_Comp = %d\r\n"
                        "enableIC4_Comp = %d\r\n"
                        "enableIC1_Freq_PWM = %d\r\n"
                        "enableIC2_Freq_PWM = %d\r\n"
                        "enableIC3_Freq_PWM = %d\r\n"
                        "enableIC4_Freq_PWM = %d\r\n"
                        "enableIC1_Temperature = %d\r\n"
                        "enableIC2_Temperature = %d\r\n"
                        "enableIC3_Temperature = %d\r\n"
                        "enableIC4_Temperature = %d\r\n",
                        cfgMeasureEnable.enableG1_V,
                        cfgMeasureEnable.enableG2_V,
                        cfgMeasureEnable.enableG3_V,
                        cfgMeasureEnable.enableG4_V,
                        cfgMeasureEnable.enableG1_I,
                        cfgMeasureEnable.enableG2_I,
                        cfgMeasureEnable.enableG3_I,
                        cfgMeasureEnable.enableG4_I,
                        cfgMeasureEnable.enableIC1_Vout,
                        cfgMeasureEnable.enableIC2_Vout,
                        cfgMeasureEnable.enableIC3_Vout,
                        cfgMeasureEnable.enableIC4_Vout,
                        cfgMeasureEnable.enableIC1_Comp,
                        cfgMeasureEnable.enableIC2_Comp,
                        cfgMeasureEnable.enableIC3_Comp,
                        cfgMeasureEnable.enableIC4_Comp,
                        cfgMeasureEnable.enableIC1_Freq_PWM,
                        cfgMeasureEnable.enableIC2_Freq_PWM,
                        cfgMeasureEnable.enableIC3_Freq_PWM,
                        cfgMeasureEnable.enableIC4_Freq_PWM,
                        cfgMeasureEnable.enableIC1_Temperature,
                        cfgMeasureEnable.enableIC2_Temperature,
                        cfgMeasureEnable.enableIC3_Temperature,
                        cfgMeasureEnable.enableIC4_Temperature);

    xQueueSend( xQueue_HwTerminal_Rx, &tempString, NULL );
}



/* End of file */
