/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: RTOS queue header

*******************************************************************************************************/
#ifndef _TS_QUEUE_H_
#define _TS_QUEUE_H_

#include <stdint.h>

#include "TS_task.h"


typedef struct {
    enum stateMeasurePlanner stateMeasurePlanner;
} MeasurePlannerQueueData_t;


typedef struct {
    enum stateMeasurePlugin stateMeasurePlugin;
} MeasurePluginQueueData_t;





extern QueueHandle_t xQueue_MeasurePlugin_Rx;
extern QueueHandle_t xQueue_MeasurePlugin_Tx;


#endif /* _TS_QUEUE_H_ */
/* End of file */
