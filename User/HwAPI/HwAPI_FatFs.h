/*****************************************************************************************************

    HwAPI FatFs



*******************************************************************************************************/


#ifndef _HWAPI_FATFS_H_
#define _HWAPI_FATFS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>

#include "HwAPI.h"

// define HWAPI_FATFS_DEBUG_INFO to allow debug info messages into terminal
//#define HWAPI_FATFS_DEBUG_INFO

#define MAX_FILES_TO_OPEN   10

#define MAX_INI_SECTION_LIST              5
#define MAX_INI_KEY_LIST                  32
#define MAX_INI_STRING_LENGTH             25



#define VOLUME_NAME   "0"

/* Exported types ------------------------------------------------------------*/
enum stateHwFatFs { 
    HW_FATFS_INIT,
    HW_FATFS_GET_STATUS,
    HW_FATFS_INIT_SD_CARD,
    HW_FATFS_DEINIT_SD_CARD,
    HW_FATFS_CREATE_FILE,
    HW_FATFS_CHECK_FILE_EXIST,
    HW_FATFS_OPEN_FILE,
    HW_FATFS_CLOSE_FILE,
    HW_FATFS_WRITE_FILE,
    HW_FATFS_GET_KEY_INI,
    HW_FATFS_PUT_KEY_INI,
    HW_FATFS_GET_CONFIG_FILE_STRINGS,
    HW_FATFS_IDLE 
};

typedef enum {
    FATFS_OK,
    FATFS_ERROR,
    FATFS_ERROR_NO_SD_CARD,
    FATFS_ERROR_INI_KEY_NOT_FOUND,
    FATFS_ERROR_INI_SECTION_NOT_FOUND,
    FATFS_ERROR_FILE_NOT_FOUND
} FatFsStatus_t;

typedef enum {
    FATFS_ENABLE,
    FATFS_DISABLE
} FatFsEnable_t;

typedef enum {
  INI_KEY_INT,
  INI_KEY_FLOAT,
  INI_KEY_STRING
} KeyType_t;

typedef enum ConfigFileType {
  MAIN_CONFIG_FILE,
  MEASURE_PLAN_FILE
} ConfigFileType_t;

typedef struct {
    char *sectionName;
    char *keyName;
    int32_t intValue;
    float floatValue;
    char *stringValue;
    KeyType_t keyType;
    ConfigFileType_t configFileType;
} INIInfoData_t;

typedef struct {
    char sectionName[ MAX_INI_STRING_LENGTH ];
    char keyList [ MAX_INI_KEY_LIST ][ MAX_INI_STRING_LENGTH ];
} INIConfigStrings_t;

typedef struct {
    enum stateHwFatFs stateHwFatFs;
    FatFsStatus_t fatFsStatus;
    FatFsEnable_t fatFsEnable;
//    SDCardStatus_t sdCardStatus;

    char *textBuffer;
    char *fileName;
    uint8_t fileIndex;
    INIInfoData_t iniInfoData;
} HwFatFsQueueData_t;




/* Exported functions --------------------------------------------------------*/
FatFsStatus_t HwAPI_FatFs_INI_GetKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t *data, ConfigFileType_t configFileType );
FatFsStatus_t HwAPI_FatFs_INI_GetKeyFloat( char *nameSection, char *nameKey, char *fileName, float *data, ConfigFileType_t configFileType );
FatFsStatus_t HwAPI_FatFs_INI_GetKeyString( char *nameSection, char *nameKey, char *fileName, char *data, ConfigFileType_t configFileType );
FatFsStatus_t HwAPI_FatFs_INI_PutKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t data, ConfigFileType_t configFileType );
FatFsStatus_t HwAPI_FatFs_INI_PutKeyFloat( char *nameSection, char *nameKey, char *fileName, float data, ConfigFileType_t configFileType );
FatFsStatus_t HwAPI_FatFs_INI_PutKeyString( char *nameSection, char *nameKey, char *fileName, char *data, ConfigFileType_t configFileType );

FatFsStatus_t HwAPI_FatFs_CreateFile( char *fileName );
FatFsStatus_t HwAPI_FatFs_CheckFileExist( char *fileName );
FatFsStatus_t HwAPI_FatFs_OpenFile( char *fileName );
FatFsStatus_t HwAPI_FatFs_CloseFile( char *fileName );
FatFsStatus_t HwAPI_FatFs_WriteTextFile( char *fileName, char *textData );

void HwAPI_FatFs_InitSDCard( void );
void HwAPI_FatFs_DeinitSDCard( void );

FatFsStatus_t HwAPI_FatFs_GetStatus( void );

void vTask_HwFatFs( void *pvParameters );
HwAPI_BootStatus_t HwAPI_FatFs_Run( void );

FatFsStatus_t HwAPI_FatFs_INI_GetConfigFileStrings( char *fileName, ConfigFileType_t configFileType );

#endif /* _HWAPI_FATFS_H_*/
/* End of file */
