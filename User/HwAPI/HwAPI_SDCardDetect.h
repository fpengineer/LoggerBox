/*****************************************************************************************************

    HwAPI SD card detect



*******************************************************************************************************/


#ifndef _HWAPI_SDCARD_DETECT_H_
#define _HWAPI_SDCARD_DETECT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"

// SD card detect port/pin defines
#define SDCARD_DETECT_PORT          GPIOA
#define SDCARD_DETECT_PIN           GPIO_Pin_0


/* Exported types ------------------------------------------------------------*/
typedef enum {
    SD_CARD_INSERT,
    SD_CARD_REMOVE
} SDCardDetectStatus_t;




/* Exported functions --------------------------------------------------------*/
SDCardDetectStatus_t HwAPI_SDCardDetect_GetStatus( void );

#endif /* _HWAPI_SDCARD_DETECT_H_*/
/* End of file */
