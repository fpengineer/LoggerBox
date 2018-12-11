/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _MEASURE_H_
#define _MEASURE_H_

#include <stdint.h>

#define CALIBR_SLOPE_Gn_V   1.0027f
#define CALIBR_OFFSET_Gn_V   0.01f

#define CALIBR_SLOPE_Gn_I   1.0f
#define CALIBR_OFFSET_Gn_I   0.0f

#define CALIBR_SLOPE_ICn_VOUT   1.0035f
#define CALIBR_OFFSET_ICn_VOUT   (-0.005f)

#define CALIBR_SLOPE_ICn_COMP   1.0f
#define CALIBR_OFFSET_ICn_COMP   0.0f


enum sawDirectionG1 {
    SAW_UP,
    SAW_DOWN
};

typedef struct {
    float G1_V;
    float G2_V;
    float G3_V;
    float G4_V;

    float G1_I;
    float G2_I;
    float G3_I;
    float G4_I;

    float IC1_Vout;
    float IC2_Vout;
    float IC3_Vout;
    float IC4_Vout;

    float IC1_Comp;
    float IC2_Comp;
    float IC3_Comp;
    float IC4_Comp;

    float IC1_Frequency;
    float IC2_Frequency;
    float IC3_Frequency;
    float IC4_Frequency;
    float IC1_PulseHigh;
    float IC2_PulseHigh;
    float IC3_PulseHigh;
    float IC4_PulseHigh;
    float IC1_PulseLow;
    float IC2_PulseLow;
    float IC3_PulseLow;
    float IC4_PulseLow;

    float IC1_Temperature;
    float IC2_Temperature;
    float IC3_Temperature;
    float IC4_Temperature;
} MeasureData_t;







#endif /* _MEASURE_H_ */
/* End of file */
