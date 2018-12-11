/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/


#ifndef _MEASURE_STRING_H_
#define _MEASURE_STRING_H_

#include <stdint.h>
#include "Measure.h"
#include "Config.h"



void ClearString(char *string, int32_t size);
void CreateHeaderString(cfgMeasureEnable_t cfgMeasureEnable, char *headerString, char *delimiter);
void CreateMeasureString(MeasureData_t MeasureData, cfgMeasureEnable_t cfgMeasureEnable, char *measureString, char *delimiter);


#endif /* _MEASURE_STRING_H_ */
/* End of file */
