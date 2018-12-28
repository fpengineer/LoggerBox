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


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t *data )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_INT;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    *data = hwFatFsQueueData.iniInfoData.intValue;

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyFloat( char *nameSection, char *nameKey, char *fileName, float *data )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_FLOAT;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    *data = hwFatFsQueueData.iniInfoData.floatValue;

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_GetKeyString( char *nameSection, char *nameKey, char *fileName, char *data )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_GET_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_STRING;
    hwFatFsQueueData.iniInfoData.stringValue = data;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}

//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyInt( char *nameSection, char *nameKey, char *fileName, int32_t data )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_PUT_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_INT;
    hwFatFsQueueData.iniInfoData.intValue = data;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;

}


//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyFloat( char *nameSection, char *nameKey, char *fileName, float data )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_PUT_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_FLOAT;
    hwFatFsQueueData.iniInfoData.floatValue = data;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_INI_PutKeyString( char *nameSection, char *nameKey, char *fileName, char *data )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_PUT_KEY_INI;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.iniInfoData.keyName = nameKey;
    hwFatFsQueueData.iniInfoData.sectionName = nameSection;
    hwFatFsQueueData.iniInfoData.keyType = INI_KEY_STRING;
    hwFatFsQueueData.iniInfoData.stringValue = data;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_CreateFile( char *fileName )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CREATE_FILE;
    hwFatFsQueueData.fileName = fileName;
    
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_CheckFileEXIST( char *fileName )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CHECK_FILE_EXIST;
    hwFatFsQueueData.fileName = fileName;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_OpenFile( char *fileName )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_OPEN_FILE;
    hwFatFsQueueData.fileName = fileName;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_CloseFile( char *fileName )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CLOSE_FILE;
    hwFatFsQueueData.fileName = fileName;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
FatFsStatus_t HwAPI_FatFs_WriteTextFile( char *fileName, char *textData )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_CLOSE_FILE;
    hwFatFsQueueData.fileName = fileName;
    hwFatFsQueueData.textBuffer = textData;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
    xQueueReceive( xQueue_HwFatFs_Tx, &hwFatFsQueueData, portMAX_DELAY );

    return hwFatFsQueueData.fatFsStatus;
}


//
void HwAPI_FatFs_InitSDCard( void )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_INIT_SD_CARD;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
}


//
void HwAPI_FatFs_DeinitSDCard( void )
{
    HwFatFsQueueData_t hwFatFsQueueData;
   
    hwFatFsQueueData.stateHwFatFs = HW_FATFS_DEINIT_SD_CARD;
        
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL );
}


/* End of file */
