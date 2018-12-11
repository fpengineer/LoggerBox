/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _MEASURE_PLAN_H_
#define _MEASURE_PLAN_H_

#include <stdint.h>

typedef struct {
    int32_t Tact1_Length_s;
    int32_t Tact2_Length_s;
    int32_t Tact3_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_t;

typedef struct {
    int32_t Tact1_Length_s;
    int32_t Tact2_Length_s;
    int32_t Tact3_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_1290EF1_t;

typedef struct {
    int32_t Tact_Length_s;
    int32_t SubTact2_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_SilaI1_t;

typedef struct {
    int32_t Tact_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_IC2_t;

typedef struct {
    int32_t Tact_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_IC3_t;

typedef struct {
    int32_t Tact_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_IC4_t;

typedef struct {
    int32_t Tact_Length_s;
    float SourceG1_V;
    float SourceG2_V;
    float SourceG3_V;
    float SourceG4_V;
} cfgMeasurePlan_IC5_t;


cfgMeasurePlan_t ConfigMeasurePlan_GetParameters(void);
void ConfigMeasurePlan_SendParametersToTerminal(cfgMeasurePlan_t);

#endif /* _MEASURE_PLAN_H_ */
/* End of file */
