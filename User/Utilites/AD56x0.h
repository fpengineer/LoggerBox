/*****************************************************************************************************

    
    
    
    Author: Filipp Popov

    Overview: 

*******************************************************************************************************/
#ifndef _AD56x0_H_
#define _AD56x0_H_

#include <stdint.h>

#if !defined( AD5620 ) && !defined( AD5640 ) && !defined( AD5660 ) 
  #define AD5620  /*!< AD5620: Single, 12-Bit nanoDAC with 5 ppm/°C On-Chip Reference in SOT-23 */
  /* #define AD5640 */  /*!< AD5640: Single, 14-Bit nanoDAC with 5 ppm/°C On-Chip Reference in SOT-23 */  
  /* #define AD5660 */  /*!< AD5660: Single, 16-Bit nanoDAC with 5 ppm/°C On-Chip Reference in SOT-23 */  
#endif

#if !defined( AD5620 ) && !defined( AD5640 ) && !defined( AD5660 )
 #error "Please select first the DAC AD56x0 in your application (in AD56x0.h file)"
#endif



#define AD5620_RESOLUTION_BITS    12
#define AD5640_RESOLUTION_BITS    14
#define AD5660_RESOLUTION_BITS    16

#define AD5620_MAX_VALUE        4095
#define AD5640_MAX_VALUE        16383
#define AD5660_MAX_VALUE        65535

/* Exported types ------------------------------------------------------------*/
typedef enum {
    AD56X0_OPERATION_MODE_NORMAL                    = 0x00,
    AD56X0_OPERATION_MODE_POWER_DOWN_10K_TO_GND     = 0x01,
    AD56X0_OPERATION_MODE_POWER_DOWN_100K_TO_GND    = 0x02,
    AD56X0_OPERATION_MODE_POWER_DOWN_THREE_STATE    = 0x03
} OperationModeAD56X0_t;

typedef uint32_t ValueAD56x0_t;

/* Exported functions --------------------------------------------------------*/
ValueAD56x0_t CalculateDAC( float value, float range, OperationModeAD56X0_t mode );

#endif /* _AD56x0_H_ */
/* End of file */
