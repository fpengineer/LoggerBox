/*****************************************************************************************************

    Plugin ConverterI7 - IC5 - V1_0 defines



*******************************************************************************************************/
#ifndef _CONVERTER_I7_IC5_V1_0_H_
#define _CONVERTER_I7_IC5_V1_0_H_

#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"
#include "PluginsDef.h"
#include "PluginsString.h"
#include "PluginsDelay.h"


#ifndef PLUGIN_4

#define PLUGIN_4
#define PLUGIN_4_NAME       "ConverterI7_IC5_V1_0"
#define PLUGIN_4_POINTER    ConverterI7_IC5_V1_0

#else 
#error "PLUGIN_4 already defined! Please select another plugin number and nam definitions."
#endif

/* Exported types --------------------------------------------------------*/
typedef struct {
    int32_t BaseTactLength_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} CfgMeasurePlan_ConverterI7_IC5_V1_0_t;

typedef struct {
    int32_t enableG1_V;
    int32_t enableG2_V;
    int32_t enableG3_V;
    int32_t enableG4_V;
    int32_t enableG1_I;
    int32_t enableG2_I;
    int32_t enableG3_I;
    int32_t enableG4_I;
    int32_t enableIC1_Vout;
    int32_t enableIC2_Vout;
    int32_t enableIC3_Vout;
    int32_t enableIC4_Vout;
    int32_t enableIC1_Freq_PWM;
    int32_t enableIC2_Freq_PWM;
    int32_t enableIC3_Freq_PWM;
    int32_t enableIC4_Freq_PWM;
    int32_t enableIC1_Temperature;
    int32_t enableIC2_Temperature;
    int32_t enableIC3_Temperature;
    int32_t enableIC4_Temperature;
} CfgMeasureEnable_ConverterI7_IC5_V1_0_t;

typedef struct {
    int32_t enableDatafile;
    char prefixDatafileName[ 25 ];
    uint32_t stringsToWrite;
    char delimiter[5];
} CfgDatafileSettings_ConverterI7_IC5_V1_0_t;

#define INIT_CFG_MEASURE_PLAN_STRUCT    { .BaseTactLength_s = 1,    \
                                          .SourceG1_V = 0.0f,       \
                                          .SourceG2_V = 0.0f,       \
                                          .SourceG3_V = 0.0f,       \
                                          .SourceG4_V = 0.0f }

#define INIT_CFG_MEASURE_ENABLE_STRUCT  { .enableG1_V = 0,             \
                                          .enableG2_V = 0,             \
                                          .enableG3_V = 0,             \
                                          .enableG4_V = 0,             \
                                          .enableG1_I = 0,             \
                                          .enableG2_I = 0,             \
                                          .enableG3_I = 0,             \
                                          .enableG4_I = 0,             \
                                          .enableIC1_Vout = 0,         \
                                          .enableIC2_Vout = 0,         \
                                          .enableIC3_Vout = 0,         \
                                          .enableIC4_Vout = 0,         \
                                          .enableIC1_Freq_PWM = 0,     \
                                          .enableIC2_Freq_PWM = 0,     \
                                          .enableIC3_Freq_PWM = 0,     \
                                          .enableIC4_Freq_PWM = 0,     \
                                          .enableIC1_Temperature = 0,  \
                                          .enableIC2_Temperature = 0,  \
                                          .enableIC3_Temperature = 0,  \
                                          .enableIC4_Temperature = 0 }
    

#define INIT_CFG_DATAFILE_SETTINGS_STRUCT { .enableDatafile = 0,                    \
                                            .prefixDatafileName = "test",           \
                                            .stringsToWrite = 0,                    \
                                            .delimiter = ";" }                          
 

/* Exported functions --------------------------------------------------------*/
void ConverterI7_IC5_V1_0( PluginResult_t *pluginResult, PluginCommand_t pluginCommand, int32_t *tactLength_ms );

#endif /* _CONVERTER_I7_IC5_V1_0_H_ */
/* End of file */
