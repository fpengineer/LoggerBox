/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: RTOS queue header

*******************************************************************************************************/


#ifndef _TS_QUEUE_H_
#define _TS_QUEUE_H_

#include <stdint.h>
#include "Config.h"
#include "Measure.h"
#include "Config.h"

#include "TS_task.h"

typedef struct {
    enum stateSystemTime stateSystemTime ;
    TM_RTC_Time_t datatime;    
} SystemTimeQueueData_t;

typedef struct {
    enum stateFatFs stateFatFs;
    MeasureData_t measureData;    
    cfgMeasurePlan_t cfgMeasurePlan;
    cfgMeasureEnable_t cfgMeasureEnable;
    uint32_t configFileExistFlag;
    uint32_t newFileCreatedFlag;
    uint32_t fileWriteFlag;
    char stringName[20];
} FatFsQueueData_t;

typedef struct {
    enum stateMainMeasure stateMainMeasure;
} MainMeasureQueueData_t;

#endif /* _TS_QUEUE_H_ */
/* End of file */
