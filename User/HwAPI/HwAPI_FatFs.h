/*****************************************************************************************************

    HwAPI FatFs



*******************************************************************************************************/


#ifndef _HWAPI_FATFS_H_
#define _HWAPI_FATFS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI Def.h"



#define MAX_FILES_TO_OPEN

/* Exported types ------------------------------------------------------------*/
typedef enum {
    FATFS_OK,
    FATFS_ERROR,
    FATFS_ERROR_NO_SD_CARD,
    FATFS_ERROR_INI_KEY_NOT_FOUND,
    FATFS_ERROR_FILE_NOT_FOUND
} FatFsStatus_t;


typedef enum {
    SD_CARD_INSERT,
    SD_CARD_NOT_INSERT
} SDCardStatus_t;


enum KeyType {
  INI_KEY_INT,
  INI_KEY_FLOAT,
  INI_KEY_STRING
};

typedef struct {
    char *nameSection;
    char *nameKey;
    int32_t intValue;
    float floatValue;
    char *stringValue;
    enum KeyType keyType;
} INIInfoData_t;




/* Exported functions --------------------------------------------------------*/
FatFsStatus_t HwAPI_FatFs_INI_GetKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t *data );
FatFsStatus_t HwAPI_FatFs_INI_GetKeyFloat( char *nameSection, char *nameKey, char *fileName, float *data );
FatFsStatus_t HwAPI_FatFs_INI_GetKeyString( char *nameSection, char *nameKey, char *fileName, char *data );
FatFsStatus_t HwAPI_FatFs_INI_PutKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t data );
FatFsStatus_t HwAPI_FatFs_INI_PutKeyFloat( char *nameSection, char *nameKey, char *fileName, float data );
FatFsStatus_t HwAPI_FatFs_INI_PutKeyString( char *nameSection, char *nameKey, char *fileName, char *data );

FatFsStatus_t HwAPI_FatFs_CreateFile( char *fileName );
FatFsStatus_t HwAPI_FatFs_CheckFileExist( char *fileName );
FatFsStatus_t HwAPI_FatFs_OpenFile( char *fileName );
FatFsStatus_t HwAPI_FatFs_CloseFile( char *fileName );
FatFsStatus_t HwAPI_FatFs_WriteTextFile( char *fileName, char *textData );



#endif /* _HWAPI_FATFS_H_*/
/* End of file */
