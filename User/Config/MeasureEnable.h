/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _MEASURE_ENABLE_H_
#define _MEASURE_ENABLE_H_

#include <stdint.h>

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
    int32_t enableIC1_Comp;
    int32_t enableIC2_Comp;
    int32_t enableIC3_Comp;
    int32_t enableIC4_Comp;
    int32_t enableIC1_Freq_PWM;
    int32_t enableIC2_Freq_PWM;
    int32_t enableIC3_Freq_PWM;
    int32_t enableIC4_Freq_PWM;
    int32_t enableIC1_Temperature;
    int32_t enableIC2_Temperature;
    int32_t enableIC3_Temperature;
    int32_t enableIC4_Temperature;
} cfgMeasureEnable_t;


cfgMeasureEnable_t ConfigMeasureEnable_GetParameters(void);
void ConfigMeasureEnable_SendParametersToTerminal(cfgMeasureEnable_t cfgMeasureEnable);

#endif /* _MEASURE_PLAN_H_ */
/* End of file */
