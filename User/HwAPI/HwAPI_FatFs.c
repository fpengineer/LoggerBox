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

#include "TS_HwQueue.h"

#include "HwAPI.h"

// Declare private functions
static void SetSDCardLED( FatFsStatus_t fatFsStatus );



//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t *data )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_INT;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    *data = hwFatFsQueueData.iniInfoData.intValue;

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyFloat( char *nameSection, char *nameKey, char *fileName, float *data )
{
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_FLOAT;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    *data = hwFatFsQueueData.iniInfoData.floatValue;

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyString( char *nameSection, char *nameKey, char *fileName, char *data )
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
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}

//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t data )
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
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyFloat( char *nameSection, char *nameKey, char *fileName, float data )
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
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    SetSDCardLED( hwFatFsQueueData.fatFsStatus );
    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyString( char *nameSection, char *nameKey, char *fileName, char *data )
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
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

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
FatFsStatus_t HwAPI_FatFs_CheckFileEXIST( char *fileName )
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
void HwAPI_FatFs_Run( void )
{
    extern TaskHandle_t xTask_HwFatFs;
    extern QueueHandle_t xQueue_HwFatFs_Rx;
    extern QueueHandle_t xQueue_HwFatFs_Tx;
    
    xQueue_HwFatFs_Rx = xQueueCreate( 5, sizeof( HwFatFsQueueData_t ) );
    xQueue_HwFatFs_Tx = xQueueCreate( 5, sizeof( HwFatFsQueueData_t ) );

	if( pdTRUE != xTaskCreate(  vTask_HwFatFs,
                                "Task - HwFatFs",
                                configMINIMAL_STACK_SIZE,
                                NULL,
                                tskIDLE_PRIORITY + 1,
                                &xTask_HwFatFs ) ) { /* some error action */ }	
}


//
HwAPI_BootStatus_t HwAPI_FatFs_GetBootStatus( void )
{
    extern HwAPI_BootStatus_t bootStatus_HwFatFs;
    
    return bootStatus_HwFatFs;
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

/* End of file */
