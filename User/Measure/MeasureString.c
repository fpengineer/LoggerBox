/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Voltmeter functions

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Measure.h"
#include "Config.h"


void ClearString(char *string, int32_t size)
{
    int32_t i = 0;

    for (i = 0; i < size; i++)
    {
        *(string + i) = '\0';
    }
}


void CreateHeaderString(cfgMeasureEnable_t cfgMeasureEnable, char *headerString, char *delimiter)
{
//    headerString should be cleared before executing this function!
    if (cfgMeasureEnable.enableG1_V)
    {
        sprintf(headerString + strlen(headerString), "G1_V, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableG2_V)
    {
        sprintf(headerString + strlen(headerString), "G2_V, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableG3_V)
    {
        sprintf(headerString + strlen(headerString), "G3_V, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableG4_V)
    {
        sprintf(headerString + strlen(headerString), "G4_V, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableG1_I)
    {
        sprintf(headerString + strlen(headerString), "G1_I, mA%s", delimiter);
    }

    if (cfgMeasureEnable.enableG2_I)
    {
        sprintf(headerString + strlen(headerString), "G2_I, mA%s", delimiter);
    }

    if (cfgMeasureEnable.enableG3_I)
    {
        sprintf(headerString + strlen(headerString), "G3_I, mA%s", delimiter);
    }

    if (cfgMeasureEnable.enableG4_I)
    {
        sprintf(headerString + strlen(headerString), "G4_I, mA%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Vout)
    {
        sprintf(headerString + strlen(headerString), "IC1_Vout, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Vout)
    {
        sprintf(headerString + strlen(headerString), "IC2_Vout, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Vout)
    {
        sprintf(headerString + strlen(headerString), "IC3_Vout, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Vout)
    {
        sprintf(headerString + strlen(headerString), "IC4_Vout, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Comp)
    {
        sprintf(headerString + strlen(headerString), "IC1_Comp, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Comp)
    {
        sprintf(headerString + strlen(headerString), "IC2_Comp, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Comp)
    {
        sprintf(headerString + strlen(headerString), "IC3_Comp, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Comp)
    {
        sprintf(headerString + strlen(headerString), "IC4_Comp, V%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Freq_PWM)
    {
        sprintf(headerString + strlen(headerString), "IC1_Freq, kHz%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC1_PWM_High, ns%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC1_PWM_Low, ns%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Freq_PWM)
    {
        sprintf(headerString + strlen(headerString), "IC2_Freq, kHz%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC2_PWM_High, ns%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC2_PWM_Low, ns%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Freq_PWM)
    {
        sprintf(headerString + strlen(headerString), "IC3_Freq, kHz%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC3_PWM_High, ns%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC3_PWM_Low, ns%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Freq_PWM)
    {
        sprintf(headerString + strlen(headerString), "IC4_Freq, kHz%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC4_PWM_High, ns%s", delimiter);
        sprintf(headerString + strlen(headerString), "IC4_PWM_Low, ns%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Temperature)
    {
        sprintf(headerString + strlen(headerString), "IC1_Temp, C%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Temperature)
    {
        sprintf(headerString + strlen(headerString), "IC2_Temp, C%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Temperature)
    {
        sprintf(headerString + strlen(headerString), "IC3_Temp, C%s", delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Temperature)
    {
        sprintf(headerString + strlen(headerString), "IC4_Temp, C%s", delimiter);
    }

    sprintf(headerString + strlen(headerString), "Date/Time\n");
}


void CreateMeasureString(MeasureData_t MeasureData, cfgMeasureEnable_t cfgMeasureEnable, char *measureString, char *delimiter)
{
//    measureString should be cleared before executing this function!
    if (cfgMeasureEnable.enableG1_V)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G1_V, delimiter);
    }

    if (cfgMeasureEnable.enableG2_V)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G2_V, delimiter);
    }

    if (cfgMeasureEnable.enableG3_V)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G3_V, delimiter);
    }

    if (cfgMeasureEnable.enableG4_V)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G4_V, delimiter);
    }

    if (cfgMeasureEnable.enableG1_I)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G1_I, delimiter);
    }

    if (cfgMeasureEnable.enableG2_I)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G2_I, delimiter);
    }

    if (cfgMeasureEnable.enableG3_I)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G3_I, delimiter);
    }

    if (cfgMeasureEnable.enableG4_I)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.G4_I, delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Vout)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC1_Vout, delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Vout)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC2_Vout, delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Vout)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC3_Vout, delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Vout)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC4_Vout, delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Comp)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC1_Comp, delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Comp)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC2_Comp, delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Comp)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC3_Comp, delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Comp)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC4_Comp, delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Freq_PWM)
    {
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC1_Frequency, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC1_PulseHigh, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC1_PulseLow, delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Freq_PWM)
    {
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC2_Frequency, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC2_PulseHigh, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC2_PulseLow, delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Freq_PWM)
    {
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC3_Frequency, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC3_PulseHigh, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC3_PulseLow, delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Freq_PWM)
    {
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC4_Frequency, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC4_PulseHigh, delimiter);
        sprintf(measureString + strlen(measureString), "%.1f%s", MeasureData.IC4_PulseLow, delimiter);
    }

    if (cfgMeasureEnable.enableIC1_Temperature)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC1_Temperature, delimiter);
    }

    if (cfgMeasureEnable.enableIC2_Temperature)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC2_Temperature, delimiter);
    }

    if (cfgMeasureEnable.enableIC3_Temperature)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC3_Temperature, delimiter);
    }

    if (cfgMeasureEnable.enableIC4_Temperature)
    {
        sprintf(measureString + strlen(measureString), "%.3f%s", MeasureData.IC4_Temperature, delimiter);
    }
}





/* End of file */
