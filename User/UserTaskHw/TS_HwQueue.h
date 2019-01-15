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
    FatFsEnable_t fatFsEnable;
//    SDCardStatus_t sdCardStatus;

    char *textBuffer;
    char *fileName;
    uint8_t fileIndex;
    INIInfoData_t iniInfoData;
} HwFatFsQueueData_t;

typedef struct {
    enum stateHwSDCardDetect stateHwSDCardDetect;
    SDCardDetectStatus_t sdCardDetectStatus;
} HwSDCardDetectQueueData_t;

typedef struct {
    enum stateHwVoltageSource stateHwVoltageSource;
    NSource_t nSource;
    ValueAD56x0_t valueDAC;
} HwVoltageSourceQueueData_t;

typedef struct {
    enum stateHwRelay stateHwRelay;
    NRelay_t nRelay;
} HwRelayQueueData_t;

typedef struct {
    enum stateHwDAQ_ADC stateHwDAQ_ADC;
    NChannelADC_t nChannelADC;
    NSourceADC_t nSourceADC;
    ValueDAQ_ADC_t valueADC;
    int32_t numberAverages;
} HwDAQ_ADCQueueData_t;

typedef struct {
    enum stateHwDAQ_Frequency stateHwDAQ_Frequency;
    uint8_t nChannelFrequency;
    FreqPWMData_t freqPWMData;
} HwDAQ_FrequencyQueueData_t;



/*
typedef struct {
    enum stateHwStatusLED stateHwStatusLED;
} HwStatusLED_QueueData_t;

typedef struct {
    enum stateHwSDCardLED stateHwSDCardLED;
} HwSDCardDetectQueueData_t;

typedef struct {
    enum stateHwRunButton stateHwRunButton;
} HwRunButtonQueueData_t;

*/


extern QueueHandle_t xQueue_HwFatFs_Rx;
extern QueueHandle_t xQueue_HwFatFs_Tx;
extern QueueHandle_t xQueue_HwSystemTime_Rx;
extern QueueHandle_t xQueue_HwSystemTime_Tx;
extern QueueHandle_t xQueue_HwTerminal_Rx;
extern QueueHandle_t xQueue_HwRelay_Rx;
extern QueueHandle_t xQueue_HwVoltageSource_Rx;
extern QueueHandle_t xQueue_HwDAQ_ADC_Rx;
extern QueueHandle_t xQueue_HwDAQ_ADC_Tx;
extern QueueHandle_t xQueue_HwMeasureFrequency_Rx;
extern QueueHandle_t xQueue_HwMeasureFrequency_Tx;
extern QueueHandle_t xQueue_HwStatusLED_Rx;
extern QueueHandle_t xQueue_HwSDCardLED_Rx;
extern QueueHandle_t xQueue_HwRunButton_Rx;
extern QueueHandle_t xQueue_HwRunButton_Tx;
extern QueueHandle_t xQueue_HwSDCardDetect_Rx;
extern QueueHandle_t xQueue_HwSDCardDetect_Tx;

#endif /* _TS_HW_EXTERN_QUEUE_H_ */
/* End of file */
