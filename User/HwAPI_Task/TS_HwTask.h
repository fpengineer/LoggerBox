/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: RTOS Hardware task functions header

*******************************************************************************************************/


#ifndef _TS_HW_TASK_H_
#define _TS_HW_TASK_H_

#include <stdint.h>

#include "defines.h"
#include "HwAPI.h"
#include "HwAPI Config.h"


/* Exported variables ------------------------------------------------------------*/
typedef enum {
    TASK_BOOT_PENDING,
    TASK_BOOT_RUN,
    TASK_BOOT_IDLE,
    TASK_BOOT_ERROR
} BootState_t;



enum stateHwSystemTime {
    HW_SYSTEM_TIME_INIT,
    HW_SYSTEM_TIME_SET,
    HW_SYSTEM_TIME_GET,
    HW_SYSTEM_TIME_IDLE
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

enum stateHwSDCardDetect {
    HW_SDCARD_DETECT_INIT,
    HW_SDCARD_DETECT_GET,
    HW_SDCARD_DETECT_INSERT,
    HW_SDCARD_DETECT_REMOVE,
    HW_SDCARD_DETECT_IDLE
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

enum stateHwSDCardLED {
    HW_SDCARD_LED_INIT,
    HW_SDCARD_LED_ON,
    HW_SDCARD_LED_OFF,
    HW_SDCARD_LED_FLASH,
    HW_SDCARD_LED_IDLE
};

enum stateHwRunButton {
    HW_RUN_BUTTON_INIT,
    HW_RUN_BUTTON_GET,
    HW_RUN_BUTTON_PRESSED,
    HW_RUN_BUTTON_IDLE
};



/* Exported variables ------------------------------------------------------------*/
extern BootState_t bootState_HwSystemTime;
extern BootState_t bootState_HwTerminal;
extern BootState_t bootState_HwFatFs;
extern BootState_t bootState_HwSDCardDetect;
extern BootState_t bootState_HwRelay;
extern BootState_t bootState_HwVoltageSource;
extern BootState_t bootState_HwDAQ_ADC;
extern BootState_t bootState_HwDAQ_Frequency;
extern BootState_t bootState_HwStatusLED;
extern BootState_t bootState_HwSDCardLED;
extern BootState_t bootState_HwRunButton;



// Hardware task list
void vTask_HwSystemTime( void *pvParameters );
void vTask_HwTerminal( void *pvParameters );
void vTask_HwFatFs( void *pvParameters );
void vTask_HwSDCardDetect( void *pvParameters );
void vTask_HwRelay( void *pvParameters );
void vTask_HwVoltageSource( void *pvParameters );
void vTask_HwDAQ_ADC( void *pvParameters );
void vTask_HwDAQ_Frequency( void *pvParameters );
void vTask_HwStatusLED( void *pvParameters );
void vTask_HwSDCardLED( void *pvParameters );
void vTask_HwRunButton( void *pvParameters );

#endif /* _TS_HW_TASK_H_ */
/* End of file */
