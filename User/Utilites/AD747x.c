/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: ADC AD747x functions

*******************************************************************************************************/
#include <stdint.h>
#include <math.h>

#include "AD747x.h"

//
float CalculateADC_AD747x( ValueAD747x_t value, float range )
{
#if defined( AD7476 )
    return ( float )value * ( range / powf( 2, AD7476_RESOLUTION_BITS ) );
    
#elif defined( AD7477 )
    return ( float )( value >> 2 ) * ( range / powf( 2, AD7477_RESOLUTION_BITS ) );

#elif defined( AD7478 )
    return ( float )( value >> 4 ) * ( range / powf( 2, AD7478_RESOLUTION_BITS ) );

#endif
}

/* End of file */
