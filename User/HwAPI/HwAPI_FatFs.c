/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: HwAPI for FatFs

*******************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "HwAPI.h"

// Declare private functions
static void SetSDCardLED( FatFsStatus_t fatFsStatus );
static void INIActionErrorMessage( FatFsStatus_t fatFsStatus, char *nameSection, char *nameKey, char *fileName );


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyInt( char *nameSection,                 \
                                         char *nameKey,                     \
                                         char *fileName,                    \
                                         int32_t *data,                     \
                                         ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
    
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_INT;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    if ( hwFatFsQueueData.fatFsStatus == FATFS_OK )
    {
        *data = hwFatFsQueueData.iniInfoData.intValue;
    }
    
    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, nameSection, nameKey, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyFloat( char *nameSection,               \
                                           char *nameKey,                   \
                                           char *fileName,                  \
                                           float *data,                     \
                                           ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_FLOAT;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    if ( hwFatFsQueueData.fatFsStatus == FATFS_OK )
    {
        *data = hwFatFsQueueData.iniInfoData.floatValue;
    }
    
    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, nameSection, nameKey, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyString( char *nameSection,              \
                                            char *nameKey,                  \
                                            char *fileName,                 \
                                            char *data,                     \
                                            ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_STRING;
    hwFatFsQueueData.iniInfoData.stringValue = data;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, nameSection, nameKey, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}

//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyInt( char *nameSection,             \
                                         char *nameKey,                 \
                                         char *fileName,                \
                                         int32_t data,                  \
                                         ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_PUT_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_INT;
    hwFatFsQueueData.iniInfoData.intValue = data;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, nameSection, nameKey, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyFloat( char *nameSection,               \
                                           char *nameKey,                   \
                                           char *fileName,                  \
                                           float data,                      \
                                           ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_PUT_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_FLOAT;
    hwFatFsQueueData.iniInfoData.floatValue = data;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, nameSection, nameKey, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyString( char *nameSection,              \
                                            char *nameKey,                  \
                                            char *fileName,                 \
                                            char *data,                     \
                                            ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_PUT_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_STRING;
    hwFatFsQueueData.iniInfoData.stringValue = data;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, nameSection, nameKey, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_CreateFile( char *fileName )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CREATE_FILE;
    hwFatFsQueueData.fileName = fileName;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_CheckFileExist( char *fileName )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CHECK_FILE_EXIST;
    hwFatFsQueueData.fileName = fileName;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_OpenFile( char *fileName )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_OPEN_FILE;
    hwFatFsQueueData.fileName = fileName;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_CloseFile( char *fileName )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CLOSE_FILE;
    hwFatFsQueueData.fileName = fileName;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_WriteTextFile( char *fileName, char *textData )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CLOSE_FILE;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.textBuffer = textData;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
void HwAPI_FatFs_InitSDCard( void )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_INIT_SD_CARD;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
}


//
void HwAPI_FatFs_DeinitSDCard( void )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_DEINIT_SD_CARD;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
}


//
FatFsStatus_t HwAPI_FatFs_GetStatus( void )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_STATUS;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
HwAPI_BootStatus_t HwAPI_FatFs_Run( void )
{
    extern TaskHandle_t xTask_HwFatFs;
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    extern volatile HwAPI_BootStatus_t bootStatus_HwFatFs;
    
    xQueue_HwFatFs_Rx = xQueueCreate( 5, sizeof( HwFatFsQueueData_t ) );
    xQueue_HwFatFs_Tx = xQueueCreate( 5, sizeof( HwFatFsQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwFatFs,
                                "Task - HwFatFs",
                                configMINIMAL_STACK_SIZE + 5000,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwFatFs ) ) { /* some error action */ }	

    while ( bootStatus_HwFatFs == HW_TASK_BOOT_IDLE ){;}
    
    if ( bootStatus_HwFatFs == HW_TASK_BOOT_PENDING )
    {
        bootStatus_HwFatFs = HW_TASK_BOOT_RUN;
    }
    
    return bootStatus_HwFatFs;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetConfigFileStrings( char *fileName, ConfigFileType_t configFileType )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
    
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_CONFIG_FILE_STRINGS;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.configFileType = configFileType;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    INIActionErrorMessage( hwFatFsQueueData.fatFsStatus, NULL, NULL, fileName );
    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//*************************************************
//
// Private function
//
// Set SD card LED according to fatfs status
//
//*************************************************
static void SetSDCardLED( FatFsStatus_t fatFsStatus )
{
    switch ( fatFsStatus )
    {
        case FATFS_OK:
            HwAPI_SDCardLED_On();    
            break;
    
        case FATFS_ERROR:
            HwAPI_SDCardLED_Flash( SDCARD_LED_FLASH_FAST );
            break;
    	
        case FATFS_ERROR_NO_SD_CARD:
            HwAPI_SDCardLED_Off();    
            break;
    	
        case FATFS_ERROR_INI_KEY_NOT_FOUND:
            HwAPI_SDCardLED_Flash( SDCARD_LED_FLASH_SLOW );
            break;
    	
        case FATFS_ERROR_INI_SECTION_NOT_FOUND:
            HwAPI_SDCardLED_Flash( SDCARD_LED_FLASH_SLOW );
            break;
    	
        case FATFS_ERROR_FILE_NOT_FOUND:
            HwAPI_SDCardLED_Flash( SDCARD_LED_FLASH_SLOW );
            break;
    	
        default:
            break;
    }
}


//*************************************************
//
// Private function
//
// Process action result for the ini files
//
//*************************************************
static void INIActionErrorMessage( FatFsStatus_t fatFsStatus, char *nameSection, char *nameKey, char *fileName )
{
    char tempString[ 150 ] = { "" };
    
    switch ( fatFsStatus )
    {
        case FATFS_ERROR_FILE_NOT_FOUND:
        {    
            snprintf( tempString,
                      sizeof( tempString ),
                      "Error! File '%s' did not found!\n",
                      fileName );
            HwAPI_Terminal_SendMessage( tempString );
            break;
        }

        case FATFS_ERROR_INI_SECTION_NOT_FOUND:
        {    
            snprintf( tempString, 
                      sizeof( tempString ),
                      "Error! Section [%s] did not found in the '%s' file!\n",
                      nameSection,
                      fileName );
            HwAPI_Terminal_SendMessage( tempString );
            break;
        }

        case FATFS_ERROR_INI_KEY_NOT_FOUND:
        {
            snprintf( tempString, 
                      sizeof( tempString ),
                      "Error! Key '%s' did not found in the section [%s] in the '%s' file!\n",
                      nameKey,
                      nameSection,
                      fileName );
            HwAPI_Terminal_SendMessage( tempString );
            break;
        }

        default:
            break;
    }
}

/* End of file */
