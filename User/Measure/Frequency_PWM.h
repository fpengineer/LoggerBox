/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _FREQUENCY_PWM_H_
#define _FREQUENCY_PWM_H_

#include <stdint.h>

#define CALIBRATION_FREQUENCY_SLOPE       GPIO_SetBits(GPIOA, GPIO_Pin_13)


#define MUX_FREQUENCY_A_1()       GPIO_SetBits(GPIOA, GPIO_Pin_13)
#define MUX_FREQUENCY_A_0()       GPIO_ResetBits(GPIOA, GPIO_Pin_13)

#define MUX_FREQUENCY_B_1()       GPIO_SetBits(GPIOC, GPIO_Pin_9)
#define MUX_FREQUENCY_B_0()       GPIO_ResetBits(GPIOC, GPIO_Pin_9)

#define MUX_FREQUENCY_C_1()       GPIO_SetBits(GPIOC, GPIO_Pin_7)
#define MUX_FREQUENCY_C_0()       GPIO_ResetBits(GPIOC, GPIO_Pin_7)



enum frequencyInput {
    FREQUENCY_IC1,
    FREQUENCY_IC2,
    FREQUENCY_IC3,
    FREQUENCY_IC4,
    FREQUENCY_IC5,
    FREQUENCY_IC6,
    FREQUENCY_IC7,
    FREQUENCY_IC8
};

typedef struct FreqPWMData {
    float frequency_kHz;
    float pulseHigh_ns;
    float pulseLow_ns;
}FreqPWMData_t;


void InitFrequencyPWMMeter(void);
void FrequencySelectInput(enum frequencyInput);
void FrequencyGetSingleValue(FreqPWMData_t *freqPWMData);
void FrequencyGetAveragedValue(int32_t numberAverages, FreqPWMData_t *freqPWMData);


#endif /* _FREQUENCY_PWM_H_ */
/* End of file */
