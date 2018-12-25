/*****************************************************************************************************

    Project: 
    
    Date: 
    Author: Filipp Popov

    Overview: Task - FatFs

*******************************************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Include core modules */
#include "stm32f4xx.h"
/* Include my libraries here */
#include "defines.h"
#include "tm_stm32f4_rtc.h"
#include "tm_stm32f4_fatfs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "HwAPI.h"
#include "TS_HwQueue.h"
#include "TS_task.h"

#include "minIni.h"
//#include "Config.h"
#include "Measure.h"
//#include "MeasureString.h"


//TaskHandle_t xTask_DebugLedBlinker;
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
static FIL fileConfig;
static FILINFO fno;
static DIR dir;
static FRESULT result = FR_NOT_READY;

static char tempString[450] = {""}; 
static char headerString[1800] = {""}; 
static char measureString[1800] = {""}; 
static char filePath[80] = {""}; 


void vTask_HwFatFs( void *pvParameters )
{
    HwFatFsQueueData_t fatFsQueueData;
    SDCardStatus_t sdCardStatus = SD_CARD_NOT_INSERT;
    FatFsStatus_t fatFsStatus = FATFS_ERROR_NO_SD_CARD;

    fatFsQueueData.stateHwFatFs = HW_FATFS_INIT;            
    xQueueSend( xQueue_HwFatFs_Rx, &fatFsQueueData, NULL ); 

    while (1)
    {
        xQueueReceive( xQueue_HwFatFs_Rx, &fatFsQueueData, portMAX_DELAY );

        switch ( fatFsQueueData.stateHwFatFs )
        {
            case HW_FATFS_INIT:
            {
                // Init FatFs module
                f_mount( &FatFs, "0:", 1 );
                f_mount( 0, "0:", 1 );
                break;
            }

            case HW_FATFS_GET_STATUS:
            {
                fatFsQueueData.sdCardStatus = sdCardStatus;            
                fatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
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
                        break;

                    default:
                        fatFsStatus = FATFS_ERROR;
                        sprintf( tempString, "TS_HwFatFs: HW_FATFS_INIT_SD_CARD Error!\n"
                                             "f_mount = %s\n", stringResult[ result ] );
                        HwAPI_Terminal_SendMessage( tempString );
                        break;
                }
                fatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 

#if 0
                    result = f_stat("0:/config.ini", NULL);
                        switch ( result )
                        {
                            case FR_OK:
                                cardReady = 1;
                                cfgSystemTime = ConfigSystemTime_GetParameters();        
                                ConfigSystemTime_SendParametersToTerminal(cfgSystemTime);        
                                if (cfgSystemTime.UpdateSystemTime >= UPDATE_SYSTEM_TIME_ENABLE)
                                {
                                    /* Set new system time */
                                    SystemTimeQueueData.stateSystemTime = SYSTEM_TIME_SET;            
                                    SystemTimeQueueData.datatime = cfgSystemTime.datatime;            
                                    xQueueSend( xQueue_SystemTimeIn, &SystemTimeQueueData, NULL );
                                    ConfigSystemTime_MarkUpdated();

                                    vTaskDelay(50);
                                    xQueueSend( xQueue_Terminal, "\r\nSet new system time\r\n", NULL );
                                    SystemTimeQueueData.stateSystemTime = SYSTEM_TIME_GET;            
                                    xQueueSend( xQueue_SystemTimeIn, &SystemTimeQueueData, NULL );
                                    xQueueReceive( xQueue_SystemTimeOut, &SystemTimeQueueData, portMAX_DELAY );
                                    sprintf(tempString, "New system time - %02d.%02d.%02d %02d:%02d:%02d\r\n",
                                                        SystemTimeQueueData.datatime.date,
                                                        SystemTimeQueueData.datatime.month,
                                                        SystemTimeQueueData.datatime.year,
                                                        SystemTimeQueueData.datatime.hours,
                                                        SystemTimeQueueData.datatime.minutes,
                                                        SystemTimeQueueData.datatime.seconds);
                                    xQueueSend( xQueue_Terminal, &tempString, NULL );

                                }
                                /* Read initial config and sendit to terminal */
                                cfgMeasurePlan = ConfigMeasurePlan_GetParameters();
                                ConfigMeasurePlan_SendParametersToTerminal(cfgMeasurePlan);
                                cfgMeasureEnable = ConfigMeasureEnable_GetParameters();
                                ConfigMeasureEnable_SendParametersToTerminal(cfgMeasureEnable);
                                cfgDatafileSettings = ConfigDatafileSettings_GetParameters();
                                ConfigDatafileSettings_SendParametersToTerminal(cfgDatafileSettings);

                                xQueueSend( xQueue_Terminal, 
                                            "\r\nConfig read - success\r\n"
                                            "System ready to start measure\r\r\n", NULL );
                                
                                stateSDCardLed = SDCARD_LED_ON;
                                xQueueSend( xQueue_SDCardLed, &stateSDCardLed, NULL );
                                break;
                                    
                            case FR_NO_FILE:
                                stateSDCardLed = SDCARD_LED_FLASH;
                                xQueueSend( xQueue_SDCardLed, &stateSDCardLed, NULL );
                                sprintf(tempString, "file <0:/config.ini> not found!\r\n");
                                xQueueSend( xQueue_Terminal, &tempString, NULL );
                                break;
                            
                            default:
                                stateSDCardLed = SDCARD_LED_FLASH;
                                xQueueSend( xQueue_SDCardLed, &stateSDCardLed, NULL );
                                sprintf(tempString, "file <0:/config.ini> error!\r\n" 
                                                    "f_stat = %s\r\n", stringResult[result]);
                                xQueueSend( xQueue_Terminal, &tempString, NULL );
                                break;
                        }
                        break;

                    default:
                        FatFsQueueData.stateFatFs = FATFS_DEINIT_SD_CARD;            
                        xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL ); 
                        break;
#endif
                


                break;
            }


            case HW_FATFS_DEINIT_SD_CARD:
            {
                //Close all opened files
                //f_close(&fil);
                f_mount(0, "0:", 1);
                //xQueueReset( xQueue_HwFatFs_Rx );

                fatFsStatus = FATFS_ERROR_NO_SD_CARD;
                fatFsQueueData.fatFsStatus = fatFsStatus;            
                xQueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
                break;
            }             

                    
            case HW_FATFS_CREATE_FILE:
            {    
                if ( fatFsStatus == FATFS_OK )
                {
                    f_close( &fileObjectSet[ fatFsQueueData.fileIndex ] );
                    sprintf( filePath, "0:/%s", fatFsQueueData.fileName );
                    result = f_open( &fileObjectSet[ fatFsQueueData.fileIndex ], filePath, FA_CREATE_ALWAYS | FA_WRITE | FA_READ );

                    
                    switch ( result )
                    {
                        case FR_OK:
                            f_close( &fileObjectSet[ fatFsQueueData.fileIndex ] );
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

                fatFsQueueData.fatFsStatus = fatFsStatus;            
                QueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_CHECK_FILE_EXIST:
            {    
                if ( fatFsStatus == FATFS_OK )
                {
                    sprintf( filePath, "0:/%s", fatFsQueueData.fileName );
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

                fatFsQueueData.fatFsStatus = fatFsStatus;            
                QueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_OPEN_FILE:
            {    
                if ( fatFsStatus == FATFS_OK )
                {
                    f_close( &fileObjectSet[ fatFsQueueData.fileIndex ] );
                    sprintf( filePath, "0:/%s", fatFsQueueData.fileName );
                    result = f_open( &fileObjectSet[ fatFsQueueData.fileIndex ], filePath, FA_OPEN_EXISTING | FA_WRITE | FA_READ );
                    
                    switch ( result )
                    {
                        case FR_OK:
                            f_close( &fileObjectSet[ fatFsQueueData.fileIndex ] );
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

                fatFsQueueData.fatFsStatus = fatFsStatus;            
                QueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_CLOSE_FILE:
            {    
                if ( fatFsStatus == FATFS_OK )
                {
                    result = f_close( &fileObjectSet[ fatFsQueueData.fileIndex ] );
                    
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

                fatFsQueueData.fatFsStatus = fatFsStatus;            
                QueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
                break;
            }


            case HW_FATFS_WRITE_FILE:
            {    
                if ( fatFsStatus == FATFS_OK )
                {
                    result = f_lseek( &fileObjectSet[ fatFsQueueData.fileIndex ],
                                      f_size( &fileObjectSet[ fatFsQueueData.fileIndex ] ) );
                    
                    switch ( result )
                    {
                        case FR_OK:
                            fatFsStatus = FATFS_OK;
                            result = f_puts( fatFsQueueData.textBuffer, &fileObjectSet[ fatFsQueueData.fileIndex ] );
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
                            break;

                        default:
                            sprintf( tempString, "TS_HwFatFs: HW_FATFS_WRITE_FILE Error!\n"
                                                 "f_lseek = %s\n", stringResult[ result ] );
                            HwAPI_Terminal_SendMessage( tempString );
                            fatFsStatus = FATFS_ERROR;
                            break;
                    }
                }                    

                fatFsQueueData.fatFsStatus = fatFsStatus;            
                QueueSend( xQueue_HwFatFs_Tx, &fatFsQueueData, NULL ); 
                break;
            }




            
            
            
            
            case FATFS_CREATE_NEW_MEASUREMENT_FILE:
                if (cardReady)
                {
                    /* Request current system time */
                    SystemTimeQueueData.stateSystemTime = SYSTEM_TIME_GET;            
                    xQueueSend( xQueue_SystemTimeIn, &SystemTimeQueueData, NULL );
                    xQueueReceive( xQueue_SystemTimeOut, &SystemTimeQueueData, portMAX_DELAY );
                    sprintf(pathMeasureFile, "0:/measure/%s_%02d.%02d.%02d_%02d.%02d.%02d.csv",
                                             cfgDatafileSettings.prefixDatafileName,
                                             SystemTimeQueueData.datatime.date,
                                             SystemTimeQueueData.datatime.month,
                                             SystemTimeQueueData.datatime.year,
                                             SystemTimeQueueData.datatime.hours,
                                             SystemTimeQueueData.datatime.minutes,
                                             SystemTimeQueueData.datatime.seconds);

                    sprintf(tempString, "Create new measurement file - %s\r\n", pathMeasureFile);
                    xQueueSend( xQueue_Terminal, &tempString, NULL );

                    f_close(&fil);
                    result = f_open(&fil, pathMeasureFile, FA_CREATE_ALWAYS | FA_WRITE | FA_READ);
//                    sprintf(tempString, "f_open = %s\n", stringResult[result]);
//                    xQueueSend( xQueue_Terminal, &tempString, NULL );
                    if (result == FR_OK)
                    {
                        sprintf(tempString, "New file <%s> have been created!\r\r\n", pathMeasureFile);
                        xQueueSend( xQueue_Terminal, &tempString, NULL );
                        ClearString(headerString, sizeof(headerString));
                        CreateHeaderString(cfgMeasureEnable, headerString, cfgDatafileSettings.delimiter);
                        sprintf(tempString, "[MeasurePlan]\n"
                                            "Tact1_Length_s = %d\n"
                                            "Tact2_Length_s = %d\n"
                                            "Tact3_Length_s = %d\n"
                                            "SourceG1_V = %.1f\n"
                                            "SourceG2_V = %.1f\n"
                                            "SourceG3_V = %.1f\n"
                                            "SourceG4_V = %.1f\n"
                                            "\nMeasured Data\n"
                                            "%s",
                                            cfgMeasurePlan.Tact1_Length_s,
                                            cfgMeasurePlan.Tact2_Length_s,
                                            cfgMeasurePlan.Tact3_Length_s,
                                            cfgMeasurePlan.SourceG1_V,
                                            cfgMeasurePlan.SourceG2_V,
                                            cfgMeasurePlan.SourceG3_V,
                                            cfgMeasurePlan.SourceG4_V,
                                            headerString);
                        f_puts(tempString, &fil);
                        f_close(&fil);
                        stringCounter = 0;
                        FatFsQueueData.configFileExistFlag = 1;    
                        xQueueSend( xQueue_FatFsOut, &FatFsQueueData, NULL );
                        ClearString(headerString, sizeof(headerString));
                        CreateHeaderString(cfgMeasureEnable, headerString, "\t");
                        sprintf(tempString, "\r[MeasurePlan]\r\n"
                                            "Tact1_Length_s = %d\r\n"
                                            "Tact2_Length_s = %d\r\n"
                                            "Tact3_Length_s = %d\r\n"
                                            "SourceG1_V = %.1f\r\n"
                                            "SourceG2_V = %.1f\r\n"
                                            "SourceG3_V = %.1f\r\n"
                                            "SourceG4_V = %.1f\r\n"
                                            "\r\nMeasured Data\r\n"
                                            "%s\r",
                                            cfgMeasurePlan.Tact1_Length_s,
                                            cfgMeasurePlan.Tact2_Length_s,
                                            cfgMeasurePlan.Tact3_Length_s,
                                            cfgMeasurePlan.SourceG1_V,
                                            cfgMeasurePlan.SourceG2_V,
                                            cfgMeasurePlan.SourceG3_V,
                                            cfgMeasurePlan.SourceG4_V,
                                            headerString);
                        xQueueSend( xQueue_Terminal, &tempString, NULL );
//                        vTaskDelay(20);
//                        result = f_open(&fil, pathMeasureFile, FA_OPEN_EXISTING | FA_WRITE);
//sprintf(tempString, "f_open = %s\n", stringResult[result]);
//xQueueSend( xQueue_Terminal, &tempString, NULL );
                    }
                    else
                    {
                        stateSDCardLed = SDCARD_LED_FLASH;
                        xQueueSend( xQueue_SDCardLed, &stateSDCardLed, NULL );

                        sprintf(tempString, "New file <%s> did not created!\r\n", pathMeasureFile);
                        xQueueSend( xQueue_Terminal, &tempString, NULL );
                        FatFsQueueData.configFileExistFlag = 0;    
                        xQueueSend( xQueue_FatFsOut, &FatFsQueueData, NULL );
                    }
                }
                break;
                    
            case FATFS_WRITE_DATA_TO_MEASUREMENT_FILE:
//xQueueSend( xQueue_Terminal, "__FATFS - fatfs write file\n", NULL );
                if (cardReady)
                {

                    SystemTimeQueueData.stateSystemTime = SYSTEM_TIME_GET;            
                    xQueueSend( xQueue_SystemTimeIn, &SystemTimeQueueData, NULL );
                    xQueueReceive( xQueue_SystemTimeOut, &SystemTimeQueueData, portMAX_DELAY );
                    result = f_open(&fil, pathMeasureFile, FA_OPEN_EXISTING | FA_WRITE);
//                    sprintf(tempString, "f_open = %s\n", stringResult[result]);
//                    xQueueSend( xQueue_Terminal, &tempString, NULL );
//                    result = FR_OK;
                    if (result == FR_OK)
                    {
                        result = f_lseek(&fil, f_size(&fil));
//                        sprintf(tempString, "f_lseek = %s\n", stringResult[result]);
//                        xQueueSend( xQueue_Terminal, &tempString, NULL );

                        ClearString(measureString, sizeof(measureString));
                        CreateMeasureString(FatFsQueueData.measureData, cfgMeasureEnable, measureString, cfgDatafileSettings.delimiter);
                        sprintf(tempString, "%s%02d.%02d.%02d %02d:%02d:%02d%s%s",
                                             measureString,                     
                                             SystemTimeQueueData.datatime.date,
                                             SystemTimeQueueData.datatime.month,
                                             SystemTimeQueueData.datatime.year,
                                             SystemTimeQueueData.datatime.hours,
                                             SystemTimeQueueData.datatime.minutes,
                                             SystemTimeQueueData.datatime.seconds,
                                             cfgDatafileSettings.delimiter,
                                             FatFsQueueData.stringName);                     
                        f_puts(tempString, &fil);
                        
//                        sprintf(tempString, "f_sizes = %d\n", (uint32_t)f_size(&fil));
//                        xQueueSend( xQueue_Terminal, &tempString, NULL );
//                        sprintf(tempString, "f_puts = %s\n", stringResult[result]);
//                        xQueueSend( xQueue_Terminal, &tempString, NULL );

                        FatFsQueueData.fileWriteFlag = 1;    
                        xQueueSend( xQueue_FatFsOut, &FatFsQueueData, NULL );

                        stringCounter++;
                        
                        if (stringCounter >= cfgDatafileSettings.stringsToWrite)
                        {
                            FatFsQueueData.stateFatFs = FATFS_CREATE_NEW_MEASUREMENT_FILE;            
                            xQueueSend( xQueue_FatFsIn, &FatFsQueueData, NULL ); 
                        }
                        ClearString(measureString, sizeof(measureString));
                        CreateMeasureString(FatFsQueueData.measureData, cfgMeasureEnable, measureString, "\t");
                        sprintf(tempString, "%s%02d.%02d.%02d %02d:%02d:%02d\t%s\tf_size = %d bytes\r\n",
                                            measureString,
                                            SystemTimeQueueData.datatime.date,
                                            SystemTimeQueueData.datatime.month,
                                            SystemTimeQueueData.datatime.year,
                                            SystemTimeQueueData.datatime.hours,
                                            SystemTimeQueueData.datatime.minutes,
                                            SystemTimeQueueData.datatime.seconds,
                                            FatFsQueueData.stringName,                     
                                            (uint32_t)f_size(&fil));
                        xQueueSend( xQueue_Terminal, &tempString, NULL );
                        f_close(&fil);
                    }
                    else
                    {
                        stateSDCardLed = SDCARD_LED_FLASH;
                        xQueueSend( xQueue_SDCardLed, &stateSDCardLed, NULL );

                        sprintf(tempString, "Can't write to measurement file <%s>!!!\nf_open = %s\r\n", pathMeasureFile, stringResult[result]);
                        xQueueSend( xQueue_Terminal, &tempString, NULL );
//                        measureEnableFlag = 0;
                        FatFsQueueData.fileWriteFlag = 0;    
                        xQueueSend( xQueue_FatFsOut, &FatFsQueueData, NULL );
                    }
  
                }
                break;
                    
            case FATFS_GET_CONFIG:
                if (cardReady)
                {
                    cfgMeasurePlan = ConfigMeasurePlan_GetParameters();
                    cfgMeasureEnable = ConfigMeasureEnable_GetParameters();
                    FatFsQueueData.cfgMeasurePlan = cfgMeasurePlan;
                    FatFsQueueData.cfgMeasureEnable = cfgMeasureEnable;
                    xQueueSend( xQueue_FatFsOut, &FatFsQueueData, NULL );
                }
                break;
                    
            case FATFS_CHECK_CONFIG_FILE_EXIST:
                if (cardReady)
                {
                    result = f_stat("0:/config.ini", NULL);
                    switch (result)
                    {
                        case FR_OK:
                            /* config file exist */
                            FatFsQueueData.configFileExistFlag = 1;    
                            break;
                                    
                        case FR_NO_FILE:
                            stateSDCardLed = SDCARD_LED_FLASH;
                            xQueueSend( xQueue_SDCardLed, &stateSDCardLed, NULL );

                            FatFsQueueData.configFileExistFlag = 0;    
                            sprintf(tempString, "file <0:/config.ini> not found!\r\n");
                            xQueueSend( xQueue_Terminal, &tempString, NULL );
                            break;
                            
                        default:
                            FatFsQueueData.configFileExistFlag = 0;    
                            sprintf(tempString, "_FATFS - FATFS_CHECK_CONFIG_FILE_EXIST - f_stat = %s\r\n", stringResult[result]);
                            xQueueSend( xQueue_Terminal, &tempString, NULL );
//                            xQueueSend( xQueue_Terminal, "System is in freeze state!!!\n", NULL );
                              break;
                    }
                    xQueueSend( xQueue_FatFsOut, &FatFsQueueData, NULL );
                }
                break;
                    
            case FATFS_IDLE:
                break;

            default:
                break;
        }
    }
}

/* End of file */
