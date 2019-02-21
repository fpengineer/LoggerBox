/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: Measure planner defines

*******************************************************************************************************/
#ifndef _MEASURE_PLANNER_DEF_H_
#define _MEASURE_PLANNER_DEF_H_

#include <stdint.h>
#include "PluginsDef.h"


// define HWAPI_DEBUG_INFO to allow debug info messages into terminal
//#define HWAPI_BOOT_DEBUG_INFO


/* Extern variables ----------------------------------------------------------*/
extern QueueHandle_t xQueue_MeasurePlanner_Rx;
extern QueueHandle_t xQueue_MeasurePlanner_Tx;
extern QueueHandle_t xQueue_MeasureX_Rx;
extern QueueHandle_t xQueue_MeasureX_Tx;


/* Exported types ------------------------------------------------------------*/
enum stateMeasurePlanner {
    MEASURE_PLANNER_INIT,
    MEASURE_PLANNER_SD_CARD_INSERT,
    MEASURE_PLANNER_SD_CARD_REMOVE,
    MEASURE_PLANNER_RUN_BUTTON_PRESSED,
    MEASURE_PLANNER_PLUGIN_ERROR,
    MEASURE_PLANNER_IDLE
};

enum stateMeasureX {
    MEASURE_X_INIT,
    MEASURE_X_RUN,
    MEASURE_X_TACT,
    MEASURE_X_STOP,
    MEASURE_X_ERROR,
    MEASURE_X_IDLE
};

typedef struct {
    enum stateMeasurePlanner stateMeasurePlanner;
} MeasurePlannerQueueData_t;

typedef struct {
    enum stateMeasureX stateMeasureX;
    void (*pluginRef)( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms ); 
} MeasureXQueueData_t;




/* Exported functions --------------------------------------------------------*/
void vTask_MeasurePlanner( void *pvParameters );
void vTask_MeasureX( void *pvParameters );

#endif /* _MEASURE_PLANNER_DEF_H_ */
/* End of file */
