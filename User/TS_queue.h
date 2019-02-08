/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: RTOS queue header

*******************************************************************************************************/


#ifndef _TS_QUEUE_H_
#define _TS_QUEUE_H_

#include <stdint.h>

#include "TS_task.h"

#include "defines.h"
#include "HwAPI.h"
#include "HwAPI Config.h"


typedef struct {
    enum stateMeasurePlanner stateMeasurePlanner;
} MeasurePlannerQueueData_t;




typedef struct {
    enum stateMeasurePlugin stateMeasurePlugin;
} MeasurePluginQueueData_t;



#endif /* _TS_QUEUE_H_ */
/* End of file */
