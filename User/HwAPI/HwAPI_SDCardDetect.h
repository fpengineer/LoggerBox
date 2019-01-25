/*****************************************************************************************************

    HwAPI SD card detect



*******************************************************************************************************/


#ifndef _HWAPI_SDCARD_DETECT_H_
#define _HWAPI_SDCARD_DETECT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"

// SD card detect port/pin defines
#define SDCARD_DETECT_PORT          GPIOA
#define SDCARD_DETECT_PIN           GPIO_Pin_0


/* Exported types ------------------------------------------------------------*/
enum stateHwSDCardDetect {
    HW_SDCARD_DETECT_INIT,
    HW_SDCARD_DETECT_GET,
    HW_SDCARD_DETECT_INSERT,
    HW_SDCARD_DETECT_REMOVE,
    HW_SDCARD_DETECT_IDLE
};

typedef enum {
    SD_CARD_INSERT,
    SD_CARD_REMOVE
} SDCardDetectStatus_t;

typedef struct {
    enum stateHwSDCardDetect stateHwSDCardDetect;
    SDCardDetectStatus_t sdCardDetectStatus;
} HwSDCardDetectQueueData_t;



/* Exported functions --------------------------------------------------------*/
SDCardDetectStatus_t HwAPI_SDCardDetect_GetStatus( void );

void vTask_HwSDCardDetect( void *pvParameters );
void HwAPI_SDCardDetect_Run( void );
HwAPI_BootStatus_t HwAPI_SDCardDetect_GetBootStatus( void );
#endif /* _HWAPI_SDCARD_DETECT_H_*/
/* End of file */
