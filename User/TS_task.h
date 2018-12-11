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
    MEASURE_PLANNER_IDLE
};

enum stateMeasureX {
    MEASURE_X_STOP,
    MEASURE_X_IDLE
};

enum stateHwFatFs { 
    HW_FATFS_INIT_SD_CARD,
    HW_FATFS_DEINIT_SD_CARD,
    HW_FATFS_CREATE_NEW_MEASUREMENT_FILE,
    HW_FATFS_WRITE_DATA_TO_MEASUREMENT_FILE,
    HW_FATFS_GET_CONFIG,
    HW_FATFS_CHECK_CONFIG_FILE_EXIST,
    HW_FATFS_IDLE 
};

enum stateHwSystemTime {
    HW_SYSTEM_TIME_SET,
    HW_SYSTEM_TIME_GET,
    HW_SYSTEM_TIME_IDLE
};

enum stateHwRelay {
    HW_RELAY_SET,
    HW_RELAY_CLEAR,
    HW_RELAY_CLEAR_ALL,
    HW_RELAY_IDLE
};

enum stateHwSource {
    HW_SOURCE_SET,
    HW_SOURCE_CLEAR,
    HW_SOURCE_CLEAR_ALL,
    HW_SOURCE_IDLE
};

enum stateHwMeasureADC {
    HW_MEASURE_ADC_GET,
    HW_MEASURE_ADC_IDLE
};

enum stateHwMeasureFrequency {
    HW_MEASURE_FREQUENCY_GET,
    HW_MEASURE_FREQUENCY_IDLE
};

enum stateStatusLed {
    HW_STATUS_LED_ON,
    HW_STATUS_LED_OFF,
    HW_STATUS_LED_FLASH,
    HW_STATUS_LED_IDLE
};

enum stateSDCardLed {
    HW_SDCARD_LED_ON,
    HW_SDCARD_LED_OFF,
    HW_SDCARD_LED_FLASH,
    HW_SDCARD_LWD_IDLE
};

enum stateRunButton {
    HW_RUN_BUTTON_GET,
    HW_RUN_BUTTON_IDLE
};

enum stateSDCardDetect {
    HW_SDCARD_DETECT_GET,
    HW_SDCARD_DETECT_IDLE
};




// Task list
vTask_MeasurePlanner( void *pvParameters );
vTask_MeasureX( void *pvParameters );

vTask_HwFatFs( void *pvParameters );
vTask_HwSystemTime( void *pvParameters );
vTask_HwTerminal( void *pvParameters );
vTask_HwRelay( void *pvParameters );
vTask_HwSource( void *pvParameters );
vTask_HwMeasureADC( void *pvParameters );
vTask_HwMeasureFrequency( void *pvParameters );
vTask_HwStatusLED( void *pvParameters );
vTask_HwSDCardLED( void *pvParameters );
vTask_HwRunButton( void *pvParameters );
vTask_HwSDCardDetect( void *pvParameters );

#endif /* _TS_TASK_H_ */
/* End of file */
