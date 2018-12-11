/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - Main Measure

*******************************************************************************************************/
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

#include "tm_stm32f4_disco.h"

#include "TS_queue.h"
#include "TS_task.h"

#include "Config.h"
#include "Measure.h"
#include "Source.h"
#include "Voltmeter.h"
#include "Relay.h"
#include "Frequency_PWM.h"

#define FATFS_QUEUE_TIMEOUT_MS    (2000 / portTICK_PERIOD_MS)

enum measureState {RUN_MODE, STOP_MODE};
enum measureTactState { RELAY_EN_ON,
                        RELAY_EN_OFF,
                        RELAY_FB_ON,
                        RELAY_FB_OFF,
                        RELAY_BS_ON,
                        RELAY_BS_OFF };

//static char tempString[250] = {""}; 

void vTask_MainMeasure( void *pvParameters )
{
    extern QueueHandle_t xQueue_StatusLed;
    extern QueueHandle_t xQueue_Terminal;
    extern QueueHandle_t xQueue_MainMeasure;;
    extern QueueHandle_t xQueue_FatFsIn;
    extern QueueHandle_t xQueue_FatFsOut;

    MainMeasureQueueData_t mainMeasureQueueData;
    FatFsQueueData_t FatFsQueueData;
    cfgMeasurePlan_t cfgMeasurePlan;
    cfgMeasureEnable_t cfgMeasureEnable;

    extern uint32_t measureEnableFlag;
    enum measureState measureState = STOP_MODE;
    enum measureTactState measureTactState = RELAY_EN_ON;
    extern uint32_t cardReady;
    volatile MeasureData_t measureData;
    enum stateStatusLed stateStatusLed = STATUS_LED_OFF;
    FreqPWMData_t freqPWMData = {0.0f, 0.0f, 0.0f};

    TickType_t xLastWakeTime;
    TickType_t tactLength = 0;    
    
    InitRelayAll();
    InitVoltmeter();
    InitSourceAll();
    VoltmeterGetSingleValue();
    InitFrequencyPWMMeter();
    SetSourceG1(0.0f);
    SetSourceG2(0.0f);
    SetSourceG3(0.0f);
    SetSourceG4(0.0f);

    xLastWakeTime = xTaskGetTickCount();
    measureEnableFlag = 0;
    mainMeasureQueueData.stateMainMeasure = MEASURE_IDLE;
    vTaskDelay(2000);   // Wait for SD card initializing
    stateStatusLed = STATUS_LED_ON;
    xQueueSend( xQueue_StatusLed, &stateStatusLed, NULL ); // Add timeout to check

/*
    while (1)
    {
        RelaySet (RELAY_K1);
        RelaySet (RELAY_K2);
        RelaySet (RELAY_K3);
        RelaySet (RELAY_K4);
        RelaySet (RELAY_K5);
        RelaySet (RELAY_K6);
        RelaySet (RELAY_K7);
        vTaskDelay(2000);
        RelayClear (RELAY_K1);
        RelayClear (RELAY_K2);
        RelayClear (RELAY_K3);
        RelayClear (RELAY_K4);
        RelayClear (RELAY_K5);
        RelayClear (RELAY_K6);
        RelayClear (RELAY_K7);
        vTaskDelay(2000);
    }
*/


//xQueueSend( xQueue_Terminal, "__MEAS - Start\r\n", NULL );
    while( 1 )
	{
        xQueueReceive( xQueue_MainMeasure, &mainMeasureQueueData, portMAX_DELAY );
//                        sprintf(tempString, "__MEAS - Receive command %d\r\n", (uint32_t)mainMeasureQueueData.stateMainMeasure);
//                        xQueueSend( xQueue_Terminal, &tempString, NULL );
//    vTaskDelay(200);   // Wait for SD card initializing

        switch (mainMeasureQueueData.stateMainMeasure)
        {
            case MEASURE_RUN:
                xQueueSend( xQueue_Terminal, "System start measuring\r\n", NULL );
                if (cardReady == 1)
                {
                    /* check config file */
//                    xQueueSend( xQueue_Terminal, "__MEAS - check config file\r\n", NULL );
                    FatFsQueueData.stateFatFs = FATFS_CHECK_CONFIG_FILE_EXIST;            
                    xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL ); // Add timeout to check
                    if (xQueueReceive( xQueue_FatFsOut, &FatFsQueueData, FATFS_QUEUE_TIMEOUT_MS ))
                    {                        
                        if (!FatFsQueueData.configFileExistFlag)
                        {
                            /* file config.ini did not found! */
                            break;
                        }
                    }
                    else
                    {
                        /* FatFs queue timeout! */
                        mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                        xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                        xQueueSend( xQueue_Terminal, "__MEAS - FatFs queue timeout! - FATFS_CHECK_CONFIG_FILE_EXIST\r\n", NULL );
                        break;
                    }
                    
                    /* get config parameters */
//                    xQueueSend( xQueue_Terminal, "__MEAS - get config parameters\n", NULL );
                    FatFsQueueData.stateFatFs = FATFS_GET_CONFIG;            
                    xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL ); 
                    if (xQueueReceive( xQueue_FatFsOut, &FatFsQueueData, FATFS_QUEUE_TIMEOUT_MS ))
                    {
                        cfgMeasurePlan = FatFsQueueData.cfgMeasurePlan;
                        cfgMeasureEnable = FatFsQueueData.cfgMeasureEnable;
                    }
                    else
                    {
                        /* FatFs queue timeout! */
                        mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                        xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                        xQueueSend( xQueue_Terminal, "__MEAS - FatFs queue timeout! - FATFS_GET_CONFIG\r\n", NULL );
                        break;
                    }

                    /* create new measurement file */
//                    xQueueSend( xQueue_Terminal, "__MEAS - create new file\n", NULL );

                    FatFsQueueData.stateFatFs = FATFS_CREATE_NEW_MEASUREMENT_FILE;            
                    xQueueReset( xQueue_FatFsOut ); 
                    xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL ); 
                    if (xQueueReceive( xQueue_FatFsOut, &FatFsQueueData, FATFS_QUEUE_TIMEOUT_MS )) 
                    {
                        if (!FatFsQueueData.newFileCreatedFlag)
                        {
                            mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                            xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                            xQueueSend( xQueue_Terminal, "__MEAS - new file not created\r\n", NULL );
                            break;
                        }
                        else
                        {
//                            xQueueSend( xQueue_Terminal, "__MEAS - new file created\n", NULL );
                        }
                    }
                    else
                    {
                        mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                        xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                        xQueueSend( xQueue_Terminal, "__MEAS - FatFs queue timeout! - FATFS_CREATE_NEW_MEASUREMENT_FILE\r\n", NULL );
                        break;
                    }

                    /* prepare measurement */
                    /* Send value to DAC of source Gn */
                    SetSourceG1(cfgMeasurePlan.SourceG1_V);
                    SetSourceG2(cfgMeasurePlan.SourceG2_V);
                    SetSourceG3(cfgMeasurePlan.SourceG3_V);
                    SetSourceG4(cfgMeasurePlan.SourceG4_V);

                    stateStatusLed = STATUS_LED_FLASH;
                    xQueueSend( xQueue_StatusLed, &stateStatusLed, NULL );

                    measureEnableFlag = 1;
                    measureState = RUN_MODE;
                    measureTactState = RELAY_FB_ON;
                    sprintf(FatFsQueueData.stringName, "Relays Off \n");                    
                    mainMeasureQueueData.stateMainMeasure = MEASURE_TACT;
                    xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );

                    tactLength = cfgMeasurePlan.Tact1_Length_s * (1000 / portTICK_PERIOD_MS);
                    xLastWakeTime = xTaskGetTickCount();
                    vTaskDelayUntil(&xLastWakeTime, tactLength);
                }
                else
                {
                    measureState = RUN_MODE;
                    mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                    xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                    xQueueSend( xQueue_Terminal, "__MEAS SD card not inserted! Please insert SD card and try again.\r\n", NULL );
                }
                break;
                
            case MEASURE_STOP:
                switch((int32_t)measureState)
                {
                    case RUN_MODE:
                        measureEnableFlag = 0;
                        measureState = STOP_MODE;
                        /* stop measure */
                        SetSourceG1(0.0f);
                        SetSourceG2(0.0f);
                        SetSourceG3(0.0f);
                        SetSourceG4(0.0f);
                        stateStatusLed = STATUS_LED_ON;
                        xQueueSend( xQueue_StatusLed, &stateStatusLed, NULL );
                        xQueueSend( xQueue_Terminal, "System stop measuring\r\n", NULL );
                        xQueueReset(xQueue_MainMeasure);
                        break;
                    
                    case STOP_MODE:
                        measureEnableFlag = 0;
                        break;
                    
                    default:
                        break;
                }
                break;
                
            case MEASURE_TACT:
                SetSourceG1(cfgMeasurePlan.SourceG1_V);
                SetSourceG2(cfgMeasurePlan.SourceG2_V);
                SetSourceG3(cfgMeasurePlan.SourceG3_V);
                SetSourceG4(cfgMeasurePlan.SourceG4_V);

                measureData.G1_V = 0.0;
                measureData.G2_V = 0.0;
                measureData.G3_V = 0.0;
                measureData.G4_V = 0.0;

                measureData.G1_I = 0.0;
                measureData.G2_I = 0.0;
                measureData.G3_I = 0.0;
                measureData.G4_I = 0.0;

                measureData.IC1_Vout = 0.0;
                measureData.IC2_Vout = 0.0;
                measureData.IC3_Vout = 0.0;
                measureData.IC4_Vout = 0.0;

                measureData.IC1_Frequency = 0.0;
                measureData.IC1_PulseHigh = 0.0;
                measureData.IC1_PulseLow = 0.0;
                measureData.IC2_Frequency = 0.0;
                measureData.IC2_PulseHigh = 0.0;
                measureData.IC2_PulseLow = 0.0;
                measureData.IC3_Frequency = 0.0;
                measureData.IC3_PulseHigh = 0.0;
                measureData.IC3_PulseLow = 0.0;
                measureData.IC4_Frequency = 0.0;
                measureData.IC4_PulseHigh = 0.0;
                measureData.IC4_PulseLow = 0.0;

                measureData.IC1_Temperature = 0.0;
                measureData.IC2_Temperature = 0.0;
                measureData.IC3_Temperature = 0.0;
                measureData.IC4_Temperature = 0.0;

/*
                switch (measureTactState)
                {
                    case RELAY_EN_ON:
                        tactLength = cfgMeasurePlan.Tact1_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay EN On\n");
                        RelaySet (RELAY_K3);
                        measureTactState = RELAY_EN_OFF;
                        break;
                    
                    case RELAY_EN_OFF:
                        tactLength = cfgMeasurePlan.Tact1_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay EN Off\n");
                        RelayClear (RELAY_K3);
                        measureTactState = RELAY_FB_ON;
                        break;
                    
                    case RELAY_FB_ON:
                        tactLength = cfgMeasurePlan.Tact2_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay FB On\n");
                        RelaySet (RELAY_K4);
                        measureTactState = RELAY_FB_OFF;
                        break;
                    
                    case RELAY_FB_OFF:
                        tactLength = cfgMeasurePlan.Tact2_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay FB Off\n");
                        RelayClear (RELAY_K4);
                        measureTactState = RELAY_BS_ON;
                        break;
                    
                    case RELAY_BS_ON:
                        tactLength = cfgMeasurePlan.Tact3_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay BS On\n");
                        RelaySet (RELAY_K5);
                        measureTactState = RELAY_BS_OFF;
                        break;
                    
                    case RELAY_BS_OFF:
                        tactLength = cfgMeasurePlan.Tact3_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay BS Off\n");
                        RelayClear (RELAY_K5);
                        measureTactState = RELAY_EN_ON;
                        break;
                    
                    default:
                        break;
                }
*/                
                switch (measureTactState)
                {
/*
                    case RELAY_EN_ON:
                        tactLength = cfgMeasurePlan.Tact1_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay EN On\n");
                        RelaySet (RELAY_K3);
                        measureTactState = RELAY_EN_OFF;
                        break;
                    
                    case RELAY_EN_OFF:
                        tactLength = cfgMeasurePlan.Tact1_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay EN Off\n");
                        RelayClear (RELAY_K3);
                        measureTactState = RELAY_EN_ON;
                        break;
*/
/*                    
                    case RELAY_FB_ON:
                        tactLength = cfgMeasurePlan.Tact2_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay FB On\n");
                        RelaySet (RELAY_K4);
                        measureTactState = RELAY_FB_OFF;
                        break;
                    
                    case RELAY_FB_OFF:
                        tactLength = cfgMeasurePlan.Tact2_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay FB Off\n");
                        RelayClear (RELAY_K4);
                        measureTactState = RELAY_FB_ON;
                        break;
*/
/*
                    case RELAY_BS_ON:
                        tactLength = cfgMeasurePlan.Tact3_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay BS On\n");
                        RelaySet (RELAY_K5);
                        measureTactState = RELAY_BS_OFF;
                        break;
                    
                    case RELAY_BS_OFF:
                        tactLength = cfgMeasurePlan.Tact3_Length_s * (1000 / portTICK_PERIOD_MS);
                        sprintf(FatFsQueueData.stringName, "Relay BS Off\n");
                        RelayClear (RELAY_K5);
                        measureTactState = RELAY_BS_ON;
                        break;
*/                    
                    default:
                        break;
                }

                vTaskDelay(100);
                
                if (cfgMeasureEnable.enableG1_V)
                {
                    /* Select input Source G1 Vin */
                    VoltmeterSelectInput(VOLTMETER_G1_V);
                    vTaskDelay(5);
                    /* Do measure Source G1 Vin */
                    measureData.G1_V = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_Gn_V) + CALIBR_OFFSET_Gn_V;
                }

                if (cfgMeasureEnable.enableG2_V)
                {
                    /* Select input Source G2 Vin */
                    VoltmeterSelectInput(VOLTMETER_G2_V);
                    vTaskDelay(5);
                    /* Do measure Source G2 Vin */
                    measureData.G2_V = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_Gn_V) + CALIBR_OFFSET_Gn_V;
                }

                if (cfgMeasureEnable.enableG3_V)
                {
                    /* Select input Source G3 Vin */
                    VoltmeterSelectInput(VOLTMETER_G3_V);
                    vTaskDelay(5);
                    /* Do measure Source G3 Vin */
                    measureData.G3_V = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_Gn_V) + CALIBR_OFFSET_Gn_V;
                }

                if (cfgMeasureEnable.enableG4_V)
                {
                    /* Select input Source G4 Vin */
                    VoltmeterSelectInput(VOLTMETER_G4_V);
                    vTaskDelay(5);
                    /* Do measure Source G4 Vin */
                    measureData.G4_V = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_Gn_V) + CALIBR_OFFSET_Gn_V;
                }

                if (cfgMeasureEnable.enableG1_I)
                {
                    /* Select input Source G1 Iin */
                    VoltmeterSelectInput(VOLTMETER_G1_I);
                    vTaskDelay(5);
                    /* Do measure Source G1 Iin */
                    measureData.G1_I = ((VoltmeterGetSingleValue() / 5.0f) * CALIBR_SLOPE_Gn_I) + CALIBR_OFFSET_Gn_I;
                }

                if (cfgMeasureEnable.enableG2_I)
                {
                    /* Select input Source G2 Iin */
                    VoltmeterSelectInput(VOLTMETER_G2_I);
                    vTaskDelay(5);
                    /* Do measure Source G2 Iin */
                    measureData.G2_I = ((VoltmeterGetSingleValue() / 5.0f) * CALIBR_SLOPE_Gn_I) + CALIBR_OFFSET_Gn_I;
                }

                if (cfgMeasureEnable.enableG3_I)
                {
                    /* Select input Source G3 Iin */
                    VoltmeterSelectInput(VOLTMETER_G3_I);
                    vTaskDelay(5);
                    /* Do measure Source G3 Iin */
                    measureData.G3_I = ((VoltmeterGetSingleValue() / 5.0f) * CALIBR_SLOPE_Gn_I) + CALIBR_OFFSET_Gn_I;
                }

                if (cfgMeasureEnable.enableG4_I)
                {
                    /* Select input Source G4 Iin */
                    VoltmeterSelectInput(VOLTMETER_G4_I);
                    vTaskDelay(5);
                    /* Do measure Source G4 Iin */
                    measureData.G4_I = ((VoltmeterGetSingleValue() / 5.0f) * CALIBR_SLOPE_Gn_I) + CALIBR_OFFSET_Gn_I;
                }

                if (cfgMeasureEnable.enableIC1_Vout)
                {
                    /* Select input IC1 Vout */
                    VoltmeterSelectInput(VOLTMETER_IC1_VOUT);
                    vTaskDelay(5);
                    /* Do measure IC1 Vout */
                    measureData.IC1_Vout = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_ICn_VOUT) + CALIBR_OFFSET_ICn_VOUT;
                }

                if (cfgMeasureEnable.enableIC2_Vout)
                {
                    /* Select input IC2 Vout */
                    VoltmeterSelectInput(VOLTMETER_IC2_VOUT);
                    vTaskDelay(5);
                    /* Do measure IC2 Vout */
                    measureData.IC2_Vout = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_ICn_VOUT) + CALIBR_OFFSET_ICn_VOUT;
                }

                if (cfgMeasureEnable.enableIC3_Vout)
                {
                    /* Select input IC3 Vout */
                    VoltmeterSelectInput(VOLTMETER_IC3_VOUT);
                    vTaskDelay(5);
                    /* Do measure IC3 Vout */
                    measureData.IC3_Vout = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_ICn_VOUT) + CALIBR_OFFSET_ICn_VOUT;
                }

                if (cfgMeasureEnable.enableIC4_Vout)
                {
                    /* Select input IC4 Vout */
                    VoltmeterSelectInput(VOLTMETER_IC4_VOUT);
                    vTaskDelay(5);
                    /* Do measure IC4 Vout */
                    measureData.IC4_Vout = ((VoltmeterGetAveragedValue(1024) * 3.0f) * CALIBR_SLOPE_ICn_VOUT) + CALIBR_OFFSET_ICn_VOUT;
                }

                if (cfgMeasureEnable.enableIC1_Comp)
                {
                    /* Select input IC1 Comp */
                    VoltmeterSelectInput(VOLTMETER_IC1_COMP);
                    vTaskDelay(5);
                    /* Do measure IC1 Comp */
                    measureData.IC1_Comp = ((VoltmeterGetAveragedValue(1024) / 2.0f) * CALIBR_SLOPE_ICn_COMP) + CALIBR_OFFSET_ICn_COMP;
                }

                if (cfgMeasureEnable.enableIC2_Comp)
                {
                    /* Select input IC2 Comp */
                    VoltmeterSelectInput(VOLTMETER_IC2_COMP);
                    vTaskDelay(5);
                    /* Do measure IC2 Comp */
                    measureData.IC2_Comp = ((VoltmeterGetAveragedValue(1024) / 2.0f) * CALIBR_SLOPE_ICn_COMP) + CALIBR_OFFSET_ICn_COMP;
                }

                if (cfgMeasureEnable.enableIC3_Comp)
                {
                    /* Select input IC3 Comp */
                    VoltmeterSelectInput(VOLTMETER_IC3_COMP);
                    vTaskDelay(5);
                    /* Do measure IC3 Comp */
                    measureData.IC3_Comp = ((VoltmeterGetAveragedValue(1024) / 2.0f) * CALIBR_SLOPE_ICn_COMP) + CALIBR_OFFSET_ICn_COMP;
                }

                if (cfgMeasureEnable.enableIC4_Comp)
                {
                    /* Select input IC4 Comp */
                    VoltmeterSelectInput(VOLTMETER_IC4_COMP);
                    vTaskDelay(5);
                    /* Do measure IC4 Comp */
                    measureData.IC4_Comp = ((VoltmeterGetAveragedValue(1024) / 2.0f) * CALIBR_SLOPE_ICn_COMP) + CALIBR_OFFSET_ICn_COMP;
                }

                if (cfgMeasureEnable.enableIC1_Freq_PWM)
                {
                    /* Select input IC1 Frequency PWM */
                    FrequencySelectInput(FREQUENCY_IC1);
                    vTaskDelay(5);
                    /* Do measure IC1 Frequency PWM */
                    FrequencyGetSingleValue(&freqPWMData);
                    measureData.IC1_Frequency = freqPWMData.frequency_kHz;
                    measureData.IC1_PulseHigh = freqPWMData.pulseHigh_ns;
                    measureData.IC1_PulseLow = freqPWMData.pulseLow_ns;
//                    measureData.IC1_Frequency = freqPWMData.frequency_kHz;
//                    measureData.IC1_PulseHigh = freqPWMData.pulseHigh_ns;
//                    measureData.IC1_PulseLow = freqPWMData.pulseLow_ns;
                }

                if (cfgMeasureEnable.enableIC2_Freq_PWM)
                {
                    /* Select input IC2 Frequency PWM */
                    FrequencySelectInput(FREQUENCY_IC2);
                    vTaskDelay(5);
                    /* Do measure IC2 Frequency PWM */
                    FrequencyGetSingleValue(&freqPWMData);
                    measureData.IC2_Frequency = freqPWMData.frequency_kHz;
                    measureData.IC2_PulseHigh = freqPWMData.pulseHigh_ns;
                    measureData.IC2_PulseLow = freqPWMData.pulseLow_ns;
//                    measureData.IC2_Frequency = 0;
//                    measureData.IC2_PulseHigh = 0;
//                    measureData.IC2_PulseLow = 0;
                }

                if (cfgMeasureEnable.enableIC3_Freq_PWM)
                {
                    /* Select input IC3 Frequency PWM */
                    FrequencySelectInput(FREQUENCY_IC3);
                    vTaskDelay(5);
                    /* Do measure IC3 Frequency PWM */
                    FrequencyGetSingleValue(&freqPWMData);
                    measureData.IC3_Frequency = freqPWMData.frequency_kHz;
                    measureData.IC3_PulseHigh = freqPWMData.pulseHigh_ns;
                    measureData.IC3_PulseLow = freqPWMData.pulseLow_ns;
//                    measureData.IC3_Frequency = 0;
//                    measureData.IC3_PulseHigh = 0;
//                    measureData.IC3_PulseLow = 0;
                }

                if (cfgMeasureEnable.enableIC4_Freq_PWM)
                {
                    /* Select input IC4 Frequency PWM */
                    FrequencySelectInput(FREQUENCY_IC4);
                    vTaskDelay(5);
                    /* Do measure IC4 Frequency PWM */
                    FrequencyGetSingleValue(&freqPWMData);
                    measureData.IC4_Frequency = freqPWMData.frequency_kHz;
                    measureData.IC4_PulseHigh = freqPWMData.pulseHigh_ns;
                    measureData.IC4_PulseLow = freqPWMData.pulseLow_ns;

//                    measureData.IC4_Frequency = 0;
//                    measureData.IC4_PulseHigh = 0;
//                    measureData.IC4_PulseLow = 0;
                }

                if (cfgMeasureEnable.enableIC1_Temperature)
                {
                    /* Select input IC1 Temperature */
//                  SelectTemperatureInput(TEMPERATURE_IC1);
                    vTaskDelay(5);
                    /* Do measure IC1 Temperature */
                    measureData.IC1_Temperature = 0;
                }

                if (cfgMeasureEnable.enableIC2_Temperature)
                {
                    /* Select input IC2 Temperature */
//                  SelectTemperatureInput(TEMPERATURE_IC2);
                    vTaskDelay(5);
                    /* Do measure IC2 Temperature */
                    measureData.IC2_Temperature = 0;
                }

                if (cfgMeasureEnable.enableIC3_Temperature)
                {
                    /* Select input IC3 Temperature */
//                  SelectTemperatureInput(TEMPERATURE_IC3);
                    vTaskDelay(5);
                    /* Do measure IC3 Temperature */
                    measureData.IC3_Temperature = 0;
                }

                if (cfgMeasureEnable.enableIC4_Temperature)
                {
                    /* Select input IC4 Temperature */
//                  SelectTemperatureInput(TEMPERATURE_IC4);
                    vTaskDelay(5);
                    /* Do measure IC4 Temperature */
                    measureData.IC4_Temperature = 0;
                }


                FatFsQueueData.stateFatFs = FATFS_WRITE_DATA_TO_MEASUREMENT_FILE;
                FatFsQueueData.measureData = measureData;
                xQueueReset( xQueue_FatFsOut ); 
                xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL ); 
                if (xQueueReceive( xQueue_FatFsOut, &FatFsQueueData, FATFS_QUEUE_TIMEOUT_MS )) // Add timeout to check
                {
                    if (!FatFsQueueData.fileWriteFlag)
                    {
                        mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                        xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                        xQueueSend( xQueue_Terminal, "__MEAS - error write data to file!\r\n", NULL );
                        break;
                    }
                }
                else
                {
                    mainMeasureQueueData.stateMainMeasure = MEASURE_STOP;
                    xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );
                    xQueueSend( xQueue_Terminal, "__MEAS - FatFs queue timeout! - FATFS_WRITE_DATA_TO_MEASUREMENT_FILE\r\n", NULL );
                    break;
                }

                mainMeasureQueueData.stateMainMeasure = MEASURE_TACT;
                xQueueSend( xQueue_MainMeasure, &mainMeasureQueueData, NULL );

                vTaskDelayUntil(&xLastWakeTime, tactLength);
                break;
                
                
            case MEASURE_IDLE: // Reserved for future
                measureState = STOP_MODE;
                break;
                
            default:
                break;
                
        }
    }
}
/* End of file */
