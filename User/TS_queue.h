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
    enum stateHwSystemTime stateHwSystemTime ;
    TM_RTC_Time_t datatime;    
} HwSystemTimeQueueData_t;

/*
typedef struct {
    enum stateMeasureX stateMeasureX;
} MeasureXQueueData_t;


typedef struct {
    enum stateHwFatFs stateHwFatFs;
    char buffer[ 800 ];
    uint32_t flagConfigFileExist;
    uint32_t flagNewFileCreated;
    uint32_t flagFileWrite;
    char fileName[ 20 ];
} HwFatFsQueueData_t;


typedef struct {
    enum stateHwRelay stateHwRelay;
    uint8_t relay;
} HwRelayQueueData_t;

typedef struct {
    enum stateHwSource stateHwSource;
    float valueVoltage_G1;
    float valueVoltage_G2;
    float valueVoltage_G3;
    float valueVoltage_G4;
} HwSourceQueueData_t;

typedef struct {
    enum stateHwMeasureADC stateHwMeasureADC;
    uint8_t selectSource;
    uint8_t selectChannel;
    uint16_t valueADC;
} HwMwasureADCQueueData_t;

typedef struct {
    enum stateHwMeasureFrequency stateHwMeasureFrequency;
    uint8_t selectChannel;
    FreqPWMData_t freqPWMData;
} HwMeasurFrequencyQueueData_t;

typedef struct {
    enum stateHwStatusLED stateHwStatusLED;
} HwStatusLED_QueueData_t;

typedef struct {
    enum stateHwSDCardLED stateHwSDCardLED;
} HwSDCardDetectQueueData_t;

typedef struct {
    enum stateHwRunButton stateHwRunButton;
} HwRunButtonQueueData_t;

typedef struct {
    enum stateHwSDCArdDetect stateHwSDCardDetect;
} HwSDCardDetectQueueData_t;
*/

#endif /* _TS_QUEUE_H_ */
/* End of file */
