/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/
#ifndef _AD747X_H_
#define _AD747X_H_

#include <stdint.h>

#if !defined( AD7476 ) && !defined( AD7477 ) && !defined( AD7478 ) 
  #define AD7476  /*!< AD7476: Single, 1 MSPS, 12-Bit ADC */
  /* #define AD7477 */  /*!< AD7477: Single, 1 MSPS, 10-Bit ADC */  
  /* #define AD7478 */  /*!< AD7478: Single, 1 MSPS, 8-Bit ADC */  
#endif

#if !defined( AD7476 ) && !defined( AD7477 ) && !defined( AD7478 )
 #error "Please select first the ADC AD747x in your application (in AD747x.h file)"
#endif

#define AD7476_RESOLUTION_BITS    12
#define AD7477_RESOLUTION_BITS    10
#define AD7478_RESOLUTION_BITS    8

#define AD7476_MAX_VALUE        4095
#define AD7477_MAX_VALUE        1024
#define AD7478_MAX_VALUE        255

/* Exported types ------------------------------------------------------------*/
typedef uint32_t ValueAD747x_t;

/* Exported functions --------------------------------------------------------*/
float CalculateADC_AD747x( ValueAD747x_t value, float range );

#endif /* _AD747X_H_ */
/* End of file */
