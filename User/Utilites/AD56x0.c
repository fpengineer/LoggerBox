/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: DAC AD56x0 functions

*******************************************************************************************************/
#include <stdint.h>
#include <math.h>

#include "AD56x0.h"


//
ValueAD56x0_t CalculateDAC( float value, float range, OperationModeAD56X0_t mode )
{
    ValueAD56x0_t temp;

#if defined( AD5620 )
    temp = ( ValueAD56x0_t )roundf( ( value * powf( 2, AD5620_RESOLUTION_BITS ) ) / range );
    if ( temp > AD5620_MAX_VALUE )
    {
        temp = AD5620_MAX_VALUE;
    }
    temp <<= 2; // shift left due to 2 least insignificant bits 
    temp |= mode << 14; // add operation mode to value
    
#elif defined( ad5640 )
    temp = ( ValueAD56x0_t )roundf( ( value * powf( 2, AD5640_RESOLUTION_BITS ) ) / range );
    if ( temp > AD5640_MAX_VALUE )
    {
        temp = AD5640_MAX_VALUE;
    }
    temp |= mode << 14; // add operation mode to value

#elif defined( ad5660 )
    temp = ( ValueAD56x0_t )roundf( ( value * powf( 2, AD5660_RESOLUTION_BITS ) ) / range );
    if ( temp > AD5660_MAX_VALUE )
    {
        temp = AD5660_MAX_VALUE;
    }
    temp |= mode << 16; // add operation mode to value

#endif
    return temp;
}

/* End of file */
