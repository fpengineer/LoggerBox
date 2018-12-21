/*****************************************************************************************************

    HwAPI FatFs



*******************************************************************************************************/


#ifndef _HWAPI_FATFS_H_
#define _HWAPI_FATFS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"


/* Exported types ------------------------------------------------------------*/
enum KeyType {
  INI_KEY_INT,
  INI_KEY_FLOAT,
  INI_KEY_STRING
};

/* Exported functions --------------------------------------------------------*/
void HwAPI_FatFs_GetKeyINI( enum KeyType, char *nameSection, char *nameKey, char *fileName, void *data );
void HwAPI_FatFs_PutKeyINI( enum KeyType, char *nameSection, char *nameKey, char *fileName, void *data );



#endif /* _HWAPI_FATFS_H_*/
/* End of file */
