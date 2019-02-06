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






// Task list
void vTask_HwBoot( void *pvParameters );
void vTask_MeasurePlanner( void *pvParameters );
//void vTask_MeasureX( void *pvParameters );


#endif /* _TS_TASK_H_ */
/* End of file */
