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
    MEASURE_PLANNER_SD_CARD_INSERT,
    MEASURE_PLANNER_SD_CARD_REMOVE,
    MEASURE_PLANNER_RUN_BUTTON_PRESSED,
    MEASURE_PLANNER_IDLE
};

enum stateMeasurePlugin {
    MEASURE_PLUGIN_INIT,
    MEASURE_PLUGIN_RUN,
    MEASURE_PLUGIN_TACT,
    MEASURE_PLUGIN_STOP,
    MEASURE_PLUGIN_IDLE
};






// Task list
//void vTask_HwBoot( void *pvParameters );
void vTask_MeasurePlanner( void *pvParameters );
//void vTask_MeasureX( void *pvParameters );


#endif /* _TS_TASK_H_ */
/* End of file */
