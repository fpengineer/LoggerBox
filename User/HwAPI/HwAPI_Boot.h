/*****************************************************************************************************

    HwAPI Boot



*******************************************************************************************************/
#ifndef _HW_API_BOOT_H_
#define _HW_API_BOOT_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"


/* Exported types ------------------------------------------------------------*/
typedef enum {
    HW_BOOT_SUCCESS,
    HW_BOOT_IN_PROGRESS,
    HW_BOOT_ERROR,
    HW_BOOT_IDLE
} HwBootStatus_t;

typedef struct {
    HwBootStatus_t hwBootStatus;
    char *message;
} HwBootData_t;


/* Exported functions --------------------------------------------------------*/
HwBootData_t HwAPI_Boot_GetStatus( void );

#endif /* _HW_API_BOOT_H_*/
/* End of file */
