/*****************************************************************************************************

    Plugin SilaI1 - V1_0 defines



*******************************************************************************************************/
#ifndef _PLUGIN_TYPES_H_
#define _PLUGIN_TYPES_H_

#include <stdint.h>

#include "HwAPI.h"

/* Exported types --------------------------------------------------------*/
typedef struct {
    int32_t BaseTactLength_s;
    int32_t TactQ;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} CfgMeasurePlan_t;
#define INIT_CFG_MEASURE_PLAN_STRUCT    { .BaseTactLength_s = 1,    \
                                          .TactQ = 50,              \
                                          .SourceG1_V = 0.0f,       \
                                          .SourceG2_V = 0.0f,       \
                                          .SourceG3_V = 0.0f,       \
                                          .SourceG4_V = 0.0f }

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
} CfgMeasureEnable_t;
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
                                          .enableIC4_Vout = 0 }
    

typedef struct {
    int32_t enableDatafile;
    char prefixDatafileName[ 25 ];
    uint32_t stringsToWrite;
    char delimiter[5];
} CfgDatafileSettings_t;
#define INIT_CFG_DATAFILE_SETTINGS_STRUCT { .enableDatafile = 0,                    \
                                            .prefixDatafileName = "test",           \
                                            .stringsToWrite = 0,                    \
                                            .delimiter = ";" }                          
 
typedef struct {
    float valueG1_V;
    float valueG2_V;
    float valueG3_V;
    float valueG4_V;
    float valueG1_I;
    float valueG2_I;
    float valueG3_I;
    float valueG4_I;
    float valueIC1_Vout;
    float valueIC2_Vout;
    float valueIC3_Vout;
    float valueIC4_Vout;
} MeasureValues_t;
#define INIT_MEASURE_VALUES_STRUCT  { .valueG1_V = 0.0f,                    \
                                      .valueG2_V = 0.0f,                    \
                                      .valueG3_V = 0.0f,                    \
                                      .valueG4_V = 0.0f,                    \
                                      .valueG1_I = 0.0f,                    \
                                      .valueG2_I = 0.0f,                    \
                                      .valueG3_I = 0.0f,                    \
                                      .valueG4_I = 0.0f,                    \
                                      .valueIC1_Vout = 0.0f,                \
                                      .valueIC2_Vout = 0.0f,                \
                                      .valueIC3_Vout = 0.0f,                \
                                      .valueIC4_Vout = 0.0f }

                                            

#endif /* _PLUGIN_TYPES_H_ */
/* End of file */
