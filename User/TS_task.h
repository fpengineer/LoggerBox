/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: RTOS Task functions header

*******************************************************************************************************/


#ifndef _TS_TASK_H_
#define _TS_TASK_H_

#include <stdint.h>

#include "defines.h"
#include "HwAPI.h"
#include "HwAPI Config.h"

enum stateMeasurePlanner {
    MEASURE_PLANNER_INIT,
    MEASURE_PLANNER_GET_TYPE,
    MEASURE_PLANNER_RUN_MEASURE_TASK,
    MEASURE_PLANNER_STOP_MEASURE_TASK,
    MEASURE_PLANNER_IDLE
};

enum stateMeasureX {
    MEASURE_X_INIT,
    MEASURE_X_RUN,
    MEASURE_X_TACT,
    MEASURE_X_STOP,
    MEASURE_X_IDLE
};

enum stateHwFatFs { 
    HW_FATFS_INIT,
    HW_FATFS_GET_STATUS,
    HW_FATFS_INIT_SD_CARD,
    HW_FATFS_DEINIT_SD_CARD,
    HW_FATFS_CREATE_FILE,
    HW_FATFS_CHECK_FILE_EXIST,
    HW_FATFS_OPEN_FILE,
    HW_FATFS_CLOSE_FILE,
    HW_FATFS_WRITE_FILE,
    HW_FATFS_GET_KEY_INI,
    HW_FATFS_PUT_KEY_INI,
    HW_FATFS_IDLE 
};

enum stateHwSystemTime {
    HW_SYSTEM_TIME_INIT,
    HW_SYSTEM_TIME_SET,
    HW_SYSTEM_TIME_GET,
    HW_SYSTEM_TIME_IDLE
};

enum stateHwRelay {
    HW_RELAY_INIT,
    HW_RELAY_SET,
    HW_RELAY_CLEAR,
    HW_RELAY_CLEAR_ALL,
    HW_RELAY_IDLE
};

enum stateHwVoltageSource {
    HW_VOLTAGE_SOURCE_INIT,
    HW_VOLTAGE_SOURCE_SET,
    HW_VOLTAGE_SOURCE_CLEAR,
    HW_VOLTAGE_SOURCE_CLEAR_ALL,
    HW_VOLTAGE_SOURCE_IDLE
};

enum stateHwDAQ_ADC {
    HW_DAQ_ADC_INIT,
    HW_DAQ_ADC_SELECT_INPUT,
    HW_DAQ_ADC_GET_SINGLE,
    HW_DAQ_ADC_GET_AVERAGED,
    HW_DAQ_ADC_IDLE
};

enum stateHwDAQ_Frequency {
    HW_DAQ_FREQUENCY_INIT,
    HW_DAQ_FREQUENCY_GET_SINGLE,
    HW_DAQ_FREQUENCY_GET_AVERAGED,
    HW_DAQ_FREQUENCY_IDLE
};

enum stateHwStatusLED {
    HW_STATUS_LED_INIT,
    HW_STATUS_LED_ON,
    HW_STATUS_LED_OFF,
    HW_STATUS_LED_FLASH,
    HW_STATUS_LED_IDLE
};

enum stateHwSDCardLed {
    HW_SDCARD_LED_ON,
    HW_SDCARD_LED_OFF,
    HW_SDCARD_LED_FLASH,
    HW_SDCARD_LWD_IDLE
};

enum stateHwRunButton {
    HW_RUN_BUTTON_GET,
    HW_RUN_BUTTON_IDLE
};

enum stateHwSDCardDetect {
    HW_SDCARD_DETECT_INIT,
    HW_SDCARD_DETECT_GET,
    HW_SDCARD_DETECT_INSERT,
    HW_SDCARD_DETECT_REMOVE,
    HW_SDCARD_DETECT_IDLE
};




// Task list
void vTask_MeasurePlanner( void *pvParameters );
//void vTask_MeasureX( void *pvParameters );

void vTask_HwFatFs( void *pvParameters );
void vTask_HwSystemTime( void *pvParameters );
void vTask_HwTerminal( void *pvParameters );
void vTask_HwRelay( void *pvParameters );
void vTask_HwSource( void *pvParameters );
void vTask_HwDAQ_ADC( void *pvParameters );
void vTask_HwDAQ_Frequency( void *pvParameters );
//void vTask_HwStatusLED( void *pvParameters );
//void vTask_HwSDCardLED( void *pvParameters );
//void vTask_HwRunButton( void *pvParameters );
//void vTask_HwSDCardDetect( void *pvParameters );

#endif /* _TS_TASK_H_ */
/* End of file */
