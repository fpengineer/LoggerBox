/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _SOURCE_H_
#define _SOURCE_H_

#include <stdint.h>

#define DAC1_CS_1()       GPIO_SetBits(GPIOB, GPIO_Pin_9)
#define DAC1_CS_0()       GPIO_ResetBits(GPIOB, GPIO_Pin_9)

#define DAC2_CS_1()       GPIO_SetBits(GPIOE, GPIO_Pin_1)
#define DAC2_CS_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_1)

#define DAC3_CS_1()       GPIO_SetBits(GPIOE, GPIO_Pin_3)
#define DAC3_CS_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_3)

#define DAC4_CS_1()       GPIO_SetBits(GPIOE, GPIO_Pin_5)
#define DAC4_CS_0()       GPIO_ResetBits(GPIOE, GPIO_Pin_5)

#define AD5620_OPERATING_MODE_NORMAL                   0x0000
#define AD5620_OPERATING_MODE_POWER_DOWN_10K_TO_GND    0x4000
#define AD5620_OPERATING_MODE_POWER_DOWN_100K_TO_GND   0x8000
#define AD5620_OPERATING_MODE_POWER_DOWN_THREE_STATE   0xC000

#define AD5620_MAX_VALUE        4095

void InitSourceAll(void);
void SetSourceG1(float value);
void SetSourceG2(float value);
void SetSourceG3(float value);
void SetSourceG4(float value);

#endif /* _SOURCE_H_ */
/* End of file */
