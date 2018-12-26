/*****************************************************************************************************

    data types for hw queues
    extern declares for queue handles



*******************************************************************************************************/


#ifndef _TS_HW_QUEUE_H_
#define _TS_HW_QUEUE_H_

#include "TS_task.h"
#include "HwAPI.h"


/* Exported types ------------------------------------------------------------*/
typedef struct {
    enum stateHwSystemTime stateHwSystemTime ;
    TM_RTC_Time_t datatime;    
//    cfgSystemTime_t cfgSystemTime;
} HwSystemTimeQueueData_t;

typedef struct {
    enum stateHwFatFs stateHwFatFs;
    FatFsStatus_t fatFsStatus;
    SDCardStatus_t sdCardStatus;

    char *textBuffer;
    char *fileName;
    uint8_t fileIndex;
    INIInfoData_t iniInfoData;
} HwFatFsQueueData_t;

/*
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


extern QueueHandle_t xQueue_HwFatFs_Rx;
extern QueueHandle_t xQueue_HwFatFs_Tx;
extern QueueHandle_t xQueue_HwSystemTime_Rx;
extern QueueHandle_t xQueue_HwSystemTime_Tx;
extern QueueHandle_t xQueue_HwTerminal_Rx;
extern QueueHandle_t xQueue_HwRelay_Rx;
extern QueueHandle_t xQueue_HwSource_Rx;
extern QueueHandle_t xQueue_HwMeasureADC_Rx;
extern QueueHandle_t xQueue_HwMeasureADC_Tx;
extern QueueHandle_t xQueue_HwMeasureFrequency_Rx;
extern QueueHandle_t xQueue_HwMeasureFrequency_Tx;
extern QueueHandle_t xQueue_HwStatusLED_Rx;
extern QueueHandle_t xQueue_HwSDCardLED_Rx;
extern QueueHandle_t xQueue_HwRunButton_Rx;
extern QueueHandle_t xQueue_HwRunButton_Tx;

#endif /* _TS_HW_EXTERN_QUEUE_H_ */
/* End of file */
