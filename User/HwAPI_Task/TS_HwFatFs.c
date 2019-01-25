/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - FatFs

*******************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_rtc.h"
#include "tm_stm32f4_fatfs.h"

#include "HwAPI.h"

#include "minIni.h"

TaskHandle_t xTask_HwFatFs;
QueueHandle_t xQueue_HwFatFs_Rx;
QueueHandle_t xQueue_HwFatFs_Tx;
HwAPI_BootStatus_t bootStatus_HwFatFs = HW_TASK_BOOT_IDLE;


// Declare private functions
static FatFsStatus_t CheckFileExist( char *fileName );
static FatFsStatus_t CheckSectionINI( char *sectionName, char *fileName );
static FatFsStatus_t CheckKeyINI( char *keyName, char *sectionName, char *fileName );







static char *stringResult [20] = {
	"FR_OK",				/* (0) Succeeded */
	"FR_DISK_ERR",			/* (1) A hard error occurred in the low level disk I/O layer */
	"FR_INT_ERR",				/* (2) Assertion failed */
	"FR_NOT_READY",			/* (3) The physical drive cannot work */
	"FR_NO_FILE",				/* (4) Could not find the file */
	"FR_NO_PATH",				/* (5) Could not find the path */
	"FR_INVALID_NAME",		/* (6) The path name format is invalid */
	"FR_DENIED",				/* (7) Access denied due to prohibited access or directory full */
	"FR_EXIST",				/* (8) Access denied due to prohibited access */
	"FR_INVALID_OBJECT",		/* (9) The file/directory object is invalid */
	"FR_WRITE_PROTECTED",		/* (10) The physical drive is write protected */
	"FR_INVALID_DRIVE",		/* (11) The logical drive number is invalid */
	"FR_NOT_ENABLED",			/* (12) The volume has no work area */
	"FR_NO_FILESYSTEM",		/* (13) There is no valid FAT volume */
	"FR_MKFS_ABORTED",		/* (14) The f_mkfs() aborted due to any problem */
	"FR_TIMEOUT",				/* (15) Could not get a grant to access the volume within defined period */
	"FR_LOCKED",				/* (16) The operation is rejected according to the file sharing policy */
	"FR_NOT_ENOUGH_CORE",		/* (17) LFN working buffer could not be allocated */
	"FR_TOO_MANY_OPEN_FILES",	/* (18) Number of open files > FF_FS_LOCK */
	"FR_INVALID_PARAMETER"	/* (19) Given parameter is invalid */
};
/* Fatfs object */
static FATFS FatFs;
/* File object */
static FIL fileObjectSet[ MAX_FILES_TO_OPEN ];
//static FIL fileConfig;
//static FILINFO fno;
//static DIR dir;
static FRESULT result = FR_NOT_READY;

static char tempString[450] = {""}; 
//static char headerString[1800] = {""}; 
//static char measureString[1800] = {""}; 
static char filePath[80] = {""}; 


void vTask_HwFatFs( void *pvParameters )
{
    HwFatFsQueueData_t hwFatFsQueueData;
//    SDCardStatus_t sdCardStatus = SD_CARD_NOT_INSERT;
    FatFsStatus_t fatFsStatus = FATFS_ERROR_NO_SD_CARD;
    FatFsEnable_t fatFsEnable = FATFS_DISABLE;
    

    hwFatFsQueueData.stateHwFatFs = HW_FATFS_INIT;            
    xQueueSend( xQueue_HwFatFs_Rx, &hwFatFsQueueData, NULL ); 

    while (1)
    {
        xQueueReceive( xQueue_HwFatFs_Rx, &hwFatFsQueueData, portMAX_DELAY );
        switch ( hwFatFsQueueData.stateHwFatFs )
        {
            case HW_FATFS_INIT:
            {
                // Init FatFs module
                f_mount( &FatFs, "0:", 1 );
                f_mount( 0, "0:", 1 );

                bootStatus_HwFatFs = HW_TASK_BOOT_PENDING;
                break;
            }

            case HW_FATFS_GET_STATUS:
            {
                hwFatFsQueueData.fatFsEnable = fatFsEnable;            
                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }
            
            case HW_FATFS_INIT_SD_CARD:
            {    
                HwAPI_Terminal_SendMessage( "TS_HwFatFs: Initialize SD Card\n" );

                f_mount( 0, "0:", 1 ); // Unmount drive
                result = f_mount( &FatFs, "0:", 1 );
                sprintf( tempString, "f_mount = %s\n", stringResult[ result ] );
                HwAPI_Terminal_SendMessage( tempString );

                switch ( result )
                {
                    case FR_OK:
                        fatFsStatus = FATFS_OK;
                        fatFsEnable = FATFS_ENABLE;
                        break;

                    default:
                        fatFsStatus = FATFS_ERROR;
                        fatFsEnable = FATFS_DISABLE;
                        sprintf( tempString, "TS_HwFatFs: HW_FATFS_INIT_SD_CARD Error!\n"
                                             "f_mount = %s\n", stringResult[ result ] );
                        HwAPI_Terminal_SendMessage( tempString );
                        break;
                }
                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_DEINIT_SD_CARD:
            {
                //Close all opened files
                //f_close(&fil);
                f_mount(0, "0:", 1);
                //xQueueReset( xQueue_HwFatFs_Rx );

                fatFsStatus = FATFS_ERROR_NO_SD_CARD;
                fatFsEnable = FATFS_DISABLE;
                hwFatFsQueueData.fatFsEnable = fatFsEnable;            
                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }             

                    
            case HW_FATFS_CREATE_FILE:
            {    
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    f_close( &fileObjectSet[ hwFatFsQueueData.fileIndex ] );
                    sprintf( filePath, "0:/%s", hwFatFsQueueData.fileName );
                    result = f_open( &fileObjectSet[ hwFatFsQueueData.fileIndex ], filePath, FA_CREATE_ALWAYS | FA_WRITE | FA_READ );

                    
                    switch ( result )
                    {
                        case FR_OK:
                            f_close( &fileObjectSet[ hwFatFsQueueData.fileIndex ] );
                            fatFsStatus = FATFS_OK;
                            break;

                        default:
                            sprintf( tempString, "TS_HwFatFs: HW_FATFS_CREATE_FILE Error!\n"
                                                 "f_open = %s\n", stringResult[ result ] );
                            HwAPI_Terminal_SendMessage( tempString );
                            fatFsStatus = FATFS_ERROR;
                            break;
                    }
                }                    

                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_CHECK_FILE_EXIST:
            {    
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    sprintf( filePath, "0:/%s", hwFatFsQueueData.fileName );
                    result = f_stat( filePath, NULL );
                    
                    switch ( result )
                    {
                        case FR_OK:
                            fatFsStatus = FATFS_OK;
                            break;

                        case FR_NO_FILE:
                            fatFsStatus = FATFS_ERROR_FILE_NOT_FOUND;
                            break;
                        
                        default:
                            sprintf( tempString, "TS_HwFatFs: HW_FATFS_CHECK_FILE_EXIST Error!\n"
                                                 "f_stat = %s\n", stringResult[ result ] );
                            HwAPI_Terminal_SendMessage( tempString );
                            fatFsStatus = FATFS_ERROR;
                            break;
                    }
                }                    

                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_OPEN_FILE:
            {    
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    f_close( &fileObjectSet[ hwFatFsQueueData.fileIndex ] );
                    sprintf( filePath, "0:/%s", hwFatFsQueueData.fileName );
                    result = f_open( &fileObjectSet[ hwFatFsQueueData.fileIndex ], filePath, FA_OPEN_EXISTING | FA_WRITE | FA_READ );
                    
                    switch ( result )
                    {
                        case FR_OK:
                            f_close( &fileObjectSet[ hwFatFsQueueData.fileIndex ] );
                            fatFsStatus = FATFS_OK;
                            break;

                        case FR_NO_FILE:
                            fatFsStatus = FATFS_ERROR_FILE_NOT_FOUND;
                            break;

                        default:
                            sprintf( tempString, "TS_HwFatFs: HW_FATFS_OPEN_FILE Error!\n"
                                                 "f_open = %s\n", stringResult[ result ] );
                            HwAPI_Terminal_SendMessage( tempString );
                            fatFsStatus = FATFS_ERROR;
                            break;
                    }
                }                    

                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_CLOSE_FILE:
            {    
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    result = f_close( &fileObjectSet[ hwFatFsQueueData.fileIndex ] );
                    
                    switch ( result )
                    {
                        case FR_OK:
                            fatFsStatus = FATFS_OK;
                            break;

                        default:
                            sprintf( tempString, "TS_HwFatFs: HW_FATFS_CLOSE_FILE Error!\n"
                                                 "f_close = %s\n", stringResult[ result ] );
                            HwAPI_Terminal_SendMessage( tempString );
                            fatFsStatus = FATFS_ERROR;
                            break;
                    }
                }                    

                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_WRITE_FILE:
            {    
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    result = f_lseek( &fileObjectSet[ hwFatFsQueueData.fileIndex ],
                                      f_size( &fileObjectSet[ hwFatFsQueueData.fileIndex ] ) );
                    
                    switch ( result )
                    {
                        case FR_OK:
                            fatFsStatus = FATFS_OK;
                            if ( f_puts( hwFatFsQueueData.textBuffer, &fileObjectSet[ hwFatFsQueueData.fileIndex ] ) > 0 )
                            {
                                // success
                            }
                            else
                            {
                                // error
                            }
/*
                            switch ( result )
                            {
                                case FR_OK:
                                    fatFsStatus = FATFS_OK;
                                    break;

                                default:
                                    sprintf( tempString, "TS_HwFatFs: HW_FATFS_WRITE_FILE Error!\n"
                                                         "f_puts = %s\n", stringResult[ result ] );
                                    HwAPI_Terminal_SendMessage( tempString );
                                    fatFsStatus = FATFS_ERROR;
                                    break;
                            }
*/
                            break;

                        default:
                            sprintf( tempString, "TS_HwFatFs: HW_FATFS_WRITE_FILE Error!\n"
                                                 "f_lseek = %s\n", stringResult[ result ] );
                            HwAPI_Terminal_SendMessage( tempString );
                            fatFsStatus = FATFS_ERROR;
                            break;
                    }
                }                    

                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_GET_KEY_INI:
            {
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    // check if file exist
                    fatFsStatus = CheckFileExist( hwFatFsQueueData.fileName );
                    if ( fatFsStatus == FATFS_OK )
                    {
                        // check if section exist
                        fatFsStatus = CheckSectionINI( hwFatFsQueueData.iniInfoData.sectionName, hwFatFsQueueData.fileName );
                        if ( fatFsStatus == FATFS_OK )
                        {
                            // check if key exist
                            fatFsStatus = CheckKeyINI( hwFatFsQueueData.iniInfoData.keyName, hwFatFsQueueData.iniInfoData.sectionName, hwFatFsQueueData.fileName );
                            if ( fatFsStatus == FATFS_OK )
                            {
                                // get key value
                                switch ( hwFatFsQueueData.iniInfoData.keyType )
                                {
                                    case INI_KEY_INT:
                                        hwFatFsQueueData.iniInfoData.intValue = ini_getl( hwFatFsQueueData.iniInfoData.sectionName, 
                                                                                          hwFatFsQueueData.iniInfoData.keyName,     
                                                                                          -1,                                       
                                                                                          hwFatFsQueueData.fileName );    
                                        break;
                    
                                    case INI_KEY_FLOAT:
                                        hwFatFsQueueData.iniInfoData.floatValue = ini_getf( hwFatFsQueueData.iniInfoData.sectionName, 
                                                                                          hwFatFsQueueData.iniInfoData.keyName,     
                                                                                          0.0f,                                       
                                                                                          hwFatFsQueueData.fileName );    
                                        break;
                    	
                                    case INI_KEY_STRING:
                                        ini_gets( hwFatFsQueueData.iniInfoData.sectionName, 
                                                  hwFatFsQueueData.iniInfoData.keyName,
                                                  "key not found", 
                                                  hwFatFsQueueData.iniInfoData.stringValue, 
                                                  MAX_INI_KEY_STRING_VALUE_LENGTH, 
                                                  hwFatFsQueueData.fileName );
                                        break;
                    	
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }                
                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }             

                    
            case HW_FATFS_PUT_KEY_INI:
            {
                if ( fatFsEnable == FATFS_ENABLE )
                {
                    // check if file exist
                    fatFsStatus = CheckFileExist( hwFatFsQueueData.fileName );
                    if ( fatFsStatus == FATFS_OK )
                    {
                        // check if section exist
                        fatFsStatus = CheckSectionINI( hwFatFsQueueData.iniInfoData.sectionName, hwFatFsQueueData.fileName );
                        if ( fatFsStatus == FATFS_OK )
                        {
                            // check if key exist
                            fatFsStatus = CheckKeyINI( hwFatFsQueueData.iniInfoData.keyName, hwFatFsQueueData.iniInfoData.sectionName, hwFatFsQueueData.fileName );
                            if ( fatFsStatus == FATFS_OK )
                            {
                                // get key value
                                switch ( hwFatFsQueueData.iniInfoData.keyType )
                                {
                                    case INI_KEY_INT:
                                        ini_putl( hwFatFsQueueData.iniInfoData.sectionName, \
                                                  hwFatFsQueueData.iniInfoData.keyName,     \
                                                  hwFatFsQueueData.iniInfoData.intValue,    \
                                                  hwFatFsQueueData.fileName );    
                                        break;
                    
                                    case INI_KEY_FLOAT:
                                        ini_putf( hwFatFsQueueData.iniInfoData.sectionName, \
                                                  hwFatFsQueueData.iniInfoData.keyName,     \
                                                  hwFatFsQueueData.iniInfoData.floatValue,  \
                                                  hwFatFsQueueData.fileName );    
                                        break;
                    	
                                    case INI_KEY_STRING:
                                        ini_puts( hwFatFsQueueData.iniInfoData.sectionName, \
                                                  hwFatFsQueueData.iniInfoData.keyName,     \
                                                  hwFatFsQueueData.iniInfoData.stringValue, \
                                                  hwFatFsQueueData.fileName );
                                        break;
                    	
                                    default:
                                        break;
                                }
                            }
                        }
                    }
                }                
                hwFatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &hwFatFsQueueData, NULL ); 
                break;
            }             

                case HW_FATFS_IDLE:
                break;

            default:
                break;
        }
    }
}






//*************************************************
//
// Private function
//
// check if file exist
//
//*************************************************
static FatFsStatus_t CheckFileExist( char *fileName )
{
    char filePath[ 80 ] = {""};
    FatFsStatus_t fatFsStatus = FATFS_OK;
    FRESULT fresult = FR_OK;

    sprintf( filePath, "%s:/%s", VOLUME_NAME, fileName );
    fresult = f_stat( filePath, NULL );
    switch ( fresult )
    {
        case FR_OK:
            fatFsStatus = FATFS_OK;
            break;

        case FR_NO_FILE:
            fatFsStatus = FATFS_ERROR_FILE_NOT_FOUND;
            break;
                        
        default:
            sprintf( tempString, "CheckFileExist() - Error!\n"
                                 "f_stat( %s, NULL) = %s\n", filePath, stringResult[ fresult ] );
            HwAPI_Terminal_SendMessage( tempString );
            fatFsStatus = FATFS_ERROR;
            break;
    }
    return fatFsStatus;
}



//*************************************************
//
// Private function
//
// check if section exist in INI file
//
//*************************************************
static FatFsStatus_t CheckSectionINI( char *sectionName, char *fileName )
{
    char filePath[ 80 ] = {""};
    int32_t sectionIndex = 0;   
    char sectionNameBuffer[ MAX_INI_SECTION_NAME_LENGTH ] = {""};

    sprintf( filePath, "%s:/%s", VOLUME_NAME, fileName );

    for ( sectionIndex = 0; ini_getsection( sectionIndex, sectionNameBuffer, MAX_INI_SECTION_NAME_LENGTH, filePath ) > 0; sectionIndex++ ){;}
    if ( sectionIndex == 0 )
    {
        return FATFS_ERROR_INI_SECTION_NOT_FOUND;
    }

    return FATFS_OK;
}



//*************************************************
//
// Private function
//
// check if section exist in INI file
//
//*************************************************
static FatFsStatus_t CheckKeyINI( char *keyName, char *sectionName, char *fileName )
{
    char filePath[ 80 ] = {""};
    int32_t keyIndex = 0;   
    char keyNameBuffer[ MAX_INI_SECTION_NAME_LENGTH ] = {""};

    sprintf( filePath, "%s:/%s", VOLUME_NAME, fileName );

    for ( keyIndex = 0; ini_getkey( sectionName, keyIndex, keyNameBuffer, MAX_INI_KEY_NAME_LENGTH, filePath ) > 0; keyIndex++ ){;}
    if ( keyIndex == 0 )
    {
        return FATFS_ERROR_INI_KEY_NOT_FOUND;
    }

    return FATFS_OK;
}




/* End of file */
