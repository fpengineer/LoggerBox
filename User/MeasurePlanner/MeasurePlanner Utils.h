/*****************************************************************************************************

    Measure Planner utilites



*******************************************************************************************************/
#ifndef _MEASURE_PLANNER_UTILS_H_
#define _MEASURE_PLANNER_UTILS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

//#include "HwAPI.h"

// define MEASURE_PLANNER_DEBUG_INFO to enable debug info messages into terminal
//#define MEASURE_PLANNER_DEBUG_INFO

/* Exported types ------------------------------------------------------------*/
typedef enum {
    MEASURE_STOP,
    MEASURE_RUN
} MeasureStatus_t;

typedef struct {
    char nameIC[ 50 ];
    char systemTimeString[ 50 ];
    int32_t updateSystemTime;
} ConfigData_t;


/* Exported functions --------------------------------------------------------*/
int32_t ReadConfigFile( ConfigData_t *configData, char *fileName );
void ProcessSystemTimeConfig( char *systemTimeString, int32_t updateSystemTime );
int32_t FindMeasurePlugin( char *nameIC );
int32_t CheckMeasurePlanFile( char *nameIC );
void LoadMeasurePlugin( int32_t pluginIndex );
void UnloadMeasurePlugin( void );
void SendPluginsList( void );
void SetSystemDefault( void );
void RunMeasurePlugin( void );
void StopMeasurePlugin( void );

void MeasurePluginError( void );

#endif /* _MEASURE_PLANNER_H_*/
/* End of file */
