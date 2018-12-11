/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _VOLTMETER_H_
#define _VOLTMETER_H_

#include <stdint.h>

#define ADC1_CS_1()       GPIO_SetBits(GPIOE, GPIO_Pin_8)
#define ADC1_CS_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_8)

#define MUX_SOURCE_A_1()       GPIO_SetBits(GPIOE, GPIO_Pin_7)
#define MUX_SOURCE_A_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_7)

#define MUX_SOURCE_B_1()       GPIO_SetBits(GPIOE, GPIO_Pin_10)
#define MUX_SOURCE_B_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_10)

#define MUX_CHANNEL_A_1()       GPIO_SetBits(GPIOE, GPIO_Pin_9)
#define MUX_CHANNEL_A_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_9)

#define MUX_CHANNEL_B_1()       GPIO_SetBits(GPIOE, GPIO_Pin_12)
#define MUX_CHANNEL_B_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_12)


enum voltmeterInput {
    VOLTMETER_G1_V,
    VOLTMETER_G2_V,
    VOLTMETER_G3_V,
    VOLTMETER_G4_V,
    VOLTMETER_G1_I,
    VOLTMETER_G2_I,
    VOLTMETER_G3_I,
    VOLTMETER_G4_I,
    VOLTMETER_IC1_VOUT,
    VOLTMETER_IC2_VOUT,
    VOLTMETER_IC3_VOUT,
    VOLTMETER_IC4_VOUT,
    VOLTMETER_IC1_COMP,
    VOLTMETER_IC2_COMP,
    VOLTMETER_IC3_COMP,
    VOLTMETER_IC4_COMP
};


void InitVoltmeter(void);
void VoltmeterSelectInput(enum voltmeterInput);
float VoltmeterGetSingleValue(void);
float VoltmeterGetAveragedValue(int32_t numberAverages);


#endif /* _VOLTMETER_H_ */
/* End of file */
